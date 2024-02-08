#include <stdlib.h>
#include <string.h>
#include "stdio.h"
#include "game.h"
#include "structure.h"
#include "global.h"
#include "reader.h"

int human(int player) {
    char input[100];
    int move;
    if(player != BLACK && player != WHITE){
        return -1;
    }
    printf("(%s:%s)>", player == BLACK ? player1->name : player2->name, player == BLACK ? player1->type : player2->type);
    scanf("%s", input);
    move = transformInput(input);
    return move;
}

int transformInput(char string[]) {
    int r, c, result;
    char* ptr, * endptr;
    char str_copy[100] = {0};
    if(!string){
        return 0;
    }
    endptr = NULL, ptr = NULL;
    to_lowercase(string);
    if((strcmp(string, "pass") == 0) || (strcmp(string, "pass\n") == 0)){
        return -1;
    } if((strcmp(string, "quit") == 0) || (strcmp(string, "quit\n") == 0)){
        return -2;
    } if((strcmp(string, "save") == 0) || (strcmp(string, "save\n") == 0)) {
        return -3;
    } if(strchr(string, '_') == NULL){
        printf("Invalid move!\n");
        return 0;
    }
    strcpy(str_copy, string);
    my_strtok_r(str_copy, "_", &ptr);
    r = strtol(str_copy, &endptr, 10);
    if(endptr == str_copy){
        printf("Invalid move!\n");
        return 0;
    }
    c = strtol(ptr, &endptr, 10);
    if(endptr == ptr){
        printf("Invalid move!\n");
        return 0;
    } if(c <= 0 || r <= 0){
        printf("Invalid move!\n");
        return 0;
    }
    result = playboard->cols * r + c;
    return result;
}