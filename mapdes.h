#include <string.h>

void processMapSquare(int suffix) {
    char filename[25];
    char picname[25];
    switch (suffix) {
        case 00001:
            strcpy(filename, "maps/map1.map");
            strcpy(picname, "pictures/start.jpg");
            break;
        case 00002:
            strcpy(filename, "maps/map1.map");
            strcpy(picname, "pictures/start.jpg");
            break;
        case 00003:
            strcpy(filename, "maps/map1.map");
            strcpy(picname, "pictures/start.jpg");
            break;
        
        default:
            break;
    }
}