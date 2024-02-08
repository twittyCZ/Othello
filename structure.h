/**
 * @file structure.h
 * @author twitty
 * @brief Hlavičkový soubor pro práci se strukturami
 * @version 1.0
 * @date 2023-12-31
 */
#ifndef STRUCTURE_H
#define STRUCTURE_H
/**
 * @brief Struktura reprezentující herní desky
 */
struct board {
    int rows; /*!< Počet řádek herní desky, včetně ohraničujících  */
    int cols; /*!< Počet sloupců herní desky, včetně ohraničujících */
    int size; /*!< Počet políček herní desky, včetně ohraničujících */
    int* values; /*!< Hodnoty jednotlivých políček */
    int initX; /*!< Místo inicializačního kamene -> pravý horní, X souřadnice */
    int initY; /*!< Místo inicializačního kamene -> pravý horní, Y souřadnice */
    int Q; /*!< Konstanta pro přepočet mezi 2D polem, který vidí uživatel a 1D polem, ve kterým je hra psaná */
    int allDirections[8]; /*!< Pole všech směrů pohybu */
};
/**
 * @brief Alokace paměti pro herní desku
 * @param board allokované hrací pole
 * @param rows počet herních řádek
 * @param cols počet herních sloupců
 * @return vrací alokovanou strukturu nebo NULL
 */
void boardAllocate(struct board** board, int rows, int cols);
/**
 * @brief Inicializace některých parametrů struktury
 * @param board inicializovaní hrací pole
 * @param rows počet herních řádek
 * @param cols počet herních sloupců
 * @return 1 pokud se povedlo, 0 pokud se nepovedlo
 */
int boardInit(struct board** board, int rows, int cols);
/**
 * @brief Metoda pro dealokaci parametrů struktury
 * @param board deinicializované hrací pole
 */
void boardDeinit(struct board** board);
/**
 * @brief Vložení inicializačních hodnot do hrací desky na začátku hry
 * @param board hrací deska
 */
void fillBoardByInnitValues(struct board** board);
/**
 * @brief Dealokace paměti
 * @param board deska k dealokaci
 */
void boardFree(struct board** board);
/**
 * @brief Uložení hodnot pro výchozí postavení kamenů
 * @param board hrací deska
 * @param stringX řádka pravého horního kamene
 * @param stringY sloupec pravého horního kamene
 * @return 1 pokud se povedlo, jinak 0
 */
int initializeBoard(struct board** board, const char* stringX, const char* stringY);
/**
 * @brief Přetížená metoda pro initializeBoard
 * @param board hrací deska
 * @param x rádka pravého horního kamene
 * @param y sloupec pravého horního kamene
 * @return 1 pokud se povedlo inicializovat, jinak 0.
 */
int initializeBoardInt(struct board** board, int x, int y);
/**
 * @brief Naplnění hodnot pro všechny možné směry
 * @param board Inicializuje možné tahy v zadané hrací desce
 */
void initDirections(struct board** board);
/**
 * @brief Vstupní bod k vytvoření, alokaci a inicializaci hrací desky
 * @param board hrací deska
 * @param row počet řádek
 * @param col počet sloupců
 */
void createBoardInt(struct board** board, int row, int col);
/**
* @brief Vstupní bod k vytvoření, alokaci a inicializaci hrací desky
* @param board hrací deska
* @param rowChar počet řádek
* @param colChar počet sloupců
*/
void createBoard(struct board** board, const char* rowChar, const char* colChar);


/**
 * @brief Logger pro uchování informací o tazích, minulých i plánovaných
 */
struct logger {
    int capacity; /*!< Počet prvků v loggeru */
    int upper_bar;  /*!< Ukazatel na poslední prvek, na obsazené místo (včetně) */
    int bottom_bar;  /*!< Ukazatel na první prvek, na ještě nevytištěné (včetně) */
    char** moves;  /*!< Pole buněk obsahující tah na pole ve formátu: X_Y */
    const char* fileOutputName; /*!< Jméno výstupního souboru */
};
/**
 * @brief Allokace paměti pro strukturu loggeru
 * @param pocetTahu kolik buněk budeme alokovat
 * @param logg alokovaný logger
 * @return strukturu loggeru, nebo NULL
 */
