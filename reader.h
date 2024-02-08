/**
 * @file reader.h
 * @author twitty
 * @brief Hlavičkový soubor pro načtení vstupních argumentů
 * @version 1.0
 * @date 2023-12-31
 */
#ifndef READER_H
#define READER_H
/**
 * @brief Pomocná funkce pro připravení typu hráče
 * @param string kandidát na typ hráče
 * @return typ hráče, jinak NULL
 */
const char* preparePlayerType(const char* string);
/**
 * @brief Pomocná funkce pro stanovení velikosti hrací plochy
 * @param string pole argumentů
 * @param index index označující začátek popisu hrací plochy
 */
void prepareSize(const char** string, int index);
/**
 * @brief Funkce pro připravení hodnot k incializiace hráče
 * @param player ukazatel na hráče, kterého budeme inicializovat
 * @param string pole argumentů
 * @param index index označující začátek popisu hráče
 * @return hráč nebo NULL
 */
void preparePlayer(struct player** player, const char** string, int index, int symbol);
/**
 * @brief Pomocná funkce pro stanovená výchozí polohy kamenů
 * @param string pole argumentů
 * @param index index označující začátek popisu hrací plochy
 */
void prepareInitBoard(const char** string, int index);
/**
 * @brief Pomocná funkce pro výstupní soubur
 * @param string pole argumentů
 * @param index index označující začátek popisu hrací plochy
 */
void prepareOutputFile(const char** string, int index);
/**
 * @brief Pomocná funkce pro vstupní soubur
 * @param string pole argumentů
 * @param index index označující začátek popisu hrací plochy
 */
void prepareInputFile(const char* *string, int index);
/**
 * @brief Určení, zda-li je string přepínač příkazové řádky nebo ne
 * @param string slovo/parametr
 * @return 0 pokud je přepínač či chyba, 1 pokud je to jiné slovo
 */
int isNotToken(const char* string);
/**
 * @brief Pokusí se otevřít a přečíst vstupní soubor
 * @param string název vstupního souboru
 */
void openInputFile(const char* string);
/**
 * @brief Pokusí se otevřít a přečíst výstupní soubor
 * @param string název výstupního souboru
 */
void openOutputFile(const char* string);
/**
 * @brief Zkontroluje, jestl se jedná o číslo, když ano tak ho vrátí, když ne tak vypne program -> je nutně očekávané číslo
 * @param string adept na číslo
 * @return číslo
 */
int isNumber(const char* string);
/**
 * @brief Převede string na číslo
 * @param string adept na číslo
 * @return číslo nebo -1 při chybě
 */
int isItNumber(const char* string);
/**
 * @brief Zkontroluje, jestli je zadaný počet parametrů pro přepínač správný
 * @param string pole argumentů
 * @param index index ukazující na první zkoumany
 * @param maxNumber maximální počet argumentů
 */
void checkNumberOfParameters(const char** string, int index, int maxNumber);
/**
 * @brief Zkontroluje, jestli je soubor v .txt formátu
 * @param string název souboru
 * @return 1 pokud ok, jinak 0
 */
int isTxtFormat(const char* string);
/**
 * @brief Funkce pro zjištění, jestli je přiložen input file
 * @param string pole argumentů
 * @param numberOfParameters počet argumentů
 * @return 1 pokud ok, jinak 0
 */
int containsInputFile(const char** string, int numberOfParameters);
/**
 * Vlastní impelemntace strdup funkce
 * @param src zadaný string
 * @return kopie nebo null
 */
char *my_strdup(const char* src);
/**
 * @brief Vlastní implementace funkce strtok_r
 * @param str string, který je rozdělován
 * @param delim znaky, dle kterých se dělí
 * @param saveptr pro udržení kontextu
 * @return rozdělené slovo
 */
char *my_strtok_r(char* str, const char* delim, char** saveptr);
/**
 * @brief Uvolnění paměti po načtení vstupního souboru
 * @param file načtená data
 * @param gameIndex index od kterého začínají tahy
 * @param numberOfWords počet slov souboru
 * @param numberOfMoves počet řádek souboru
 */
void freeInputLoad(char*** file, int gameIndex, int numberOfWords, int numberOfMoves);
/**
 * @brief Načítání parametrů dle tokenů
 * @param argc počet parametrů
 * @param argv pole parametrů
 * @param fromFile označení, jestli jde o čtení ze souboru, 1 ano, 0 ne.
*/
void load(int argc, const char *argv[], int fromFile);
/**
 * @brief
 * @param gameIndex index od kterého začínají tahy
 * @param lastToken index na kterém se vyskytuje poslední token
 * @param numberOfLines počet řádek souboru
 */
void validateInputFile(int gameIndex, int lastToken, int numberOfLines);
/**
 * @brief Načtení souboru řádek po řádce
 * @param inputFile čtený soubor
 * @param file pole pro načtená data
 * @param numberOfWords počet slov v souboru
 */
void readLinesAndTokenize(FILE* inputFile, char*** file, int* numberOfWords);
/**
 * @brief Počítání počtu řádků a slov v souboru
 * @param inputFile zdrojový soubor
 * @param numberOfWords pointer na počet slove
 * @param numberOfLines pointner na počet řádek
 */
void countWordsAndLines(FILE* inputFile, int* numberOfWords, int* numberOfLines);
/**
 * @brief Přidá první označení souboru jako první načtené slovo pro udržení stejné struktury jako u
 *  načítaných a parametrů z příkazové řádky
 * @param file zdrojový soubor
 * @param numberOfWords počet slov v souboru
 */
void addFirstWord(char*** file, int* numberOfWords);
/**
 * @brief Načte defaultní informace, pokud nějaká chybí.
 */
void loadDefaultInformation();
#endif
