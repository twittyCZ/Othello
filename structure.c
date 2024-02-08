#include <stdlib.h>
#include <string.h>
#include "stdio.h"
#include "global.h"
#include "structure.h"
#include "reader.h"
#include <ctype.h>

void playerFree(struct player** play){
    if(!play || !*play){
        return;
    }
    playerDeinit(play);
    free((*play)->name);
    free((*play)->type);
    free(*play);
    *play = NULL;
}

void playerDeinit(struct player** pPlayer){
    if(!(*pPlayer)){
        return;
    }
    if((*pPlayer)->name){
        free((*pPlayer)->name);
        (*pPlayer)->name = NULL;
    }
    if((*pPlayer)->type){
        free((*pPlayer)->type);
        (*pPlayer)->type = NULL;
    }
    (*pPlayer)->depth = 0;
    (*pPlayer)->symbol = 0;
}

int playerInit(struct player** pPlayer, const char *type, const char *name, const int depth, int symbol){
    if(!(*pPlayer) || !type || !name || depth < 0){
        return 0;
    }
    (*pPlayer)->type = malloc((strlen(type) + 1) * sizeof(char));
    if(!(*pPlayer)->type){
        return 0;
    }
    (*pPlayer)->name = malloc((strlen(name) + 1) * sizeof(char));
    if(!(*pPlayer)->name){
        return 0;
    }
    memcpy((*pPlayer)->name, name, (strlen(name) + 1) * sizeof(char));
    memcpy((*pPlayer)->type, type, (strlen(type) + 1) * sizeof(char));
    (*pPlayer)->depth = depth;
    (*pPlayer)->symbol = symbol;
    return 1;
}

int playerChangeInit(struct player** pPlayer, const char *type, const char *name, const int depth, int symbol){
    if(!pPlayer || (*pPlayer == NULL) || !type || !name || depth < 0){
        return 0;
    }
    free((*pPlayer)->type);
    (*pPlayer)->type = malloc(sizeof (strlen(type) + 1));
    if(!(*pPlayer)->type){
        return 0;
    }
    free((*pPlayer)->name);
    (*pPlayer)->name = malloc(sizeof (strlen(name) + 1));
    if(!(*pPlayer)->name){
        return 0;
    }
    strcpy((*pPlayer)->type, type);
    strcpy((*pPlayer)->name, name);
    (*pPlayer)->depth = depth;
    (*pPlayer)->symbol = symbol;
    return 1;
}

void playerAllocate(struct player** pPlayer, const char *type, const char *name, const int depth, int symbol) {
    if (!type || !name || depth < 0 || !pPlayer) {
        printf("Invalid player description!\n");
        ext(1);
    }
    if ((*pPlayer) != NULL) {
        playerChangeInit(pPlayer, type, name, depth, symbol);
        return;
    }
    (*pPlayer) = malloc(sizeof(struct player));
    if (!(*pPlayer)) {
        return;
    }
    if (!playerInit(pPlayer, type, name, depth, symbol)) {
        free((*pPlayer));
        return;
    }
}

void loggerAllocate(struct logger** logg, int pocetTahu){
    if(pocetTahu <= 0 && !logg){
        return;
    }
    if((*logg) == NULL){
        (*logg) = malloc(sizeof(struct logger));
        if(!(*logg)){
            return;
        }
    }
    if(!loggerInit(logg, pocetTahu)){
        loggerFree(logg);
        return;
    }
}

int loggerInit(struct logger** logg, int pocetTahu){
    if(pocetTahu <= 0){
        return 0;
    }
    (*logg)->capacity = pocetTahu;
    (*logg)->bottom_bar = 0;
    (*logg)->upper_bar = 0;
    (*logg)->moves = malloc(sizeof (char *) * pocetTahu);
    (*logg)->fileOutputName = NULL;
    if(!(*logg)->moves){
        return 0;
    }
    return 1;
}

void loggerResize(struct logger** logg){
    if(!logg || !(*logg)){
        return;
    }
    (*logg)->moves = realloc((*logg)->moves, ((*logg)->capacity + 10) * sizeof(char *));
    (*logg)->capacity += 10;
}

void loggerSetOuputFile(struct logger** logg, const char* fileName){
    if(!fileName || !logg){
        return;
    }
    if ((*logg) == NULL){
        loggerAllocate(logg, 1);
    }
    (*logg)->fileOutputName = fileName;
}

