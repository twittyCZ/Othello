#include "structure.h"
/**
 * @file game.h
 * @author twitty
 * @brief Hlavičkový soubor pro herní metody + logger
 * @version 1.0
 * @date 2023-12-31
 */

#ifndef GAME_H
#define GAME_H

/**
 * ----------------------------------------------------------------------------------
 *                                  minimax.c funkce
 * -----------------------------------------------------------------------------------
 */
/**
 * @brief Přístupový bod minimaxu
 * @param player hráč na tahu
 * @param board herní deska
 * @return nejlepší tah
 */
int minimaxStartPoint(int player, int* board);
/**
 * @brief Implementace algoritmu minimax
 * @param player hráč na tahu
 * @param board aktuální podoba hřiště
 * @param depth hloubka stromu
 * @param alpha minimální hodnoa
 * @param beta maximální hodnota
 * @param type typ hráče
 * @return ideální tah
 */
int minimaxAB(int player, int* board, int depth, int alpha, int beta, char* type);
/**
 * @brief Tahy, která udělá minimax pro zlepšení skore
 * @param player hráč na tahu
 * @param board aktuální podoba hřiště
 * @param depth hloubka stromu
 * @param alpha minimální hodnoa
 * @param beta maximální hodnota
 * @param type typ hráče
 * @return jeho nejlepší tah
 */
int maxPlayer(int player, int* board, int depth, int alpha, int beta, char* type);
/**
 * @brief Tahy, která udělá protivník pro zhoršení situace
 * @param player hráč na tahu
 * @param board aktuální podoba hřiště
 * @param depth hloubka stromu
 * @param alpha minimální hodnoa
 * @param beta maximální hodnota
 * @param type typ hráče
 * @return protivníkův nejlepší tah
 */
int minPlayer(int player, int* board, int depth, int alpha, int beta, char* type);
/**
 * @brief Spočítání políček obou hráčů
 * @param player Hráč z jehož pohledu se díváme na hodnoty hráčů
 * @param board aktuální stav hry
 * @return políčka zadaného hráče mínus políčka druhého hráče
 */
int weightMove(int player, const int* board);
/**
 * Ohodonocení políček na základě vzdálenosti od středu, na kraji jsou nejvýhodnější políčka
 * Jedná se o nevyužitou metodu, jde o implementaci nápadu z dokumenteace
 * @return ohodnocená herní deska
 */
int* loadBoardByPositionNumbers();
/**
 * @brief Seřadí zadané pole vzestupně dle hodnot políčka,tím se docílí preference levých tahů u minimaxu
 * @param arrayMoves řazené pole
 */
void sortArray(int* arrayMoves);
/**
 * @brief Vyhodnocení hry, pokud není možnost dalšího tahu
 * @param player hráč na tahu
 * @param newScore pointer na skóre
 * @param newBoard hrací deska
 * @param win hodnota pokud vyhrajeme
 * @param loss hodnota pokud prohrajeme
 * @return 0 pokud již není další hráč, jinak 1
 */
int noNextPlayer(int player, int* newScore, int* newBoard, int win, int loss);

/**
 * ----------------------------------------------------------------------------------
 *                                  game.c funkce
 * -----------------------------------------------------------------------------------
 */
/**
 * @brie Určení, jestli je tah v souladu s pravidly
 * @param move zamýšlený tah
 * @param player hráč na tahu
 * @param board hrací deska
 * @return 1 pokud v přádku, jinak 0
 */
int legalMove(int move, int player,int* board);
/**
 * @brief Učinění zamýšleného tahu
 * @param move zamýšlený tah
 * @param player hráč na tahu
 * @param board hrací deska
 */
void makeMove(int move, int player, int* board);
/**
 * @brief Zjistí, jestli je možný nějaký tah
 * @param player hráč na tahu
 * @param board hrací deska
 * @return 0 pokud není žádný možný tah, 1 pokud je možný tah
 */
int anyCorrectMove(int player, int* board);
/**
 * @brief Vstupní funkce hry
 */
void othello();
/**
 * @brief Na základě symbolu hráče vrátí symbol druhého hráče
 * @param player zadaný symbol hráče
 * @return symbol druhého hráče
 */
int otherPlayer(int player);
/**
 * @brief Nalezení políčka, z kterého lze táhnout na dané políčko
 * @param move cílové políčko
 * @param player hráč, který táhne
 * @param board herní plocha
 * @param direction směr, kterým táhne hráč
 * @return políčko nebo 0, pokud nelze táhnout
 */
