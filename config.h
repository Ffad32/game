#ifdef CONFIG_H
#error config.h is already included
#endif
#define CONFIG_H

//set a widnow resolution
struct Config
{
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
} config = {1024 , 768 };