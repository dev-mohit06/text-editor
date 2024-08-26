// linked_list.c
#include "linked_list.h"

NODE *HEAD = NULL;
NODE *TAIL = NULL;
int lineCount = 0;

NODE *getNode(char *string) {
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode->prev = newNode->next = NULL;
    strcpy(newNode->line, string);
    return newNode;
}

void insertLine(char *string) {
    NODE *newLine = getNode(string);

    if (HEAD == NULL) {
        HEAD = newLine;
        TAIL = newLine;
    } else {
        TAIL->next = newLine;
        newLine->prev = TAIL;
        TAIL = newLine;
    }
    lineCount++;
}

void edit(char *string, int lineNumber) {
    if (lineNumber == 1 && (HEAD == NULL || TAIL == NULL)) {
        insertLine(string);
        return;
    }

    if (lineNumber > lineCount) {
        printf("\n========== LINE NOT EXIST ==========\n");
        return;
    }

    NODE *TEMP = (lineNumber <= lineCount / 2) ? HEAD : TAIL;

    if (lineNumber <= lineCount / 2) {
        for (int i = 1; i < lineNumber; i++) {
            TEMP = TEMP->next;
        }
    } else {
        for (int i = lineCount; i > lineNumber; i--) {
            TEMP = TEMP->prev;
        }
    }
    strcpy(TEMP->line, string);
}

void deleteLine(int lineNumber) {
    if (lineNumber > lineCount) {
        printf("\n========== LINE NOT EXIST ==========\n");
        return;
    }

    NODE *TEMP;

    if (HEAD == TAIL) {
        HEAD = TAIL = NULL;
        return;
    }

    TEMP = (lineNumber <= lineCount / 2) ? HEAD : TAIL;

    if (lineNumber <= lineCount / 2) {
        for (int i = 1; i < lineNumber; i++) {
            TEMP = TEMP->next;
        }
    } else {
        for (int i = lineCount; i > lineNumber; i--) {
            TEMP = TEMP->prev;
        }
    }

    if (TEMP->next != NULL) {
        TEMP->next->prev = TEMP->prev;
    }
    if (TEMP->prev != NULL) {
        TEMP->prev->next = TEMP->next;
    }

    if (TEMP == HEAD) {
        HEAD = TEMP->next;
    }
    if (TEMP == TAIL) {
        TAIL = TEMP->prev;
    }

    free(TEMP);
    lineCount--;
}

void display() {
    if (HEAD == NULL) {
        printf("\n========== EMPTY FILE ==========\n");
        return;
    }

    NODE *TEMP = HEAD;
    for (int i = 1; TEMP != NULL; i++) {
        printf("%d %s\n", i, TEMP->line);
        TEMP = TEMP->next;
    }
}

void reset() {
    NODE *current = HEAD;
    NODE *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    HEAD = NULL;
    TAIL = NULL;
    lineCount = 0;
}