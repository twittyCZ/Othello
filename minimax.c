#include <stdlib.h>
#include "stdio.h"
#include "game.h"
#include "structure.h"
#include "global.h"

int minimaxStartPoint(int player, int * board) {
    int move;
    char *string;
    if(!board){
        return 0;
    }
    string = NULL;
    if(player == BLACK){
        move = (minimaxAB(player, board, player1->depth, LOSS, WIN, player1->type));
    } else {
        move = (minimaxAB(player, board, player2->depth, LOSS, WIN, player2->type));
    }
    reverseTransformInput(move, &string);
    printf("(%s:%s)> %s\n", player == BLACK ? player1->name : player2->name, player == BLACK ? player1->type : player2->type, string);
    free(string);
    return move;
}

int minimaxAB (int player, int * board, int depth, int alpha, int beta, char* type) {
    int i, max, newScore, bestMove, * arrayMoves, * newBoard;
    if(!player || !board || depth < 0){
        return 0;
    }
    arrayMoves = validMoves(player, board); /* vytvoří všech pole validních tahů*/
    bestMove = -1; max = LOSS - 1;
    for (i = 1; i <= arrayMoves[0]; i++) {
        newBoard = copyboard(board); /* hrací deska pro daný tah */
        makeMove(arrayMoves[i], player, newBoard);
        if(noNextPlayer(player, &newScore, newBoard, WIN, LOSS) != 0 ){
            newScore = minPlayer(player, newBoard, depth - 1, alpha, beta, type);
        }
        if (newScore > max) { /* uchování nejlepšího tahu */
            max = newScore;
            bestMove = arrayMoves[i];
        }
        if (max >= beta) { /* beta řez */
           free(newBoard);
           break;
        }
        if (max > alpha) { /* alfa řez */
            alpha = max;
        }
        free(newBoard);
    }
    free(arrayMoves);
    return (bestMove);
}

int maxPlayer(int player, int *board, int depth, int alpha, int beta, char* type) {
    int i, max, newScore, * arrayMoves, * newBoard;
    if(!player || !board || depth < 0){
        return 0;
    }
    if (depth == 0){ /*Pokud uz nemame k dispozici urovne pro spekulaci, vratime ohodnocenou desku*/
        return weightMove(player, board);
    }
    newScore = 0;
    arrayMoves = validMoves(player, board); /*vytvorime pole validnich tahu*/
    max = LOSS; /* hodnota jen ilustrační, důležité je aby byla větší než hodnota max v minimaxu! */
    for (i = 1; i <= arrayMoves[0]; i++) {
        newBoard = copyboard(board);
        makeMove(arrayMoves[i], player, newBoard);
        if(noNextPlayer(player, &newScore, newBoard, WIN / 2, 0) != 0){
            newScore = minPlayer(player, newBoard, depth - 1, alpha, beta, type);
        }
        if (newScore > max){ /* udržení nejlepšího dosaženého skore */
            max = newScore;
        }
        if (max >= beta) { /* dale uz neprohledavej */
            free(newBoard);
            break;
        }
        if (max > alpha) { /* posunutí dolní meze */
            alpha = max;
        }
        free(newBoard);
    }
    free(arrayMoves);
    return (max);
}

int minPlayer(int player, int* board, int depth, int alpha, int beta, char* type) {
    int i, min, newScore, * arrayMoves, * newBoard;
    if(!player || !board || depth < 0){
        return 0;
    } /* protivnikovy tahy */
    if (depth == 0) {
        return weightMove(player, board);
    }
    arrayMoves = validMoves(otherPlayer(player), board);
    min = WIN + 1; /* protivnikuv nejlepsi tah, hledame nejnizsi hodnotu */
    for (i = 1; i <= arrayMoves[0]; i++) {
        newBoard = copyboard(board);
        makeMove(arrayMoves[i], otherPlayer(player), newBoard);
        if(noNextPlayer(player, &newScore, newBoard, WIN / 2, 0) != 0){
            newScore = maxPlayer(player, newBoard, depth - 1, alpha, beta, type);
        }
        if (newScore < min) { /* udrzeni nejnizsi hodnoty */
            min = newScore;
        }
        if (min <= alpha) { /* máme uz lepsi (mensi) odpoved, zde jiz nemusime prohledavat */
            free(newBoard);
            break;
        }
        if (min < beta) { /* posunutí horní meze */
            beta = min;
        }
        free(newBoard);
    }
    free(arrayMoves);
    return (min);
}

int noNextPlayer(int player, int* newScore, int* newBoard, int win, int loss){
    int nextPlay;
    if(!newBoard){
        return 0;
    }
    nextPlay = nextPlayer(newBoard, player);
    if (nextPlay == 0) { /* Pokud již není validní tah */
        (*newScore) = weightMove(player, newBoard);
        if ((*newScore) > 0) (*newScore) = win;
        if ((*newScore) < 0) (*newScore) = loss;
    }
    return nextPlay;
}

int weightMove (const int player, const int* board) {
    int i, myPoints, opponentsPoints, opponent;
    if(!player || !board){
        return 0;
    }
    myPoints = 0; opponentsPoints = 0;
    opponent = otherPlayer(player);
    for (i = 0; i < playboard->size; i++) {
        if (board[i] == player) {
            myPoints++;
        } if (board[i] == opponent){
            opponentsPoints++;
        }
    }
    return myPoints-opponentsPoints;
    /*weightedBoard = loadBoardByPositionNumbers();*/ /* Implementace návrhu z dokumentace  */
}

int* loadBoardByPositionNumbers(){
    int i,j, distanceToCenterX, distanceToCenterY, distanceToCenter;
    int row = playboard->rows;
    int col = playboard->cols;
    int *pole;
    pole = malloc(row * col * sizeof(int));
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            distanceToCenterX = abs(i - row );
            distanceToCenterY = abs(j - col );
            if(i > row/2){
                distanceToCenterX = i;
            }
            if(j > col/2){
                distanceToCenterY = j;
            }
            distanceToCenter = distanceToCenterX + distanceToCenterY;
            /*  Hodnota na políčku je rovna vzdálenosti od středu*/
            pole[i * col + j] = distanceToCenter;
            if (i == 0 || i == row - 1 || j == 0 || j == col - 1) {
                pole[i*col + j] = -1;
            }
        }
    }
    return pole;
}