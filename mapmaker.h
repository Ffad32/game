#ifdef MAPMAKER_H
#error mapmaker.h is already included
#endif
#define MAPMAKER_H

#include <SDL.h>
#include <stdio.h>
#include <math.h>

enum MAP_INFO {
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

int map(const char *filename)
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
    if (fscanf(f, "code=%4d\n", &code) == 1)
    {
        printf("Code: %d\n", code);
    }
    if (fscanf(f, "name=%24s\n", name) == 1)
    {
        printf("Name: %s\n", name);
    }
    fscanf(f, "%*[^\n]\n"); // Skip the third line
    if (fscanf(f, "size=%f\n", &size) == 1)
    {
        printf("Size: %f\n", size);
    }
    fscanf(f, "%*[^\n]\n");
    fscanf(f, "%*[^\n]\n");

    // getting map data

    int row = 20;
    int col = 15;
    int count = 0;
    int prefix, suffix;
    float sx = config.SCREEN_WIDTH / row;
    float sy = config.SCREEN_HEIGHT / col;
    int x = 0;
    int y = 0;
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            ranges[j][i].x_start = j * sx;
            ranges[j][i].x_end = j * sx + sx;
            ranges[j][i].y_start = i * sy;
            ranges[j][i].y_end = i * sy + sy;
        }
    }
    while (count < LIMIT && fscanf(f, "%2d:%4d", &prefix, &suffix) == 2)
    {
        int i = count / row; // Calculate the row index
        int j = count % row; // Calculate the column index

        ranges[j][i].info = prefix; // Assign the prefix value to the info field of the range
        ranges[j][i].code = suffix; // Assign the suffix value to the code field of the range

        count++;
    }
    fclose(f);
    return 0;
}