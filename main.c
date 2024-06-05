#include "scene.h"
#include "map.h"
#include "dialogue.h"
#include "entity.h"
#include "controller.h"
#include <stdbool.h>

int main()
{
    int stepSize = 2;
    KeyChain keyChain;
    // key initialization
    keyChain.actOneKey = false;
    keyChain.bedRoomKey = false;
    keyChain.tavernthought = false;
    keyChain.shopthought = false;
    // animation ints
    int framenum = 0;
    int cycle = 0;
    // stats
    enum Direction direction = NONE;
    enum Status status = MOVING;
    // timers
    Uint32 dialogueEndTime = 0; // timer for dialogue
    Uint32 espamtimer = 0;      // timer for e spam
    bool epressed = false;
    // collision ints
    Range collision;
    // window and map creation
    
    Scene scene = initScene();

    initPlayer();
    loadMap(-1, &scene);
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
            handleEvent(&e,&direction,&epressed, &quit);
        }

        if (SDL_GetTicks() > espamtimer)
        {
            if (collision.info == 3)
            {
                if (status == MOVING && (SDL_GetTicks() > dialogueEndTime))
                {
                    if (processNPCSquare(collision.code, &keyChain) == 6)
                    {
                        printf("End of dialogue reached.\n");
                        status = MOVING;
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
                    if (processNPCSquare(collision.code, &keyChain) == 6)
                    {
                        printf("End of dialogue reached.\n");
                        status = MOVING;
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
            bool temp = false;
            status = HOLD;
            temp = processMapSquare(collision.code, &keyChain);
            if (temp == true)
            {
                loadMap(collision.code, &scene);
                //loadMapDefinition(filename);
            }
            status = MOVING;
        }
        // movemet sollution
        if (status == MOVING)
        {
            SDL_Rect target = {cube.x, cube.y, 50, 50};
            moving(direction, &target, stepSize);
            canMove(target, direction, &collision);
            // printf("collll: %d\n",collision);
            if (collision.info == 1)
            {
                moving(direction, &cube, stepSize);
            }
        }

        if (status == MOVING && direction != NONE)
        {
            cycle++;
            if (cycle % 10 == 0)
            {
                framenum++;
            }
            framenum = framenum % 8;
        }

        // screen update

        updaterend(scene.renderer);
        renderBackground(scene.renderer, scene.bgTexture);

        updatePlayer(scene.renderer, scene.playerTexture, framenum);

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