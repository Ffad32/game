#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <SDL.h>
#include "entity.h"
#include <stdbool.h>

void handleEvent(SDL_Event *e,int *direction, bool *epressed,bool *quit)
{
    // quit event
    if (e->type == SDL_QUIT /* || e.type == SDL_MOUSEBUTTONDOWN*/)
    {
        *quit = true;
    }
    // keyboard events
    if (e->type == SDL_KEYDOWN)
    {
        switch (e->key.keysym.scancode)
        {
        case SDL_SCANCODE_W:
            *direction |= NORTH;
            break;
        case SDL_SCANCODE_S:
            *direction |= SOUTH;
            break;
        case SDL_SCANCODE_A:
            *direction |= WEST;
            break;
        case SDL_SCANCODE_D:
            *direction |= EAST;
            break;
        case SDL_SCANCODE_E:
            *epressed = true;
            break;
        }
    }
    if (e->type == SDL_KEYUP)
    {
        switch (e->key.keysym.scancode)
        {
        case SDL_SCANCODE_W:
            *direction &= ~NORTH;
            break;
        case SDL_SCANCODE_S:
            *direction &= ~SOUTH;
            break;
        case SDL_SCANCODE_A:
            *direction &= ~WEST;
            break;
        case SDL_SCANCODE_D:
            *direction &= ~EAST;
            break;
        case SDL_SCANCODE_E:
            *epressed = false;
            break;
        }
    }
}
#endif //_CONTROLLER_H_