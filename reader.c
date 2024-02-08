#include <stdlib.h>
#include <string.h>
#include "stdio.h"
#include "game.h"
#include "structure.h"
#include "reader.h"
#include "global.h"

void containsSize(int argc, const char** argv, int loadFromFile){
    int i;
    if(!argv || !*argv || argc < 0){
        return;
    }
    for(i=1; i<argc; i++){
        if(strcmp(argv[i],SIZE_TOKEN) == 0){
            prepareSize(argv, i);
            return;
        }
    }
    if(loadFromFile == 1){
        createBoardInt(&playboard, DEFAULT_ROWS_BOARD, DEFAULT_COLS_BOARD);
    } else {
        if(playboard == NULL){
            createBoardInt(&playboard, DEFAULT_ROWS_BOARD, DEFAULT_COLS_BOARD);
        }
    }
}

int lastTokenIndex(int argc, char* argv[]){
    int i, number;
    if(argc < 0 || !argv || !*argv){
        return 0;
    }
    number = 0;
    for (i=0; i<argc; i++){
        if(isNotToken(argv[i]) == 0){
            number = i;
        }
    }
    return number;
}

void loadDefaultInformation(){
    if(player1 == NULL && player2 == NULL){
        playerAllocate(&player1, HUMAN_TYPE, ANNA_NAME, 0, BLACK);
        playerAllocate(&player2, HUMAN_TYPE, KAREL_NAME, 0, WHITE);
    } else if(player1 == NULL){
        if(strcmp(player2->name,KAREL_NAME) == 0){
            playerAllocate(&player1, HUMAN_TYPE, ANNA_NAME, 0, BLACK);
        } else if(strcmp(player2->name,ANNA_NAME) == 0){
            playerAllocate(&player1, HUMAN_TYPE, KAREL_NAME, 0, BLACK);
        } else {
            playerAllocate(&player1, HUMAN_TYPE, ANNA_NAME, 0, BLACK);
        }
    } else if(player2 == NULL){
        if(strcmp(player1->name,KAREL_NAME) == 0){
            playerAllocate(&player2, HUMAN_TYPE, ANNA_NAME, 0, WHITE);
        } else if(strcmp(player1->name,ANNA_NAME) == 0){
            playerAllocate(&player2, HUMAN_TYPE, KAREL_NAME, 0, WHITE);
        } else {
            playerAllocate(&player2, HUMAN_TYPE, ANNA_NAME, 0, WHITE);
        }
    }
    if(!playboard) {
        createBoardInt(&playboard, DEFAULT_ROWS_BOARD, DEFAULT_COLS_BOARD);
        initializeBoardInt(&playboard, DEFAULT_INNITX_BOARD, DEFAULT_INNITY_BOARD);
    }
}

void load(int argc, const char* argv[], int fromFile) {
    int i;
    if(!argv || argc < 2){
        return;
    }
    prepareInputFile(argv, containsInputFile(argv,argc));
    containsSize(argc, argv, fromFile);
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], PB_TOKEN) == 0) {
            preparePlayer(&player1, argv, i, BLACK);
        } else if (strcmp(argv[i], PW_TOKEN) == 0) {
            preparePlayer(&player2, argv, i, WHITE);
        } else if (strcmp(argv[i], SIZE_TOKEN) == 0) {
            prepareSize(argv, i);
        } else if (strcmp(argv[i], INIT_TOKEN) == 0) {
            prepareInitBoard(argv, i);
        } else if (strcmp(argv[i], OUTPUT_TOKEN) == 0) {
            prepareOutputFile(argv, i);
        }
    }
}

int containsInputFile(const char** string, int numberOfParameters){
    int i;
    if(!string || !*string || numberOfParameters < 1){
    }
    for(i = 0; i < numberOfParameters; i++){
        if(strcmp(string[i], INPUT_TOKEN) == 0){
            return i;
        }
    }
    return 0;
}

void checkNumberOfParameters(const char** string, int index, int maxNumber){
    int indexStart, indexEnd;
    if(!string){
        return;
    }
    indexStart = index; indexEnd = index;
    while(isNotToken(string[index + 1])){
        index++;
        indexEnd = index;
        if(index == maxNumber + indexStart){
            break;
        }
    }
    if(indexEnd - indexStart > maxNumber){
        printf("Invalid player description!\n");
        ext(1);
    }
}

void prepareInitBoard(const char** string, int index){
    checkNumberOfParameters(string, index, 2);
    initializeBoard(&playboard, string[index+1], string[index+2]);
}

