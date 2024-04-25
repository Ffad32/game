#include "test.h"
#include "mapmaker.h"
#include "mapdes.h"

int main()
{
    
    
    //mpa variables
    char filename[50]="";
    char picname[50]="";
    // movement flags for the player
    bool moving_up = false;
    bool moving_down = false;
    bool moving_left = false;
    bool moving_right = false;
    // stop flag
    bool stop = false;
    // collision ints
    int collsion1, collision2;
    int suffix;
    // window and map creation
    Scene scene=test();
    drawcube();
    map("maps/tos.map");
    seticon(scene.window);
    // main loop
    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        // event handling
        while (SDL_PollEvent(&e))
        {
            // quit event
            if (e.type == SDL_QUIT)
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
                }
            }
            // quit event
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                quit = true;
            }
        }
        if (collsion1 == 3 || collision2 == 3)
        {
            // NPC dialog box
        }

        if (collsion1 == 2 || collision2 == 2)
        {
            processMapSquare(suffix, filename, picname);
            mapchange(picname,scene);
            map(filename);
        }
        // collision sollution
        if (moving_up && moving_right)
        {
            collsion1 = check_collision_with_poin(cube, false, false, true, false,&suffix);
            collision2 = check_collision_with_poin(cube, true, false, false, false,&suffix);
            if (collsion1 == 1 && collision2 == 1)
            {
                cube.y -= 4;
                cube.x += 4;
            }
        }
        else if (moving_up && moving_left)
        {
            collsion1 = check_collision_with_poin(cube, false, true, false, false,&suffix);
            collision2 = check_collision_with_poin(cube, false, false, true, false,&suffix);
            if (collsion1 == 1 && collision2 == 1)
            {
                cube.y -= 4;
                cube.x -= 4;
            }
        }
        else if (moving_down && moving_right)
        {
            collsion1 = check_collision_with_poin(cube, false, false, false, true,&suffix);
            collision2 = check_collision_with_poin(cube, true, false, false, false,&suffix);
            if (collsion1 == 1 && collision2 == 1)
            {
                cube.y += 4;
                cube.x += 4;
            }
        }
        else if (moving_down && moving_left)
        {
            collsion1 = check_collision_with_poin(cube, false, false, false, true,&suffix);
            collision2 = check_collision_with_poin(cube, false, true, false, false,&suffix);
            if (collsion1 == 1 && collision2 == 1)
            {
                cube.y += 4;
                cube.x -= 4;
            }
        }
        else if (moving_up)
        {
            collsion1 = check_collision_with_poin(cube, false, false, true, false,&suffix);
            if (collsion1 == 1)
            {
                cube.y -= 4;
            }
        }
        else if (moving_down)
        {
            collsion1 = check_collision_with_poin(cube, false, false, false, true,&suffix);
            if (collsion1 == 1)
            {
                cube.y += 4;
            }
        }
        else if (moving_left)
        {
            collsion1 = check_collision_with_poin(cube, false, true, false, false,&suffix);
            if (collsion1 == 1)
            {
                cube.x -= 4;
            }
        }
        else if (moving_right)
        {
            collsion1 = check_collision_with_poin(cube, true, false, false, false,&suffix);
            if (collsion1 == 1)
            {
                cube.x += 4;
            }
        }
        // screen update
    
        updateMap(scene.renderer);
        background(scene.renderer, scene.bgTexture);
        updatePlayer(scene.renderer, scene.playerTexture);
        drawtext(scene.renderer, scene.texture);
        SDL_RenderPresent(scene.renderer);
        SDL_Delay(16);
    }
    // clean up
    clear(scene);
    return 0;
}
// collision detection function
int check_collision_with_poin(SDL_Rect cube, int moving_right, int moving_left, int moving_up, int moving_down, int* suffix)
{
    int margin = 12; // Adjust this to change the size of the margin for collision detection

    int left_margin = moving_left ? margin : 0;
    int right_margin = moving_right ? margin : 0;
    int top_margin = moving_up ? margin : 0;
    int bottom_margin = moving_down ? margin : 0;

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            Range range = ranges[i][j];
            if (moving_right && cube.x + cube.w + margin > range.x_start && cube.x + cube.w <= range.x_end &&
                cube.y < range.y_end && cube.y + cube.h > range.y_start)
            {
                printf("Collision detected with range at (%d, %d) with info = %d and code %d\n", i, j, range.info, range.code);
                *suffix = range.code;
                return range.info;
            }
            if (moving_left && cube.x - margin < range.x_end && cube.x >= range.x_start &&
                cube.y < range.y_end && cube.y + cube.h > range.y_start)
            {
                printf("Collision detected with range at (%d, %d) with info = %d and code %d\n", i, j, range.info, range.code);
                *suffix = range.code;
                return range.info;
            }
            if (moving_up && cube.y - margin < range.y_end && cube.y >= range.y_start &&
                cube.x < range.x_end && cube.x + cube.w > range.x_start)
            {
                printf("Collision detected with range at (%d, %d) with info = %d and code %d\n", i, j, range.info, range.code);
                *suffix = range.code;
                return range.info;
            }
            if (moving_down && cube.y + cube.h + margin > range.y_start && cube.y + cube.h <= range.y_end &&
                cube.x < range.x_end && cube.x + cube.w > range.x_start)
            {
                printf("Collision detected with range at (%d, %d) with info = %d and code %d\n", i, j, range.info, range.code);
                *suffix = range.code;
                return range.info;
            }
        }
    }

    return 0;
}