void loggerAdd(struct logger** logg, const char* string){
    size_t len;
    if(!string){
        return;
    }
    if (!(*logg) || !(*logg)->moves) {
        loggerAllocate(logg, 1);
    }
    if((*logg)->upper_bar == (*logg)->capacity){
        loggerResize(logg);
    }
    len = strlen(string);
    (*logg)->moves[(*logg)->upper_bar] = malloc(sizeof(char) * (len + 2));
    memcpy((*logg)->moves[(*logg)->upper_bar], string, len);
    (*logg)->moves[(*logg)->upper_bar][len] = '\n';
    (*logg)->moves[(*logg)->upper_bar][len + 1] = '\0';
    (*logg)->upper_bar++;
}

char* logger_pop(struct logger** logg){
    if((*logg)->bottom_bar >= (*logg)->capacity || (*logg)->bottom_bar >= (*logg)->upper_bar){
        return NULL;
    }
    (*logg)->bottom_bar++;
    return (*logg)->moves[(*logg)->bottom_bar-1];
}

void logger_deinit(struct logger** logg){
    if(!(*logg)){
        return;
    }
    (*logg)->bottom_bar = 0;
}

void loggerFree(struct logger** logg){
        int i;
    if(!(*logg)){
        return;
    }
    logger_deinit(logg);
    if((*logg)->moves && (*logg)->upper_bar > 0){
        for(i = 0; i < (*logg)->upper_bar; i++){
            free((*logg)->moves[i]);
            (*logg)->moves[i] = NULL;
        }
    }
    if((*logg)->moves){
        free((*logg)->moves);
    }
    (*logg)->upper_bar = 0;
    (*logg)->capacity = 0;
    free((*logg));
}

void createBoardInt(struct board** board, int row, int col){
    if(row < 2 || col < 2){
        printf("Invalid board size!\n");
        ext(2);
    }
    boardAllocate(board, row, col);
}

void createBoard(struct board** board, const char* rowChar, const char* colChar){
    char* endptr;
    int row, col;
    if(!rowChar || !colChar){
        return;
    }
    row = strtol(rowChar, &endptr,0);
    if(*endptr != '\0'){
        return;
    }
    col = strtol(colChar, &endptr, 0);
    if(*endptr != '\0'){
        return;
    }
    boardAllocate(board, row, col);
}

void boardFree(struct board** board){
    if(!(board) || !(*board) || (*board) == NULL){
        return;
    }
    boardDeinit(board);
    free((*board)->values);
    free((*board));
    (*board) = NULL;
}

void boardDeinit(struct board** board){
    int i;
    if(!board || !(*board)) {
        return;
    }
    for (i = 0; i < (*board)->size; ++i) {
        (*board)->values[i] = 0;
    }
    (*board)->rows = 0;
    (*board)->cols = 0;
    (*board)->size = 0;
    (*board)->Q = 0;
    (*board)->initY = 0;
    (*board)->initX = 0;
}

int boardInit(struct board** board, int rows, int cols){
    if(!(*board) || !rows || !cols){
        return 0;
    }
    (*board)->cols = cols + 2;
    (*board)->rows = rows + 2;
    if((*board)->size == 0) {
        (*board)->values = malloc((*board)->cols * (*board)->rows * sizeof(int));
    } else {
        (*board)->values = realloc((*board)->values, (*board)->cols * (*board)->rows * sizeof(int));
    }
    (*board)->Q = (*board)->cols;
    (*board)->size = (*board)->cols * (*board)->rows;
    return 1;
}

void boardAllocate(struct board** board, int rows, int cols){
    if(!rows || !cols){
        printf("Invalid board size!\n");
        ext(2);
    }
    if(!(*board) || (*board) == NULL){
        (*board) = malloc(sizeof(struct board));
        if(!(*board)){
            return;
        }
        (*board)->initY = DEFAULT_INNITY_BOARD;
        (*board)->initX = DEFAULT_INNITX_BOARD;
        (*board)->size = 0;
    }
    if(!boardInit(board, rows, cols)){
        free(*board);
    }

}

int initializeBoardInt(struct board** board, int x, int y){
    if(!board || !(*board)){
        return 0;
    }
    if(x < 1 || y < 1){
        printf("Unable to place initial stones!\n");
        ext(3);
        return 0;
    }
    (*board)->initX = x;
    (*board)->initY = y;
    return 1;
}

