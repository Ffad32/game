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
#include <SDL_mixer.h>
//#include "entity.h"

typedef struct Scene
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Texture *bgTexture;
    SDL_Texture *texture;
    SDL_Texture *playerTexture;
} Scene;
// global variables
SDL_Rect cube;

void drawcube(void)
{
    cube.w = 50;                       // Width of the cube
    cube.h = 50;                       // Height of the cube
    cube.x = 0;                        // Initial x position of the cube
    cube.y = 0;                        // Initial y position of the cube
    cube.y = config.SCREEN_HEIGHT / 2; // Center the cube
    cube.x = config.SCREEN_WIDTH / 2;  // Center the cube
}
void seticon(SDL_Window *window)
{
    SDL_Surface *iconSurface = IMG_Load("pictures/icon.png");
    if (iconSurface == NULL)
    {
        fprintf(stderr, "IMG_Load Error: %s\n", IMG_GetError());
        return;
    }
    SDL_SetWindowIcon(window, iconSurface);
    SDL_FreeSurface(iconSurface);
}
Scene test(void)
{
    Scene scene;
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return scene;
    }
    // initialize SDL_ttf
    if (TTF_Init())
    {
        fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
        return scene;
    }
    SDL_DisplayMode dm;
    if(SDL_GetDesktopDisplayMode(0,&dm)!=0){
        fprintf(stderr,"SDL_GetDesktopDisplayMode Error : %s\n", SDL_GetError());
    }
    // set a window
    scene.window = SDL_CreateWindow("Edge of destiny", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dm.w, dm.h-50, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (scene.window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return scene;
    }

    // set a renderer
    scene.renderer = SDL_CreateRenderer(scene.window, -1, SDL_RENDERER_ACCELERATED);
    if (scene.renderer == NULL)
    {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return scene;
    }
    // logical size of the window
    SDL_RenderSetLogicalSize(scene.renderer, config.SCREEN_WIDTH, config.SCREEN_HEIGHT);

    // map jpg
    SDL_Surface *bgSurface = IMG_Load("pictures/start.jpg");
    // check if the image was loaded
    if (!bgSurface)
    {
        printf("Unable to load image: %s\n", IMG_GetError());
    }
    // create a texture from the surface
    scene.bgTexture = SDL_CreateTextureFromSurface(scene.renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    // check if the texture was created
    if (!scene.bgTexture)
    {
        printf("Unable to create texture: %s\n", SDL_GetError());
    }
    // player png
    SDL_Surface *playerSurface = IMG_Load("pictures/Screenshot 2024-01-31 161013.png");
    // check if the image was loaded
    if (!playerSurface)
    {
        printf("Unable to load image: %s\n", IMG_GetError());
    }
    // create a texture from the surface
    scene.playerTexture = SDL_CreateTextureFromSurface(scene.renderer, playerSurface);
    SDL_FreeSurface(playerSurface);
    // check if the texture was created
    if (!scene.playerTexture)
    {
        printf("Unable to create texture: %s\n", SDL_GetError());
    }
    return scene;
}
void updateMap(SDL_Renderer *rend)
{
    // set render color
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
    // clear the window with the render color
    SDL_RenderClear(rend);

    SDL_Rect rect = {0, 0, config.SCREEN_WIDTH, config.SCREEN_HEIGHT};
    SDL_RenderDrawRect(rend, &rect);
}
void updatePlayer(SDL_Renderer *rend, SDL_Texture *playerTexture)
{
    SDL_Rect playerDest = cube;
    SDL_RenderCopy(rend, playerTexture, NULL, &playerDest);
}
void clear(Scene scene)
{
    // clean up resources
    SDL_DestroyTexture(scene.bgTexture);
    SDL_DestroyTexture(scene.texture);
    SDL_DestroyRenderer(scene.renderer);
    SDL_DestroyTexture(scene.playerTexture);
    SDL_DestroyWindow(scene.window);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}
void background(SDL_Renderer *rend, SDL_Texture *bgTexture)
{
    //SDL_RenderClear(rend);
    SDL_RenderCopy(rend, bgTexture, NULL, NULL);
}
void mapchange(char *picname, Scene scene)
{

    SDL_Surface *bggSurface = IMG_Load(picname);
    // check if the image was loaded
    if (!bggSurface)
    {
        printf("Unable to load image: %s\n", IMG_GetError());
        return;
    }
    SDL_DestroyTexture(scene.bgTexture);
    // create a texture from the surface
    scene.bgTexture = SDL_CreateTextureFromSurface(scene.renderer, bggSurface);
    SDL_FreeSurface(bggSurface);
    // check if the texture was created
    if (!scene.bgTexture)
    {
        printf("Unable to create texture: %s\n", SDL_GetError());
    }
}
int drawtext(SDL_Renderer *rend, SDL_Texture *texture,char *dialogue)
{
    TTF_Font *font = TTF_OpenFont("fonts/Pixellettersfull-BnJ5.ttf", 32);
    if (font == NULL)
    {
        fprintf(stderr, "TTF_OpenFont Error: %s\n", TTF_GetError());
        return 5;
    }
    SDL_Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

    SDL_Surface *surface = TTF_RenderUTF8_Solid(font, dialogue, color);
    if (surface == NULL)
    {
        fprintf(stderr, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        return 6;
    }
    texture = SDL_CreateTextureFromSurface(rend, surface);
    if (texture == NULL)
    {
        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        return 7;
    }
    SDL_Rect dstrect;
    dstrect.x = 80;
    dstrect.y = 600;
    dstrect.w = surface->w;
    dstrect.h = surface->h;
    SDL_RenderCopy(rend, texture, NULL, &dstrect);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return 0;
}
void drawBlackRect(SDL_Renderer* rend) {
    SDL_Rect textforeground;
    textforeground.x = 0;
    textforeground.y = config.SCREEN_HEIGHT * 3 / 4;  // start at the bottom fouth of the screen
    textforeground.w = config.SCREEN_WIDTH;  // width is the full screen width
    textforeground.h = config.SCREEN_HEIGHT / 4;  // height is one fourth of the screen height

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);  // set the draw color to black
    SDL_RenderFillRect(rend, &textforeground);  // draw the rectangle
}

void playSoundtrack() {
    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    // Load music
    Mix_Music *music = Mix_LoadMUS("music/sound.mp3");
    if (music == NULL) {
        printf("Failed to load music. SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    // Play music
    if (Mix_PlayMusic(music, -1) == -1) {
        printf("Failed to play music. SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }
}
/*void player (SDL_Renderer* rend, enum Direction direction) {
    int frame = 0;
    switch (direction)
    {
    case NORTH:
        animationset(frame);
        frame ++;
        break;
    case SOUTH:
        animationset(frame);
        frame ++;
        break;
    case WEST:
        animationset(frame);
        frame ++;
        break;
    case EAST:
        animationset(frame);
        frame ++;
        break;
    case NORTH_WEST:
        animationset(frame);
        frame ++;
        break;
    case NORTH_EAST:
        animationset(frame);
        frame ++;
        break;
    case SOUTH_WEST:
        animationset(frame);
        frame ++;
        break;
    case SOUTH_EAST:
        animationset(frame);
        frame ++;
        break;
    default:
        break;
    }
    SDL_Surface* playerSurface1 = IMG_Load("pictures/Screenshot 2024-01-31 161013.png");   
}
void animationset(int frame,enum Direction direction){
    switch (direction)
    {
    case NORTH:
        
        break;
    case SOUTH:
        
        break;
    case WEST:
        
        break;
    case EAST:
        
        break;
    case NORTH_WEST:
        
        break;
    case NORTH_EAST:
        
        break;
    case SOUTH_WEST:
        
        break;
    case SOUTH_EAST:
        
        break;
    default:
        break;
    }
}   */