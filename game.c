#include <stdlib.h>
#include <string.h>
#include "stdio.h"
#include "game.h"
#include "structure.h"
#include "global.h"

void othello() {
    int player;
    fillBoardByInnitValues(&playboard); /* Vložení inicializačních kamenů do hrací desky*/
    printboard();
    player = inputPlay();
    do {
        if (player == BLACK) {
            getmove(player1->type, BLACK, playboard->values);
        } else {
            getmove(player2->type, WHITE, playboard->values);
        }
        player = nextPlayer(playboard->values, player);
        printboard();
    }
    while (player != 0);
    printf("The game is over. Final result:\n");
    printboard();
    printToInputFile(&logger, 1);
}

int otherPlayer(int player) {
    if(player == BLACK){
        return WHITE;
    } else if(player == WHITE){
        return BLACK;
    } return 0;
}

int findFinalDestination(int move, int player, int* board, int direction) {
    if(move < 0 || !board){
        return 0;
    }
    while (board[move] == otherPlayer(player)) {
        move = move + direction;
    }
    if (board[move] == player) {
        return move;
    } else {
        return 0;
    }
}

int tryJump(int move, int player, int* board, int direction) {
    int nextSquare;
    if(move < 0 || !board){
        return 0;
    }
    nextSquare = move + direction;
    if (board[nextSquare] == otherPlayer(player)) {
        return findFinalDestination(nextSquare + direction, player, board, direction);
    } else {
        return 0;
    }
}

int validMove(int move) {
    if ((move > playboard->Q) && (move < (playboard->Q * (playboard->rows - 1))) && (move % playboard->Q != 0) && (move % playboard->Q != playboard->Q - 1)) {
        return 1;
    } else {
        return 0;
    }
}

int legalMove(int move, int player,int* board) {
    int i;
    if (!validMove(move) || !board) {
        return 0;
    }
    if (board[move]==EMPTY) {
        i=0;
        while (i <=7 && !tryJump(move, player, board, playboard->allDirections[i])) {
            i++;
        } if (i == 8) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}

int makeJump(int move, int player, int* board, int direction) {
    int finalDestination, nextSquare;
    if(!board){
        return 0;
    }
    finalDestination = tryJump(move, player, board, direction);
    if (finalDestination) {
        nextSquare = move + direction;
        do {
            board[nextSquare] = player;
            nextSquare = nextSquare + direction;
        } while (nextSquare != finalDestination);
        return 1;
    }
    return 0;
}

void makeMove(int move, int player, int* board) {
    int i;
    if(!board){
        return;
    }
    board[move] = player;
    for (i = 0; i <= 7; i++) {
        makeJump(move, player, board, playboard->allDirections[i]);
    }
}


int anyCorrectMove(int player, int* board) {
    int move;
    if(!board){
        return 0;
    }
    for (move= playboard->Q + 1; move < playboard->size ; move++){
        if(legalMove(move, player, board)){
            return 1;
        }
    }
    return 0;
}

int nextPlayer(int* board, int previousplayer) {
    int opponent;
    if(!board || !previousplayer){
        return 0;
    }
    opponent = otherPlayer(previousplayer);
    if (anyCorrectMove(opponent, board)){
        return opponent;
    } else if (opponent == BLACK && (strcmp(player1->type, HUMAN_TYPE) == 0)){
        return opponent;
    } else if(opponent == WHITE && (strcmp(player2->type, HUMAN_TYPE) == 0)){
        return opponent;
    }
    if (anyCorrectMove(previousplayer, board)) {
        return opponent;
    }
    return 0;
}

void sortArray(int* arrayMoves) {
    int i, j, temp1, n;
    if(!arrayMoves){
        return;
    }
    n = arrayMoves[0];
    for (i = 1; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (arrayMoves[j] < arrayMoves[i]) {
                temp1 = arrayMoves[i];
                arrayMoves[i] = arrayMoves[j];
                arrayMoves[j] = temp1;
            }
        }
    }
}

