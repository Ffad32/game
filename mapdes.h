#include <string.h>

void processMapSquare(int suffix, char *filename, char *picname)
{

    switch (suffix)
    {
    case 1:
        strcpy(filename, "maps/tos.map");
        strcpy(picname, "pictures/Vlada.png");
        cube.x=500;
        cube.y=500;
        break;
    case 2:
        strcpy(filename, "maps/map1.map");
        strcpy(picname, "pictures/start.jpg");
        break;
    case 3:
        strcpy(filename, "maps/map1.map");
        strcpy(picname, "pictures/start.jpg");
        break;

    default:
        break;
    }
}