#include <stdio.h>
#include <string.h>
#include "StrList.h"

#define TRUE 1
#define FALSE 0
#define BOOL int

typedef struct StrListNode {
    char* data;
    struct StrListNode* next;
} StrListNode;

struct _StrList {
    int size;
    StrListNode* head;
};

StrList* StrList_alloc() {
    StrList* strList = malloc(sizeof(StrList));
    if (strList != NULL) {
        strList->size = 0;
        strList->head = NULL;
    }

    return strList;
}

void StrList_free(StrList *strList) {
    if (strList == NULL) {
        return;
    }

    StrListNode* iterator = strList->head;
    while (iterator != NULL) {
        StrListNode* next = iterator->next;
        free(iterator->data);
        free(iterator);
        iterator = next;
    }

    free(strList);
}

size_t StrList_size(const StrList *strList) {
    return strList->size;
}

void StrList_insertLast(StrList *strList, const char *data) {
    if (strList == NULL) {
        return;
    }

    StrListNode *newItem = malloc(sizeof(StrListNode));
    if ((newItem->data = strdup(data)) == NULL) {
        free(newItem);
        return;
    }
    newItem->next = NULL;

    if (strList->size == 0) {
        newItem->next = strList->head;
        strList->head = newItem;
    } else {
        int i = 0;
        StrListNode *current = strList->head;
        while (i != strList->size - 1 && current->next != NULL) {
            i++;
            current = current->next;
        }

        if (i == strList->size - 1) {
            newItem->next = current->next;
            current->next = newItem;
        }
    }

    strList->size++;
}

void StrList_insertAt(StrList *strList, const char *data, int index) {
    if (strList == NULL) {
        return;
    }

    StrListNode *newItem = malloc(sizeof(StrListNode));
    if ((newItem->data = strdup(data)) == NULL) {
        free(newItem);
        return;
    }
    newItem->next = NULL;

    if (index == 0) {
        newItem->next = strList->head;
        strList->head = newItem;
    } else {
        int i = 0;
        StrListNode *current = strList->head;
        while (i != index && current->next != NULL) {
            i++;
            current = current->next;
        }

        if (i == index) {
            newItem->next = current->next;
            current->next = newItem;
        }
    }

    strList->size++;
}

char *StrList_firstData(const StrList *strList) {
    if (strList == NULL) {
        return NULL;
    }

    return strList->head->data;
}

void StrList_print(const StrList *strList) {
    if (strList == NULL) {
        return;
    }

    if (strList->size > 0) {
        const StrListNode *iterator = strList->head;

        do {
            printf("%s ", iterator->data);
            iterator = iterator->next;
        } while (iterator->next != NULL);

        printf("%s", iterator->data);
    }

    printf("\n");
}

void StrList_printAt(const StrList *strList, int index) {
    if (strList == NULL) {
        return;
    }

    int i = 0;
    const StrListNode *iterator = strList->head;

    while (i != index && iterator->next != NULL) {
        i++;
        iterator = iterator->next;
    }

    if (i == index) {
        printf("%s", iterator->data);
    }

    printf("\n");
}

int StrList_printLen(const StrList *strList) {
    if (strList == NULL || strList->size == 0) {
        return 0;
    }

    int chars = 0;
    const StrListNode *iterator = strList->head;

    while (iterator != NULL) {
        size_t len = strlen(iterator->data);
        chars += (int) len;
        iterator = iterator->next;
    }

    return chars;
}

int StrList_count(StrList *strList, const char *data) {
    if (strList == NULL) {
        return 0;
    }

    int count = 0;
    const StrListNode *iterator = strList->head;

    while (iterator != NULL) {
        if (strcmp(iterator->data, data) == 0) {
            count++;
        }
        iterator = iterator->next;
    }

    return count;
}

void StrList_remove(StrList *strList, const char *data) {
    if (strList == NULL) {
        return;
    }

    StrListNode *iterator = strList->head;
    StrListNode *previous = NULL;

    while (iterator != NULL) {
        if (strcmp(iterator->data, data) == 0) {
            StrListNode* next = iterator->next;

            if (previous != NULL) {
                previous->next = iterator->next;
            } else {
                strList->head = next;
            }

            free(iterator->data);
            free(iterator);

            iterator = next;

            strList->size--;
        } else {
            previous = iterator;
            iterator = iterator->next;
        }
    }
}

void StrList_removeAt(StrList *strList, int index) {
    if (strList == NULL || strList->size == 0) {
        return;
    }

    int i = 0;
    StrListNode *iterator = strList->head;
    StrListNode *previous = NULL;

    while (i != index && iterator != NULL) {
        i++;
        previous = iterator;
        iterator = iterator->next;
    }

    if (iterator != NULL) {
        if (previous == NULL) {
            strList->head = iterator->next;
        } else {
            previous->next = iterator->next;
        }
        free(iterator->data);
        free(iterator);

        strList->size--;
    }
}

BOOL StrList_isEqual(const StrList* strList1, const StrList* strList2) {
    if (strList1 == NULL && strList2 == NULL) {
        return TRUE;
    }

    if (strList1 == NULL || strList2 == NULL || strList1->size != strList2->size) {
        return FALSE;
    }

    for (StrListNode *p1 = strList1->head, *p2 = strList2->head; p1 != NULL && p2 != NULL; p1 = p1->next, p2 = p2->next) {
        if (strcmp(p2->data, p1->data) != 0) {
            return FALSE;
        }
    }

    return TRUE;
}

StrList* StrList_clone(const StrList* strList) {
    StrList* newList = StrList_alloc();

    for (StrListNode* i = strList->head; i != NULL; i = i->next) {
        StrList_insertLast(newList, i->data);
    }

    return newList;
}

void StrList_reverse(StrList* StrList) {
    if (StrList == NULL || StrList->head == NULL) {
        return;
    }

    StrListNode* previous = NULL;
    StrListNode* current = StrList->head;
    StrListNode* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    StrList->head = previous;
}

int compareStrings(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    return strcmp(str1, str2);
}

void StrList_sort(StrList* strList) {
    if (!strList || strList->size <= 1) {
        return;
    }

    char **stringArray = malloc(strList->size * sizeof(char *));
    if (!stringArray) {
        printf("Memory allocation failed.\n");
        return;
    }

    StrListNode *current = strList->head;
    size_t i = 0;
    while (current != NULL) {
        stringArray[i++] = current->data;
        current = current->next;
    }

    qsort(stringArray, strList->size, sizeof(char *), compareStrings);

    current = strList->head;
    i = 0;
    while (current != NULL) {
        current->data = stringArray[i];
        current = current->next;
        i++;
    }

    free(stringArray);
}

BOOL StrList_isSorted(StrList* StrList) {
    if (StrList == NULL || StrList->size <= 1) {
        return TRUE;
    }

    StrListNode* previous = NULL;
    StrListNode* current = StrList->head;
    while (current != NULL) {
        if (previous != NULL && strcmp(previous->data, current->data) > 0) {
            return FALSE;
        }

        previous = current;
        current = current->next;
    }

    return TRUE;
}
