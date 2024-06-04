#include <string.h>
#include <stdio.h>
#define max 1000

int processNPCSquare(int suffix, KeyChain *key)
{

    switch (suffix)
    {
    case 1:
        if (dialogue("charactersdialogues/stranger/stranger.txt") == 6)
        {
            key->actOneKey = true;
            return 6;
        }
        break;
    case 2:
        if (dialogue("charactersdialogues/thoughts/taverthought.txt") == 6)
        {
            key->tavernthought = true;
            return 6;
        };
        break;
    case 3:
        if (dialogue("charactersdialogues/barman/barmanACT1.txt") == 6)
        {
            key->bedRoomKey = true;
            return 6;
        };
        break;
    case 4:
        if (dialogue("charactersdialogues/thoughts/tavernThought2.txt") == 6)
        {
            key->shopthought = true;
            return 6;
        }
        break;
    case 5:
        if (dialogue("charactersdialogues/barman/barmanACT2.txt") == 6)
        {
            key->barmanlastdialogue = true;
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