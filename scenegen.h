#include <string.h>
#include <stdio.h>
#define max 1000

int processNPCSquare(int suffix, int scenemun)
{

    switch (suffix)
    {
    case 1:
        barmanSceneChoice(scenemun);
        break;
    case 2:
        break;
    case 3:
        break;

    default:
        break;
    }
}
int barmanSceneChoice(int scenenum){
    switch (scenenum)
    {
    case 1 :
        dialogue("charactersdialogues/barman/barmanScene1.txt");
        break;
    case 2:

        break;
    default:
        break;
    }
}
FILE* dialogueFile = NULL;
char dialoguet[max] = "";
int dialogue(char* NPCnameFile) {
    
    if (dialogueFile == NULL) {
        dialogueFile = fopen(NPCnameFile, "r");
        if (dialogueFile == NULL) {
            fprintf(stderr, "Error opening file: %s\n", NPCnameFile);
            return 1;
        }
    }

    if (fgets(dialoguet, max, dialogueFile) == NULL) {
        fprintf(stderr, "End of dialogue reached.\n");
        fclose(dialogueFile);
        dialogueFile = NULL;
        return 6;
    }
    printf("%s", dialoguet);
}

void endDialogue() {
    if (dialogueFile != NULL) {
        fclose(dialogueFile);
        dialogueFile = NULL;
    }
}