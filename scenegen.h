#include <string.h>
#include <stdio.h>
#define max 1000

int processNPCSquare(int suffix, int scenemun, KeyChain *key)
{

    switch (suffix)
    {
    case 1:
        if (dialogue("charactersdialogues/stranger/stranger.txt") == 6){
            key->actOneKey = true;
            return 6;
        }
        break;
    case 2:
        if(barmanSceneChoice(scenemun, key) == 6){
            return 6;
        };
        break;
    case 3:
        break;

    default:
        break;
    }
}
int barmanSceneChoice(int scenenum, KeyChain *key)
{
    switch (scenenum)
    {
    case 1:
        if(dialogue("charactersdialogues/barman/barmanACT1.txt")==6){
            key->tavernthought= true;
            return 6;
        }
        break;
    case 2:
        if(dialogue("charactersdialogues/barman/barmanACT2.txt")==6){
            key->shopthought= true;
            return 6;
        }
        break;
    default:
        break;
    }
}
FILE *dialogueFile = NULL;
char dialoguet[max] = "";
int dialogue(char *NPCnameFile)
{

    if (dialogueFile == NULL)
    {
        dialogueFile = fopen(NPCnameFile, "r");
        if (dialogueFile == NULL)
        {
            fprintf(stderr, "Error opening file: %s\n", NPCnameFile);
            return 1;
        }
    }

    if (fgets(dialoguet, max, dialogueFile) == NULL)
    {
        fprintf(stderr, "End of dialogue reached.\n");
        fclose(dialogueFile);
        dialogueFile = NULL;
        return 6;
    }
    printf("%s", dialoguet);
}

void endDialogue()
{
    if (dialogueFile != NULL)
    {
        fclose(dialogueFile);
        dialogueFile = NULL;
    }
}