#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINE_CHAR 1024
#define WORD_COUNT 10
#define MAX_FILENAME_LENGTH 256
#define DIRECTORY_PATH "./exports"

typedef struct node {
    char line[MAX_LINE_CHAR];
    struct node *prev, *next;
} NODE;

extern NODE *HEAD;
extern NODE *TAIL;
extern int lineCount;
extern char globalFileName[MAX_FILENAME_LENGTH];
extern char fullPath[MAX_FILENAME_LENGTH];

#endif // COMMON_H