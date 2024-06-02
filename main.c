#include "test.h"
#include "mapmaker.h"
#include "mapdes.h"
#include "scenegen.h"
#include "entity.h"

int main()
{
    enum Direction direction;
    enum Status status = MOVING;
    Uint32 dialogueEndTime = 0; // timer for dialogue
    Uint32 espamtimer = 0;
    int scenenum = 1;
    // mpa variables
    char filename[100] = "";
    char picname[100] = "";
    // movement flags for the player
    bool moving_up = false;
    bool moving_down = false;
    bool moving_left = false;
    bool moving_right = false;
    bool epressed = false;
    // collision ints
    Range collision;
    // window and map creation

    Scene scene = test();

    drawcube();
    map("maps/tos.map");
    seticon(scene.window);
    // text
    bool textfore = false;
    // main loop
    SDL_Event e;
    bool quit = false;
    playSoundtrack();
    while (!quit)
    {
        // event handling
        while (SDL_PollEvent(&e))
        {
            // quit event
            if (e.type == SDL_QUIT || e.type == SDL_MOUSEBUTTONDOWN)
            {
                quit = true;
            }
            // keyboard events
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                    moving_up = true;
                    break;
                case SDL_SCANCODE_S:
                    moving_down = true;
                    break;
                case SDL_SCANCODE_A:
                    moving_left = true;
                    break;
                case SDL_SCANCODE_D:
                    moving_right = true;
                    break;
                case SDL_SCANCODE_E:
                    epressed = true;
                    break;
                }
            }
            if (e.type == SDL_KEYUP)
            {
                switch (e.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                    moving_up = false;
                    break;
                case SDL_SCANCODE_S:
                    moving_down = false;
                    break;
                case SDL_SCANCODE_A:
                    moving_left = false;
                    break;
                case SDL_SCANCODE_D:
                    moving_right = false;
                    break;
                case SDL_SCANCODE_E:
                    epressed = false;
                    break;
                }
            }
        }

        direction = keyToDirection(moving_right, moving_left, moving_up, moving_down);
        // printf("Direction: %d\n", direction);

        if (SDL_GetTicks() > espamtimer)
        {
            if (collision.info == 3)
            {
                if (status == MOVING && (SDL_GetTicks() > dialogueEndTime))
                {
                    if (processNPCSquare(collision.code, scenenum) == 6)
                    {
                        printf("End of dialogue reached.\n");
                        status = MOVING;
                        // scenenum++;
                        espamtimer = SDL_GetTicks() + 2000; // set the end time to 2 seconds from now
                    }
                    else
                    {
                        status = DIALOGUE;
                        epressed = false;
                    }
                }

                if (epressed == true && SDL_GetTicks() > espamtimer)
                {
                    if (processNPCSquare(collision.code, scenenum) == 6)
                    {
                        printf("End of dialogue reached.\n");
                        status = MOVING;
                        // scenenum++;
                        espamtimer = SDL_GetTicks() + 2000; // set the end time to 2 seconds from now
                    }
                    else
                    {
                        epressed = false;
                    }
                }
            }
        }
        if (collision.info == 2)
        {
            status = HOLD;
            processMapSquare(collision.code, filename, picname);
            mapchange(picname, &scene);
            map(filename);
            status = MOVING;
        }
        // movemet sollution
        if (status == MOVING)
        {
            SDL_Rect target = {cube.x, cube.y, 50, 50};
            moving(direction, &target);

            // collision sollution
            // collision = detect(direction, &suffix,target);

            canMove(target, direction, &collision);
            // printf("collll: %d\n",collision);
            if (collision.info == 1)
            {
                moving(direction, &cube);
            }
        }

        // screen update

        updateMap(scene.renderer);
        renderBackground(scene.renderer, scene.bgTexture);
        updatePlayer(scene.renderer, scene.playerTexture);

        if (status == DIALOGUE)
        {
            drawBlackRect(scene.renderer);
            drawtext(scene.renderer, scene.texture, dialoguet);
            // draw textforeground
        }
        SDL_RenderPresent(scene.renderer);
        SDL_Delay(16);
    }
    // clean up
    clear(scene);
    return 0;
}
// collision detection function

void moving(enum Direction direction, SDL_Rect *rect)
{
    if (direction & NORTH)
    {
        rect->y -= 4;
    }
    if (direction & SOUTH)
    {
        rect->y += 4;
    }
    if (direction & WEST)
    {
        rect->x -= 4;
    }
    if (direction & EAST)
    {
        rect->x += 4;
    }
}

int keyToDirection(int moving_right, int moving_left, int moving_up, int moving_down)
{
    if (moving_right && moving_up)
    {
        return NORTH_EAST;
    }
    if (moving_right && moving_down)
    {
        return SOUTH_EAST;
    }
    if (moving_left && moving_up)
    {
        return NORTH_WEST;
    }
    if (moving_left && moving_down)
    {
        return SOUTH_WEST;
    }
    if (moving_right)
    {
        return EAST;
    }
    if (moving_left)
    {
        return WEST;
    }
    if (moving_up)
    {
        return NORTH;
    }
    if (moving_down)
    {
        return SOUTH;
    }
    return NONE;
}

bool intersect(SDL_Rect rect1, SDL_Rect rect2)
{
    bool inter = SDL_HasIntersection(&rect1, &rect2) == SDL_TRUE;
    return inter;
}

void canMove(SDL_Rect rect, enum Direction direction, Range *lastCode)
{
    int i = rect.x / 51.2;
    int j = rect.y / 51.2;

    // printf("ranges: %d, %d\n",i,j);
    lastCode->info = 1;

    if (direction & NORTH)
    {
        testRange(rect, ranges[i][j], lastCode);
        testRange(rect, ranges[i - 1][j], lastCode);
        testRange(rect, ranges[i + 1][j], lastCode);
    }
    if (direction & SOUTH)
    {
        testRange(rect, ranges[i][j + 1], lastCode);
        testRange(rect, ranges[i - 1][j + 1], lastCode);
        testRange(rect, ranges[i + 1][j + 1], lastCode);
    }
    if (direction & WEST)
    {
        testRange(rect, ranges[i][j], lastCode);
        testRange(rect, ranges[i][j - 1], lastCode);
        testRange(rect, ranges[i][j + 1], lastCode);
    }
    if (direction & EAST)
    {
        testRange(rect, ranges[i + 1][j], lastCode);
        testRange(rect, ranges[i + 1][j - 1], lastCode);
        testRange(rect, ranges[i + 1][j + 1], lastCode);
    }
}

SDL_Rect rangeToRect(Range range)
{
    SDL_Rect target;
    target.h = 50;
    target.w = 50;
    target.x = range.x_start;
    target.y = range.y_start;
    return target;
}

void testRange(SDL_Rect rect, Range range, Range *lastCode)
{
    if (range.info != 1)
    {
        if (intersect(rect, rangeToRect(range)) == true)
        {
            // printf("tttttt");
            if (lastCode->info == 1 || (range.info > lastCode->info))
                *lastCode = range;
        }
    }
}