#include <stdio.h>
#include "StrList.h"

#define MAX_STRING_LENGTH 1000
#define NEW_LIST 1
#define INSERT_STR 2
#define PRINT_LIST 3
#define LIST_LEN 4
#define PRINT_STR_BY_INDEX 5
#define TOTAL_CHARS 6
#define APPEARANCES 7
#define REMOVE_STR 8
#define REMOVE_INDEX 9
#define REVERSE_LIST 10
#define CLEAR_LIST 11
#define LEXICOGRAPHIC_SORT 12
#define IS_SORTED 13
#define EXIT 0

void getString(char* s) {
    scanf("%s", s);
}

void getInt(int* i) {
    scanf("%d", i);
}

int main() {
    int selection;
    char word[MAX_STRING_LENGTH];
    int index;

    StrList* strList = StrList_alloc();

    do {
        getInt(&selection);
        switch (selection) {
            case NEW_LIST:
                getInt(&selection);
                for (int i = 1; i <= selection; i++) {
                    getString(word);
                    StrList_insertLast(strList, word);
                }
                break;

            case INSERT_STR:
                getInt(&index);
                getString(word);
                StrList_insertAt(strList, word, index);
                break;

            case PRINT_LIST:
                StrList_print(strList);
                break;

            case LIST_LEN:
                printf("%zu\n", StrList_size(strList));
                break;

            case PRINT_STR_BY_INDEX:
                getInt(&index);
                StrList_printAt(strList, index);
                break;

            case TOTAL_CHARS:
                printf("%d\n", StrList_printLen(strList));
                break;

            case APPEARANCES:
                getString(word);
                printf("%d\n", StrList_count(strList, word));
                break;

            case REMOVE_STR:
                getString(word);
                StrList_remove(strList, word);
                break;

            case REMOVE_INDEX:
                getInt(&index);
                StrList_removeAt(strList, index);
                break;

            case REVERSE_LIST:
                StrList_reverse(strList);
                break;

            case CLEAR_LIST:
                while (StrList_size(strList) != 0) {
                    StrList_removeAt(strList, 0);
                }
                break;

            case LEXICOGRAPHIC_SORT:
                StrList_sort(strList);
                break;

            case IS_SORTED:
                printf("%s\n", StrList_isSorted(strList) ? "true" : "false");
                break;
        }
    } while (selection != EXIT);

    StrList_free(strList);

    return 0;
}