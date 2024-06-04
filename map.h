#ifndef _MAP_H
#define _MAP_H

#include <SDL.h>
#include <stdio.h>
#include <math.h>
#include "dialogue.h"

enum MAP_INFO
{
    VOID = 0,
    ROAD = 1,
    TRIGGER = 2,
    GATEWAY = 3
};

typedef struct
{
    int x_start;
    int x_end;
    int y_start;
    int y_end;
    int info;
    int code;
} Range;

Range ranges[20][15];

#define LIMIT 10000

int loadMapDefinition(const char *filename)
{

    int td = 0;
    int code = 0;   // Variable to store the return code
    char name[25];  // Array to store the data
    float size = 0; // Variable to store the data
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Error: Could not open file\n");
        return 1;
    }

    // getting map info

    fscanf(f, "%*[^\n]\n"); // Skip the first line
    if (fscanf(f, "code=%4d\n", &code) != 1)
    {
        printf("code error");
    }
    if (fscanf(f, "name=%24s\n", name) != 1)
    {
        printf("name error");
    }
    fscanf(f, "%*[^\n]\n");                    // Skip the third line
    if (fscanf(f, "size=%f\n", &size) != NULL) /////////// 
    {
        printf("Size error\n");
    }
    fscanf(f, "%*[^\n]\n");
    fscanf(f, "%*[^\n]\n");

    // getting map data

    int col = 20;
    int row = 15;
    int count = 0;
    int prefix, suffix;
    float sx = config.SCREEN_WIDTH / col;
    float sy = config.SCREEN_HEIGHT / row;
    int x = 0;
    int y = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            ranges[j][i].x_start = j * sx;
            ranges[j][i].x_end = j * sx + sx;
            ranges[j][i].y_start = i * sy;
            ranges[j][i].y_end = i * sy + sy;
        }
    }
    while (count < LIMIT && fscanf(f, "%2d:%4d", &prefix, &suffix) == 2)
    {
        int i = count / col; // Calculate the col index
        int j = count % col; // Calculate the column index

        ranges[j][i].info = prefix; // Assign the prefix value to the info field of the range
        ranges[j][i].code = suffix; // Assign the suffix value to the code field of the range

        count++;
    }
    fclose(f);
    printf("map layout updated sucesfully\n");
    return 0;
}

bool processMapSquare(int suffix, KeyChain *key)
{

    switch (suffix)
    {
    case 1:
        return key->actOneKey == true;
    case 2:
        return key->tavernthought == true;
    case 3:
        return key->bedRoomKey == true;
    case 4:
        return true;
    case 5:
        return key->shopthought == true;
    case 6:
        return key->barmanlastdialogue == true;
    case 7:
        break;
    default:
        break;
    }
    return false;
}

// change background
void loadMap(int suffix, Scene *scene)
{
    char filename[100] = "";
    char picname[100] = "";

    switch (suffix)
    {
    case 1:
        strcpy(filename, "maps/tavern_at_night.map");
        strcpy(picname, "pictures/mapPic/taver near night.jpg");
        cube.x = ((config.SCREEN_WIDTH / 2) - (cube.w / 2));
        cube.y = ((config.SCREEN_HEIGHT / 2) - (cube.h / 2));
        break;
    case 2:
        strcpy(filename, "maps/taverna.map");
        strcpy(picname, "pictures/mapPic/tavern.jpg");
        cube.x = ((config.SCREEN_WIDTH / 2) - (cube.w / 2));
        cube.y = ((config.SCREEN_HEIGHT / 2) - (cube.h / 2));
        break;
    case 3:
        strcpy(filename, "maps/bedroommap.map");
        strcpy(picname, "pictures/mapPic/bedroomNightt.jpg");
        cube.x = ((config.SCREEN_WIDTH / 2) - (cube.w / 2) + 100);
        cube.y = ((config.SCREEN_HEIGHT / 2) - (cube.h / 2));
        break;
    case 4:
        strcpy(filename, "maps/bedroommap copy.map");
        strcpy(picname, "pictures/mapPic/bedroomDayy.jpg");
        cube.x = ((config.SCREEN_WIDTH / 2) - (cube.w / 2) + 100);
        cube.y = ((config.SCREEN_HEIGHT / 2) - (cube.h / 2));
        break;
    case 5:
        strcpy(filename, "maps/taverna copy.map");
        strcpy(picname, "pictures/mapPic/tavern.jpg");
        cube.x = ((config.SCREEN_WIDTH / 2) - (cube.w / 2));
        cube.y = ((config.SCREEN_HEIGHT / 2) - (cube.h / 2));
        break;
    case 6:
        strcpy(filename, "maps/tavern_at_night.map");
        strcpy(picname, "pictures/mapPic/taver near.jpg");
        cube.x = ((config.SCREEN_WIDTH / 2) - (cube.w / 2));
        cube.y = ((config.SCREEN_HEIGHT / 2) - (cube.h / 2));
        break;
    case 7:
        strcpy(filename, "maps/tos.map");
        strcpy(picname, "pictures/mapPic/tavern.jpg");
        cube.x = ((config.SCREEN_WIDTH / 2) - (cube.w / 2));
        cube.y = ((config.SCREEN_HEIGHT / 2) - (cube.h / 2));
        break;
    case -1:
        strcpy(filename, "maps/starting map.map");
        strcpy(picname, "pictures/mapPic/startingLoc.jpg");
        break;
    default:
        return;
    }

    if (scene->bgTexture != NULL)
    {
        SDL_DestroyTexture(scene->bgTexture);
        scene->bgTexture = NULL;
    }
    scene->bgTexture = IMG_LoadTexture(scene->renderer, picname);
    // check if the texture was created
    if (!scene->bgTexture)
    {
        printf("Unable to create texture: %s\n", SDL_GetError());
    }

    loadMapDefinition(filename);
}

#endif //_MAP_H