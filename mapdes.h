#include <string.h>
// #include "scenegen.h"

bool processMapSquare(int suffix, char *filename, char *picname, KeyChain *key)
{

    switch (suffix)
    {
    case 1:
        if (key->actOneKey == true)
        {
            strcpy(filename, "maps/tavern_at_night.map");
            strcpy(picname, "pictures/mapPic/taverNearNight.jpg");
            cube.x = ((config.SCREEN_WIDTH / 2) - (cube.w / 2));
            cube.y = ((config.SCREEN_HEIGHT / 2) - (cube.h / 2));
            return true;
        }
        break;
    case 2:
        strcpy(filename, "maps/taverna.map");
        strcpy(picname, "pictures/mapPic/tavern.jpg");
        cube.x = ((config.SCREEN_WIDTH / 2) - (cube.w / 2));
        cube.y = ((config.SCREEN_HEIGHT / 2) - (cube.h / 2));
        printf("lol");
        return true;
        break;
    case 3:
        strcpy(filename, "maps/bedroommap.map");
        strcpy(picname, "pictures/mapPic/bedroom.jpg");
        cube.x = ((config.SCREEN_WIDTH / 2) - (cube.w / 2)+100);
        cube.y = ((config.SCREEN_HEIGHT / 2) - (cube.h / 2));
        return true;
        break;
    case 4:
        strcpy(filename, "maps/tos.map");
        strcpy(picname, "pictures/start.jpg");
        cube.x = ((config.SCREEN_WIDTH / 2) - (cube.w / 2));
        cube.y = ((config.SCREEN_HEIGHT / 2) - (cube.h / 2));
        break;
    case 5:
        strcpy(filename, "maps/tos.map");
        strcpy(picname, "pictures/start.jpg");
        cube.x = ((config.SCREEN_WIDTH / 2) - (cube.w / 2));
        cube.y = ((config.SCREEN_HEIGHT / 2) - (cube.h / 2));
        break;
    default:
        break;
    }
    return false;
}