int initializeBoard(struct board** board, const char *stringX, const char * stringY) {
    char* endptr;
    int x,y;
    if(!stringX || !stringY || !board || !(*board)){
        return 0;
    }
    x = strtol(stringX, &endptr, 0);
    if(*endptr !='\0'){
        ext(3);
        return 0;
    }
    y = strtol(stringY, &endptr, 0);
    if(*endptr != '\0'){
        ext(3);
        return 0;
    }
    if(x < 1 || y < 1){
        printf("Unable to place initial stones!\n");
        ext(3);
        return 0;
    }
    (*board)->initX = x;
    (*board)->initY = y;
    return 1;
}

void fillBoardByInnitValues(struct board** board){
    int i,j, number;
    if((*board)->cols - 2 <= 1 || (*board)->rows - 2 <= 1){
        printf("Invalid board size!\n");
        ext(2);
    }
    if(!(*board)){
        printf("Unable to place initial stones!\n");
        ext(3);
    }
    if((*board)->initX <= 0 || (*board)->initY <= 0){
        printf("Unable to place initial stones!\n");
        ext(3);
    }
    if((*board)->initY >= (*board) ->cols - 2 || (*board)->initX >= (*board) ->rows - 2){
        printf("Unable to place initial stones!\n");
        ext(3);
    }
    for( i = 0; i < (*board)->rows; i++){
        for(j = 0; j < (*board)->cols; j++){
            if(i == 0){
                (*board)->values[i*(*board)->Q + j] = BORDER;
            } else if(i == (*board)->rows - 1){
                (*board)->values[i*(*board)->Q + j] = BORDER;
            } else if(j == 0){
                (*board)->values[i*(*board)->Q + j] = BORDER;
            } else if( j == (*board)->cols - 1){
                (*board)->values[i*(*board)->Q + j] = BORDER;
            } else {
                (*board)->values[i*(*board)->Q + j] = EMPTY;
            }
        }
    }
    number = ((*board)->initX) * ((*board)->cols) + (*board)->initY;
    (*board)->values[number] = WHITE;
    number++;
    (*board)->values[number] = BLACK;
    number = ((*board)->initX+1) * ((*board)->cols) + (*board)->initY;
    (*board)->values[number] = BLACK;
    number++;
    (*board)->values[number] = WHITE;
}

void initDirections(struct board** board){
    (*board)->allDirections[0] = (*board)->Q;
    (*board)->allDirections[1] = - (*board)->Q;
    (*board)->allDirections[2] = 1;
    (*board)->allDirections[3] = -1;
    (*board)->allDirections[4] = (*board)->Q - 1;
    (*board)->allDirections[5] = (*board)->Q + 1;
    (*board)->allDirections[6] = - (*board)->Q - 1;
    (*board)->allDirections[7] = - (*board)->Q + 1;
}

char letterOfPlayer (int symbol) {
    if(symbol == BLACK){
        return 'b';
    } else if(symbol == WHITE) {
        return 'w';
    } else {
        return '?';
    }
}

int getPlayersScors(int symbol){
    int i, pocet;
    if(symbol != BLACK && symbol != WHITE){
        return 0;
    }
    pocet = 0;
    for(i = 0; i < playboard->rows * playboard->cols; i++){
        if(symbol == playboard->values[i]){
            pocet++;
        }
    }
    return pocet;
}

void printboard() {
    int row, col;
    for (col=1; col< playboard->cols - 1; col++) {
        if(col == 1){
            printf("   ");
        }
        printf("%d ", col);
    }
    printf("[%c=%d %c=%d]", letterOfPlayer(BLACK), getPlayersScors(BLACK), letterOfPlayer(WHITE),
           getPlayersScors(WHITE));
    printf("\n");
    for (row=1; row< playboard->rows - 1; row++) {
        printf("%d ", row);
        if(playboard->rows >= 10 && row < 10){
            printf(" ");
        }
        for (col=1; col< playboard->cols - 1; col++) {
            if (playboard->values[(row)*playboard->Q + col] == BLACK) {
                printf("b ");
            } else if (playboard->values[(row)*playboard->Q + col] == WHITE) {
                printf("w ");
            } else {
                printf(". ");
            }
            if (col >= 10) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void to_lowercase(char *str) {
    int i;
    for (i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void ext(int problem){
    boardFree(&playboard);
    playerFree(&player1);
    playerFree(&player2);
    loggerFree(&logger);
    exit(problem);
}