void prepareSize(const char** string, int index){
    checkNumberOfParameters(string, index, 2);
    createBoard(&playboard, string[index+1], string[index+2]);
}

const char* preparePlayerType(const char* string) {
    if(!string){
        printf("Invalid player description!\n");
        ext(1);
    }
    if(strcmp(string,HUMAN_TYPE) == 0){
        return string;
    } else if(strcmp(string,MINIMAX_TYPE) == 0){
        return string;
    } else {
        printf("Invalid player description!\n");
        ext(1);
    }
    return NULL;
}

void prepareOutputFile(const char** string, int index){
    if(!string || index < 1){
        printf("Invalid output Invalid output file destination!\n");
        return;
    }

    checkNumberOfParameters(string, index, 1);
    openOutputFile(string[index + 1]);
}

void prepareInputFile(const char** string, int index){
    if(!string || index < 1){
        return;
    }
    checkNumberOfParameters(string, index, 1);
    openInputFile(string[index + 1]);
}

void openOutputFile(const char* string) {
    FILE *outputFile;
    if(!string){
        printf("Invalid output file destination!\n");
        ext(4);
    }
    if(!isTxtFormat(string)){
        printf("Invalid output file destination!\n");
        ext(4);;
    }
    outputFile = fopen(string, "w");
    if(!outputFile){
        printf("Invalid output file destination!\n");
        ext(4);
    }
    loggerSetOuputFile(&logger, string);
    fclose(outputFile);
}
int isTxtFormat(const char* string){
    size_t length;
    if(!string){
        return 0;
    }
    length = strlen(string);
    if (length >= 4 && strcmp(string + length - 4, ".txt") == 0) {
        return 1;
    } else {
        return 0;
    }
}



void countWordsAndLines(FILE* inputFile, int* numberOfWords, int* numberOfLines){
    char line[MAX_LINE_LENGTH];
    (*numberOfWords) = 0;
    (*numberOfLines) = 0;

    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        (*numberOfLines)++;
    }
}

void addFirstWord(char*** file, int* numberOfWords){
    char *firstWord = "othello.exe";
    (*file) = realloc((*file), ((*numberOfWords) + 1) * sizeof(char *));
    (*file)[(*numberOfWords)] = my_strdup(firstWord);
    (*numberOfWords)++;
}

void addWordToFile(char*** file, int* numberOfWords, char* token){
    int i, len;
    len = strlen(token);
    (*file) = realloc((*file), ((*numberOfWords) + 1) * sizeof(char *));
    (*file)[(*numberOfWords)] = malloc(len + 1);
    for (i = 0; i < len; i++) {
        if (token[i] == '[') {
            (*file)[(*numberOfWords)][i] = '-';
        } else {
            (*file)[(*numberOfWords)][i] = token[i];
        }
    }
    (*file)[(*numberOfWords)][len] = '\0';
    (*numberOfWords)++;
}


void readLinesAndTokenize(FILE* inputFile, char*** file, int* numberOfWords){
    char line[MAX_LINE_LENGTH];
    char *token;
    /* Přečtení obsahu souboru řádek po řádku */
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        /* Tokenizace řádku na slova */
        token = strtok(line, DELIMITERS);
        while (token != NULL) {
            addWordToFile(file, numberOfWords, token);
            token = strtok(NULL, DELIMITERS);
        }
    }
}

void readFile(const char* fileName, char*** file, int* numberOfWords, int* numberOfLines){
    FILE *inputFile;

    /* Otevření souboru pro čtení */
    inputFile = fopen(fileName, "r");
    if (!inputFile) {
        printf("Invalid input file!\n");
        exit(5);
    }
    countWordsAndLines(inputFile, numberOfWords, numberOfLines);
    rewind(inputFile); /* Znovuotevření souboru pro přečtení */
    addFirstWord(file, numberOfWords);
    readLinesAndTokenize(inputFile, file, numberOfWords);
    fclose(inputFile);
}

int loadMovesFromFile(const char** file, int* numberOfMoves, int numberOfWords){
    int i, gameIndex;
    if(file == NULL || numberOfWords == -1 || numberOfMoves == 0){
        return 0;
    }
    gameIndex = -1;
    for (i = 0; i < numberOfWords; i++) {
        if (strcmp(file[i], GAME_TOKEN) == 0) {
            gameIndex = i;
            (*numberOfMoves) = numberOfWords - gameIndex - 1;
        }
    }
    return gameIndex;
}

