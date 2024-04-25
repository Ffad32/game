#include <string.h>

int processNPCSquare(int suffix, char *text, int scenemun)
{

    switch (suffix)
    {
    case 1:
        dialogueByScene(scenemun, 1, text);
        break;
    case 2:
        break;
    case 3:
        break;

    default:
        break;
    }
}
int dialogueByScene(int scene, int suf, char *text)
{
    switch (scene)
    {
    case 1:
        strcpy(text, "maps/map1.map");
        break;
    case 2:
        break;
    case 3:
        break;

    default:
        break;
    }
}