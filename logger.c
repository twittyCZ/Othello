#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game.h"
#include "structure.h"
#include "global.h"

void reverseTransformInput(int number, char** myMemory){
    int r,c;
    if(number == -1){
        *myMemory = (char*) malloc(20 * sizeof(char));
        strcpy(*myMemory, "pass");
        return;
    } if(number == -3){
        *myMemory = (char*) malloc(20 * sizeof(char));
        strcpy(*myMemory, "save");
        return;
    } if(number == -2){
        *myMemory = (char*) malloc(20 * sizeof(char));
        strcpy(*myMemory, "quit");
        return;
    } if(number == 0 || number < -2) {
        ext(1);
    }
    r = number / playboard->cols;
    c = number % playboard->cols;
    *myMemory = (char*) malloc(20 * sizeof(char));
    sprintf(*myMemory, "%d_%d", r, c);
}

void addMoveToLogger(struct logger** pLogger, const char* newData) {
    if (!newData || !pLogger) {
        return;
    }
    loggerAdd(pLogger, newData);
}

void addWordsToLogger(struct logger** pLogger, const char** file, int gameIndex, int numberOfWords){
    int i, indexMove;
    if(!pLogger || !file){
        return;
    }
    indexMove = 0;
    for (i = gameIndex + 1; i < numberOfWords; i++) {
        if ((strlen(file[i]) == 1)) {
            break;
        }
        loggerAdd(pLogger, file[i]);
        indexMove++;
    }
}

void printParameters(){
    FILE *file;
    file = fopen(logger->fileOutputName,"a");
    if(strcmp(player1->type, MINIMAX_TYPE) == 0){
        fprintf(file,"[pb %s,%s,%d]\n", player1->type, player1->name, player1->depth);
    } else {
        fprintf(file,"[pb %s,%s]\n", player1->type, player1->name);
    }
    if(strcmp(player2->type, MINIMAX_TYPE) == 0){
        fprintf(file,"[pw %s,%s,%d]\n", player2->type, player2->name, player2->depth);
    } else {
        fprintf(file,"[pw %s,%s]\n", player2->type, player2->name);
    }
    fprintf(file,"[size %d %d]\n", playboard->cols - 2, playboard->rows - 2);
    fprintf(file,"[init %d %d]\n", playboard->initX, playboard->initY);
    fprintf(file,"[game]\n");
    fclose(file);
}

void printToInputFile(struct logger** pLogger, int end){
    FILE *file;
    char* word;
    if(!pLogger || (*pLogger) == NULL || !(*pLogger)->fileOutputName ||  (*pLogger)->fileOutputName == NULL || !(*pLogger)  || !(*pLogger)->moves){
        if(end == 0){
            printf("Invalid output file destinatination\n");
        }
        return;
    }
    if((*pLogger)->bottom_bar == 0 && (*pLogger)->upper_bar > 0){
        printParameters();
    }
    file = fopen((*pLogger)->fileOutputName,"a");
    while((word = logger_pop(pLogger)) != NULL){
        if((strcmp("save\n",word) == 0 || (strcmp("quit\n",word) == 0))) /* Příkazy interpretu se do souboru nezapisují */
        {
            continue;
        }
        fprintf(file,"%s",word);
    }
    fclose(file);
}