void openInputFile(const char* string) {
    char **file = NULL;
    int gameIndex, numberOfMoves, numberOfWords, lastToken, numberOfLines;
    if (!string) {
        printf("Invalid input file!\n");
        ext(5);
    }
    if (!isTxtFormat(string)) {
        printf("Invalid input file!\n");
        ext(5);
    }
    numberOfMoves = -1; numberOfMoves = 0, lastToken = 0, numberOfLines = 0;
    readFile(string, &file, &numberOfWords, &numberOfLines);
    gameIndex = loadMovesFromFile((const char**) file, &numberOfMoves, numberOfWords);
    load(numberOfWords, (const char **) file, 1);
    lastToken = lastTokenIndex(numberOfWords,file);
    if(numberOfMoves > 0 && gameIndex != -1){
        loggerAllocate(&logger, numberOfMoves);
        addWordsToLogger(&logger, (const char **) file, gameIndex, numberOfWords);
    }
    freeInputLoad(&file, gameIndex, numberOfWords, numberOfMoves);
    validateInputFile(gameIndex, lastToken, numberOfLines);
}

void validateInputFile(int gameIndex, int lastToken, int numberOfLines){
    if(gameIndex == -1 &&  lastToken + 3 <= numberOfLines){
        printf("Invalid input file!\n");
        ext(5);
    }
}

void freeInputLoad(char*** file, int gameIndex, int numberOfWords, int numberOfMoves){
    int i;
    if(gameIndex > -1){
    free((*file)[gameIndex]);
    }
    if(numberOfMoves != -1 && gameIndex != -1) {
        for (i = gameIndex + 1; i < numberOfWords; i++) {
            free((*file)[i]);
        }
    }
    for (i = 0; i < gameIndex; i++) {
        free((*file)[i]);
    } /* Uvolnění paměti pro každé slovo */

    free((*file));
}

int isNotToken(const char* string) {
    char *arrayOfKeyWords[] = {PB_TOKEN, PW_TOKEN, SIZE_TOKEN, INIT_TOKEN, INPUT_TOKEN, OUTPUT_TOKEN, GAME_TOKEN};
    int numOfKeywords, i;
    if (!string || !string[0]) {
        return 0;
    }
    numOfKeywords = sizeof(arrayOfKeyWords) / sizeof(arrayOfKeyWords[0]);
    for (i = 0; i < numOfKeywords; i++) {
        if (strcmp(arrayOfKeyWords[i], string) == 0) {
            return 0;
        }
    }
    return 1;  /*Řetězec nebyl nalezen*/
}

int playerNameUsed(const char* name, int symbol){
    if(!name || symbol < 0){
        return 0;
    }
    if(player1 && player1->symbol == symbol && (strcmp(player1->name, name) == 0)){
        return 1;
    }
    if(player2 && player2->symbol == symbol && (strcmp(player2->name, name) == 0)){
        return 1;
    }
    return 0;
}


int findOutNumberOfParameters(const char** string, int index, int maxNumber){
    int indexStart, indexEnd;
    indexEnd = index; indexStart = index;
    while(isNotToken(string[index])){
        indexEnd = index;
        if(indexEnd - indexStart >= maxNumber){
            return -1;
        }
        index++;
    }
    indexEnd = index;
    return indexEnd - indexStart;
}

void onePlayerParameter(struct player** player, const char* type,int symbol){
    int depth;
    if(!player){
        return;
    }
    depth = 3;
    if(playerNameUsed(ANNA_NAME, symbol)){
        playerAllocate(player, type, KAREL_NAME, depth, symbol);
    } else if(playerNameUsed(KAREL_NAME, symbol)){
        playerAllocate(player, type, ANNA_NAME, depth, symbol);
    } else {
        playerAllocate(player ,type, ANNA_NAME, depth, symbol);
    }
}

void threePlayerParameter(struct player** player, const char** string, int index, const char* type, int symbol){
    int depth;
    if(!string || !player){
        return;
    }
    depth = isNumber(string[index + 3]);
    if(player1){  /*pokud je již první hráč zadán, zkontroluj jestli druhý nemá stejné jméno*/
        if(!strcmp(player1->name, string[index+2])){
            printf("Invalid player description!\n");
            ext(1);
        }
    }
    if(!strcmp(string[index + 3], ANNA_NAME)){
    } else if (!strcmp(string[index + 3], KAREL_NAME)){
    }
    playerAllocate(player, type, string[index + 2], depth, symbol);
}