void loggerAllocate(struct logger** logg, int pocetTahu);
/**
 * @brief Inicializace parametrů struktury
 * @param pocetTahu kolik buněk budeme alokovat
 * @param logg inicializovaný logger
 * @return 1 pokud se povedlo, jinak 0
 */
int loggerInit(struct logger** logg, int pocetTahu);
/**
 * @brief Deinicializace parametrů
 * @param logg deinicializovaný logger
 */
void logger_deinit(struct logger** logg);
/**
 * @brief Dealokace paměti
 * @param logg dealokovaný logger
 */
void loggerFree(struct logger** logg);
/**
 * Funkce pro vypsání prvku ze struktury => posunutí dolníhu ukazovatele
 * @param logg logger z kterého vypisujeme prvky
 * @return vrací první ještě nevypsaný prvek, jinak NULL
 */
char* logger_pop(struct logger** logg);
/**
 * @brief Funkce pro přidání prvku do struktury
 * @param string přidávaný prvek, ve formátu: X_Y
 * @param logg logger, kam chceme vložit prvek
 */
void loggerAdd(struct logger** logg, const char* string);
/**
 * Zvětšení pole hodnot, pokud je již zaplněno
 */
void loggerResize(struct logger** logg);
/**
 * @brief Vložení jména vstupního souboru
 * @param logg logger, kam se vkládají informace
 * @param fileName vkládané výstupního jméno souboru
 */
void loggerSetOuputFile(struct logger** logg, const char* fileName);


/**
 * @brief Struktura reprezentující jednoho hráče
 */
struct player {
    char *type; /*!< Typ hráče human/minimax */
    char *name; /*!< Jméno hráče */
    int depth;  /*!< Hloubka stromu pro minimax */
    int symbol; /*!< Symbol hráče, 1 = černý, 2 = bílý*/
};
/**
 * @brief Změna hodnt u již alokovaného hráče
 * @param pPlayer ukazatel na hráče
 * @param type typ hráče
 * @param name jméno hráče
 * @param depth hloubka stromu
 * @param symbol symbol hráče
 * @return 1 pokud se povedlo, jinak 0.
 */
int playerChangeInit(struct player** pPlayer, const char *type, const char *name, const int depth, int symbol);
/**
 * @brief Alokace paměti pro strukturu hráče
 *  * @param pPlayer ukazatel na hráče
 * @param type minimax/human
 * @param name jméno hráče
 * @param depth hloubka stromu pro minimax
 * @return alokovanou strukturu, nebo NULL
 */
void playerAllocate(struct player** pPlayer, const char *type, const char *name, const int depth, int symbol);
/**
 * @brief Inicializace hodnot stroktury
 * @param pPlayer ukazatel na hráče
 * @param type minimax/human
 * @param name jméno hráče
 * @param depth hloubka stromu pro minimax
 * @return 1 pokud povedlo, jinak 0
 */
int playerInit(struct player** pPlayer, const char *type, const char *name, const int depth, int symbol);
/**
 * @brief Deinicializace hodnot struktury
 * @param pPlayer ukazatel na hráče
 */
void playerDeinit(struct player** pPlayer);
/**
 * @brief Dealokace paměti
 * @param pPlayer ukazatel na hráče
 */
void playerFree(struct player** play);
/**
 * @brief Ukončení programu, dealokace veškeré paměti
 * @param problem návratová hodnota pro uživatele
 */
void ext(int problem);
/**
 * @brief Metoda pro vytištění hrací plochy
 */
void printboard();
/**
 * @brief Rozpoznání jména hráčů
 * @param piece symbol hráče
 * @return písmenné označení hráče
 */
char letterOfPlayer(int symbol);
/**
 * @brief Převední vstupu na malé písmena
 * @param str převáděný string
 */
void to_lowercase(char *str);
#endif