int findFinalDestination(int move, int player, int* board, int direction);
/**
 * @brief Zjištění, jestli daným směrem lze táhnout na cílové políčko
 * @param move cílové políčko
 * @param player hráč, který táhne
 * @param board herní plocha
 * @param direction směr, kterým táhne hráč
 * @return číslo políčka nebo 0, pokud nelze táhnout
 */
int tryJump(int move, int player, int* board, int direction);
/**
 * @brief Zjištění, jestli nejsme tahem mimo rozsah hrací desky
 * @param move zkoumaný tah
 * @return 1 pokud ok, jinak 0
 */
int validMove(int move);
/**
 * @brief provedení tahu
 * @param move tah
 * @param player hráč, který táhne
 * @param board herní plocha
 * @param direction směr, kterým táhne hráč
 */
int makeJump(int move, int player, int* board, int direction);
/**
 * @brief Určení, kdo další je na tahu
 * @param board stav hry
 * @param previousplayer předchozí hráč
 * @return symbol daného hráče
 */
int nextPlayer(int* board, int previousplayer);
/**
 * @brief vytvoření pole všech validních tahů v dané situaci
 * @param player hrající hráč
 * @param board  hrací deska
 * @return pole možných tahů
 */
int* validMoves(int player, int* board);
/**
 * @brief Vytvoření nového cvičného hřiště
 * @param board staré hřiště
 * @return nové hřiště
 */
int* copyboard(const int* board);
/**
 * @brief Střídání hráčů na tahu nebo ukončení hry, pokud takový tah není
 * @param type typ hráče
 * @param player hráč
 * @param board hrací deska
 */
void getmove(char* type, int player, int* board);
/**
 * @brief Hraní se vstupního souboru
 * @return symbol hráče, který je na tahu
 */
int inputPlay();
/**
 * @brief Vyhodnocení požadovaného tahu, jestli ho lze provést a jak
 * @param move chtěný tah
 * @param player symbol hráče na tahu
 * @param board herní deska
 * @param type typ hráče
 * @param string ukazatel na string, pro vložení do loggeru
 */
void playMove(int move, int player, int* board, char* type, char** string);

/**
 * ----------------------------------------------------------------------------------
 *                                  human.c funkce
 * -----------------------------------------------------------------------------------
 */
/**
 * @brief Funkce pro zadání vstupu lidským hráčem
 * @param player hráč, který je na tahu
 * @return číslo políčka, na který chce hráč táhnout
 */
int human(int player);
/**
 * @brief pokus o transformaci vstupu od uživatele na číslo políčka
 * @param string políčko, na který chce uživatel táhnout ve formátu X_Y
 * @return 0 pokud špatný vstup, jinak číslo políčka
 */
int transformInput(char string[]);


/**
 * ----------------------------------------------------------------------------------
 *                                  logger.c funkce
 * -----------------------------------------------------------------------------------
 */
/**
 * @brief Funkce k převedení čísla políčka na hodnotu ve tvaru: X_Y ve 2D poli
 * @param number očíslování políček jako řada v 1D poli
 * @param myMemory ukazatel na paměť, do které chceme daný string uložit
 * @return tvar X_Y
 */
void reverseTransformInput(int number, char** myMemory);
/**
 * @brief Metoda k zapsání dat do výstupního souboru, je-li dán
 * @param pLogger ukazatel na logger, ze kterého vypisujeme data
 * @param end 1 pokud se jedná o ukončovací výpis, 0 pokud o něco jiného
 */
void printToInputFile(struct logger** pLogger, int end);
/**
 * @brief Metoda k přidání provedeného tahu do Loggeru
 * @param pLogger ukazatel na logger, kam vkládáme tahy
 * @param newData data, která jsou přidávána, ve formátu: X_Y
 */
void addMoveToLogger(struct logger** pLogger, const char* newData);
/**
 * @brief Metoda pro vypsání parametrů, s kterými je hrána hra, do výstupního souboru
 */
void printParameters();
/**
 * @brief Přidání načtených slov ze vstupního souboru do loggeru
 * @param pLogger logger, kam vložíme informace
 * @param file načtená slova
 * @param gameIndex index, od kterého začánají tahy
 * @param numberOfWords počet slov v souboru
 */
void addWordsToLogger(struct logger** pLogger, const char** file, int gameIndex, int numberOfWords);
#endif