void twoPlayerParameter(struct player** player, const char** string, int index, const char* type, int symbol){
    int depth;
    if(!string || !player){
        return;
    }
    if((depth = isItNumber(string[index + 2])) == -1){
        depth = 3;
        if(player1){
            if(!strcmp(player1->name, string[index+2])){
                printf("Invalid player description!\n");
                ext(1);
            }
        }
        playerAllocate(player, type, string[index + 2], depth, symbol);
    } else {
        if(playerNameUsed(ANNA_NAME,symbol)){
            playerAllocate(player, type, KAREL_NAME, depth, symbol);
        } else if(playerNameUsed(ANNA_NAME,symbol)){
            playerAllocate(player, type, ANNA_NAME, depth, symbol);
        } else {
            playerAllocate(player, type, ANNA_NAME, depth, symbol);
        }
    }
}

void preparePlayer(struct player** player, const char** string, int index, int symbol) {
    int number;
    const char *type;
    if (!string || index < 0) {
        printf("Invalid player description!\n");
        ext(1);
    }
    number = findOutNumberOfParameters((const char **) string, index + 1, 3);
    if (number <= 0) {
        printf("Invalid player description!\n");
        ext(1);
    }
    type = preparePlayerType(string[index + 1]);
    if (number == 1) {  /*vyplněn jen typ*/
        onePlayerParameter(player, (const char *) type, symbol);
    } else if (number == 3) {  /*-> prvně zkontroluj jestli je to třetí číslo, když ano tak vše ok, když ne, tak vše špatně a error*/
        threePlayerParameter(player, (const char **) string, index, (const char *) type, symbol);
    } else if (number == 2) {  /*vyplněno jen jedno*/
        twoPlayerParameter(player, (const char **) string, index, (const char *) type, symbol);
    }
}

int isItNumber(const char* string) {
    char *endptr;
    int depth;
    depth = strtol(string, &endptr, 0);
    if (*endptr != '\0') {
        return -1;
    } else return depth;
}

int isNumber(const char *string) {
    char *endptr;
    int depth;
    depth = strtol(string, &endptr,0);
    if (*endptr != '\0') {
        printf("Invalid player description!\n");
        ext(1);
    }
    return depth;
}

char *my_strdup(const char* src) {
    size_t len;
    char *dst;
    if (src == NULL) {
        return NULL;
    }
    len = strlen(src);
    dst = (char *)malloc(len + 1);
    if (dst == NULL) {
        return NULL;
    }
    strcpy(dst, src);
    return dst;
}

char *my_strtok_r(char* str, const char* delim, char** saveptr){
    char *token;
    if (str == NULL) {
        str = *saveptr;
    }
    str += strspn(str, delim);
    if (*str == '\0'){
        return NULL;
    }
    token = str;
    str += strcspn(token, delim);
    if (*str != '\0'){
        *str = '\0';
        *saveptr = str + 1;
    } else {
        *saveptr = NULL;
    }
    return token;
}

int getNumberOfWords(int numberOfParameters, const char* parameters[]){
    int result, i;
    size_t j;
    if(!parameters || !*parameters || !numberOfParameters){
        return 0;
    }
    result = 1; /* První argument je vždy název souboru */
    for (i = 1; i < numberOfParameters; i++) {
        result++; /* Každé políčko obsahuje alespoň jedno slovo */
        for (j = 0; j < strlen(parameters[i]); j++) {
            if (parameters[i][j] == ',') { /* Slova jsou odděleny čárkami */
                result++;
            }
        }
    }
    return result;
}

void fillParameters(char** words, int numberOfWords, char *parameters[], int numberOfParameters){
    char* token;
    int i, j;
    if(!parameters || !*parameters || !numberOfParameters || !numberOfWords){
        return;
    }
    words[0] = "othello.exe";
    j = 1;
    for (i = 1; i < numberOfParameters; i++) {
        token = strtok(parameters[i], ","); /* Rozdělení dle čárky a vložení do paměti */
        words[j] = token;
        while(token != NULL){
            j++;
            token = strtok(NULL, ",");
            if(token == NULL){
                break;
            }
            words[j] = token;
        }
    }
}

void loadStartPoint(int numberOfParameters, char* parameters[]){
    int numberOfWords; char *words[MAX_LINE_LENGTH] = {NULL};
    if (!parameters || !*parameters || !numberOfParameters){
        return;
    }
    if(numberOfParameters < 2){ /* Příkazová řádka obsahuje jen název souboru */
    }
    numberOfWords = getNumberOfWords(numberOfParameters, (const char**) parameters);
    fillParameters(words, numberOfWords, parameters,numberOfParameters);
    load(numberOfWords, (const char **) words, 0);
    loadDefaultInformation();
    initDirections(&playboard);
}

int main(int argv, char* argc[]){
    loadStartPoint(argv, argc);
    othello();
    ext(0);
    return 0;
}
