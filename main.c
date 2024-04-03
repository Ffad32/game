#include "test.c"
#include "mapmaker.c"

int main()
{
    //movement flags for the player
    bool moving_up = false;
    bool moving_down = false;
    bool moving_left = false;
    bool moving_right = false;
    //stop flag
    bool stop = false;
    //window and map creation
    test();
    drawcube();
    map();
    //main loop
    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        //event handling
        while (SDL_PollEvent(&e))
        {
            //quit event
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            //keyboard events
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
            //quit event
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                quit = true;
            }
        }
        //collision sollution
        int collsion1,collision2;
        if(collsion1==2 || collision2==2)
        {

        }
        if (moving_up && moving_right)
        {   
            collsion1=check_collision_with_poin(cube, false, false, true, false);
            collision2=check_collision_with_poin(cube, true, false, false, false);
            if (collsion1 == 1 && collision2 == 1)
            {
                cube.y -= 4;
                cube.x += 4;
            }
        }
        else if (moving_up && moving_left)
        {   
            collsion1=check_collision_with_poin(cube, false, true, false, false);
            collision2=check_collision_with_poin(cube, false, false, true, false);
            if (collsion1 == 1 && collision2 == 1)
            {
                cube.y -= 4;
                cube.x -= 4;
            }
        }
        else if (moving_down && moving_right)
        {   
            collsion1=check_collision_with_poin(cube, false, false, false, true);
            collision2=check_collision_with_poin(cube, true, false, false, false);
            if (collsion1 == 1 && collision2 == 1)
            {
                cube.y += 4;
                cube.x += 4;
            }
        }
        else if (moving_down && moving_left)
        {   
            collsion1=check_collision_with_poin(cube, false, false, false, true);
            collision2=check_collision_with_poin(cube, false, true, false, false);
            if (collsion1 == 1 && collision2 == 1)
            {
                cube.y += 4;
                cube.x -= 4;
            }
        }
        else if (moving_up)
        {
            collsion1=check_collision_with_poin(cube, false, false, true, false);
            if (collsion1 == 1){
            cube.y -= 4;
            }
        }
        else if (moving_down)
        {
            collsion1=check_collision_with_poin(cube, false, false, false, true);
            if (collsion1 == 1){
            cube.y += 4;
            }
        }
        else if (moving_left)
        {
            collsion1=check_collision_with_poin(cube, false, true, false, false);
            if (collsion1 == 1){
            cube.x -= 4;
            }
        }
        else if (moving_right)
        {
            collsion1=check_collision_with_poin(cube, true, false, false, false);
            if (collsion1 == 1){
                cube.x += 4;
            }
        }
        //screen update
        updateMap();
        background();
        updatePlayer();
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    //clean up
    clear();
    return 0;
}
//collision detection function
int check_collision_with_poin(SDL_Rect cube, int moving_right, int moving_left, int moving_up, int moving_down)
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
                printf("Collision detected with range at (%d, %d) with info = %d\n", i, j, range.info);
                return range.info;
            }
            if (moving_left && cube.x - margin < range.x_end && cube.x >= range.x_start &&
                cube.y < range.y_end && cube.y + cube.h > range.y_start)
            {
                printf("Collision detected with range at (%d, %d) with info = %d\n", i, j, range.info);
                return range.info;
            }
            if (moving_up && cube.y - margin < range.y_end && cube.y >= range.y_start &&
                cube.x < range.x_end && cube.x + cube.w > range.x_start)
            {
                printf("Collision detected with range at (%d, %d) with info = %d\n", i, j, range.info);
                return range.info;
            }
            if (moving_down && cube.y + cube.h + margin > range.y_start && cube.y + cube.h <= range.y_end &&
                cube.x < range.x_end && cube.x + cube.w > range.x_start)
            {
                printf("Collision detected with range at (%d, %d) with info = %d\n", i, j, range.info);
                return range.info;
            }
        }
    }

    return 0;
}