int* validMoves(int player, int* board) {
    int move, numberOfValidMoves, i, * arrayMoves;
    if(!player || !board){
        return 0;
    }
    numberOfValidMoves = (playboard->rows - 2) * (playboard->cols - 2);
    arrayMoves = (int *)malloc(numberOfValidMoves * sizeof(int));
    arrayMoves[0] = numberOfValidMoves;
    i = 0;
    for (move= playboard->Q + 1; move < playboard->size ; move++)
        if (legalMove(move, player, board)) {
            i++;
            arrayMoves[i]=move;
        }
    arrayMoves[0]=i;
    sortArray(arrayMoves);
    return arrayMoves;
}

int* copyboard(const int * board) {
    int i, * newboard;
    if(!board){
        return NULL;
    }
    newboard = malloc(playboard->size * sizeof(int* ));
    for (i = 0; i < playboard->size; i++) {
        newboard[i] = board[i];
    }
    return newboard;
}

void playMove(int move, int player, int* board, char* type, char** string){
    if(move == -1){ /* Pokud chci hrát pass */
        if(!anyCorrectMove(player, board)){ /* a je to dovoleno */
            reverseTransformInput(move, string);
            addMoveToLogger(&logger, *string);
            free(*string);
            return;
        }
        getmove(type, player, board); /* pass je zakázán */
    } else if(move == 0){ /* neplatný vstup, který nelze převést na tah */
        printf("Invalid move\n");
        getmove(type, player, board);
    } else if(move == -2){ /* ukončení hry */
        printf("The game is over. Final result:\n");
        printboard();
        printToInputFile(&logger, 0);
        ext(0);
    } else if(move == -3){ /* uložení hry */
        printToInputFile(&logger, 0);
        getmove(type, player, board);
    } else if (legalMove(move, player, board)) { /* povolený tah */
        makeMove(move, player, board);
        reverseTransformInput(move, string);
        addMoveToLogger(&logger, *string);
        free(*string);
    } else { /* zakázaný tah */
        printf("Invalid move\n");
        getmove(type, player, board);
    }
}

void getmove(char* type, int player, int* board) {
    int move;
    char *string = NULL;
    move = 0;
    if(!anyCorrectMove(player, board) && ! anyCorrectMove(otherPlayer(player), board)){
        printf("The game is over. Final result:\n");
        printToInputFile(&logger, 0);
        ext(0);
    }
    if(strcmp(type, HUMAN_TYPE) == 0) {
        move = human(player);
    } else {
        move = minimaxStartPoint(player, board);
    }
    playMove(move, player, board, type, &string);
}

int inputPlay(){
    int i,q, player; int* moves;
    if(logger == NULL || logger->capacity <= 0){
        return BLACK;
    }
    moves = malloc(sizeof (int* ) * logger->upper_bar);
    for(i = 0; i < logger->upper_bar; i++){
        moves[i] = transformInput(logger->moves[i]);
    }
    i = 0; player = BLACK; q = logger->upper_bar;
    while(i < q){
        if(legalMove(moves[i], player, playboard->values)){ /* Tah lze provést */
            makeMove(moves[i], player, playboard->values);
        } else if(moves[i] == -1 && !anyCorrectMove(player, playboard->values)) { /* Chce hrát pass, ale není to možné */
            continue;
        }else if(moves[i] == -2){ /* ukončení hry */
            printf("The game is over. Final result:\n");
            printboard();
            printToInputFile(&logger, 0);
            ext(0);
        } else if(moves[i] == -3){ /* uložení hry */
            printToInputFile(&logger, 0);
            player = otherPlayer(player);
        } else { /* neplatný tah*/
                printf("Invalid move!\n");
                free(moves);
                ext(10);
        }
        printboard();
        i++;
        player = otherPlayer(player);
    }
    free(moves);
    return player;
}

