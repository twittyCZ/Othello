#include <limits.h>
/**
 * @file global.h
 * @author twitty
 * @brief Hlavičkový soubor pro potřebné globální proměnné
 * @version 1.0
 * @date 2023-12-31
 */
#ifndef GLOBAL_H
#define GLOBAL_H
/**
 * @brief Maximální delka řádky
 */
#define MAX_LINE_LENGTH 1000
/**
 * @brief Symboly pro rozdělení řádků vstupního souboru
 */
#define DELIMITERS " \t\n],"
/**
 * @brief První defaultní jméno hráče
 */
#define ANNA_NAME "Anna"
/**
 * @brief Druhé defaultní jméno hráče
 */
#define KAREL_NAME "Karel"
/**
 * @brief Typ hráče člověk
 */
#define HUMAN_TYPE "human"
/**
 * @brief Typ hráče minimax
 */
#define MINIMAX_TYPE "minimax"
/**
 * @brief Defaultní x-ová souřadnice levého horního inicializačního kamene
 */
#define DEFAULT_INNITX_BOARD 4
/**
 * @brief Defaultní y-ová souřadnice levého horního inicializačního kamene
 */
#define DEFAULT_INNITY_BOARD 4
/**
 * @brief Defaultní počet řádek hrací desky
 */
#define DEFAULT_ROWS_BOARD 8
/**
 * @brief Defaultní počet sloupců hrací desky
 */
#define DEFAULT_COLS_BOARD 8
/**
 * @brief Token pro načtení vstupních údajů černého hráče
 */
#define PB_TOKEN "-pb"
/**
 * @brief Token pro načtení vstupních údajů bílého hráče
 */
#define PW_TOKEN "-pw"
/**
 * @brief Token pro načtení rozměrů desky
 */
#define SIZE_TOKEN "-size"
/**
 * @brief Token pro načtení pozice inicializačních kamenů
 */
#define INIT_TOKEN "-init"
/**
 * @brief Token pro načtení výstupního souboru
 */
#define OUTPUT_TOKEN "-o"
/**
 * @brief Token pro načtení vstupního souboru
 */
#define INPUT_TOKEN "-i"
/**
 * @brief Token pro načtení tahů ze vstupního soubru
 */
#define GAME_TOKEN "-game"
/**
 * @brief Hodnota znázorňující prázdné pole
 */
#define EMPTY 0
/**
 * @brief Hodnota znázorňující pole obsazené černým hráčem
 */
#define BLACK 1
/**
 * @brief Hodnota znázorňující pole obsazené bílým hráčem
 */
#define WHITE 2
/**
 * @brief Hodnota znázorňující pole mimo hrací desku
 */
#define BORDER 3
/**
 * @brief Nejlepší možný ohodnocení tahu pro minimax
 */
#define WIN (INT_MAX - 1)
/**
 * @brief Nejhorší možný ohodnocení tahu pro minimax
 */
#define LOSS (INT_MIN + 1)
/**
 * @brief Hráč jedna, černý
 */
extern struct player* player1;
/**
 * @brief Hráč dva, bílý
 */
extern struct player* player2;
/**
 * @brief logger k uchovávání informací o učiněných či budoucích tazích
 */
extern struct logger* logger;
/**
 * @brief hrací plocha
 */
extern struct board* playboard;

#endif
