#define SDL_MAIN_HANDLED
#ifdef TEST_H
#error test.h is already included
#endif
#define TEST_H

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

// global variables
SDL_Renderer *renderer;
SDL_Window *window;
SDL_Rect cube;
SDL_Rect sq;
SDL_Surface *bgSurface;
SDL_Texture *bgTexture;
SDL_Texture *playerTexture = NULL;
SDL_Surface *playerSurface;
/*TTF_Font* font;
SDL_Color color;
SDL_Surface* surface;
SDL_Texture* texture;
SDL_Rect dstrect;*/

void drawcube(void)
{
    cube.w = 50;                       // Width of the cube
    cube.h = 50;                       // Height of the cube
    cube.x = 0;                        // Initial x position of the cube
    cube.y = 0;                        // Initial y position of the cube
    cube.y = config.SCREEN_HEIGHT / 2; // Center the cube
    cube.x = config.SCREEN_WIDTH / 2;  // Center the cube
}

int test()
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 2;
    }
    // initialize SDL_ttf
    if (TTF_Init()){
        fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
        return 5;
    }

    // set a window
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, config.SCREEN_WIDTH, config.SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 3;
    }

    // set a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 4;
    }
    // map jpg
    bgSurface = IMG_Load("pictures/start.jpg");
    // check if the image was loaded
    if (!bgSurface)
    {   
        printf("Unable to load image: %s\n", IMG_GetError());
    }
    // create a texture from the surface
    bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    // check if the texture was created
    if (!bgTexture)
    {
        printf("Unable to create texture: %s\n", SDL_GetError());
    }
    // player png
    playerSurface = IMG_Load("pictures/Screenshot 2024-01-31 161013.png");
    // check if the image was loaded
    if (!playerSurface)
    {
        printf("Unable to load image: %s\n", IMG_GetError());
    }  
    // create a texture from the surface
    playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
    SDL_FreeSurface(playerSurface);
    // check if the texture was created
    if (!playerTexture)
    {
        printf("Unable to create texture: %s\n", SDL_GetError());
    }
    //logical size of the window
    SDL_RenderSetLogicalSize(renderer, config.SCREEN_WIDTH, config.SCREEN_HEIGHT);
}
void updateMap(void)
{
    // set render color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    // clear the window with the render color
    SDL_RenderClear(renderer);

    SDL_Rect rect = {0, 0, config.SCREEN_WIDTH, config.SCREEN_HEIGHT};
    SDL_RenderDrawRect(renderer, &rect);

}
void updatePlayer(void)
{
    SDL_Rect playerDest = cube; 
    SDL_RenderCopy(renderer, playerTexture, NULL, &playerDest);

}
void clear(void)
{
    // clean up resources
    SDL_DestroyTexture(bgTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
void background(void)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bgTexture, NULL, NULL);
}
void mapchange(char *picname)
{
   bgSurface = IMG_Load(picname);
    // check if the image was loaded
    if (!bgSurface)
    {   
        printf("Unable to load image: %s\n", IMG_GetError());
    }
    // create a texture from the surface
    bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    // check if the texture was created
    if (!bgTexture)
    {
        printf("Unable to create texture: %s\n", SDL_GetError());
    }
}
/*void updatetext(void){
    font = TTF_OpenFont("fonts/Pixelletters-RLm3.ttf", 24);
    color.r = 0;
    color.g = 0;
    color.b = 255;
    color.a = 255;

    surface = TTF_RenderText_Solid(font, "Hello, world!", color);
    if (surface == NULL)
    {
        fprintf(stderr, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 6;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 7;
    }

    dstrect.x = 50;
    dstrect.y = 50;
    dstrect.w = surface->w;
    dstrect.h = surface->h;

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}*/