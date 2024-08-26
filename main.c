#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINE_CHAR 1024
#define WORD_COUNT 10
#define MAX_FILENAME_LENGTH 256
#define DIRECTORY_PATH "./saves"

typedef struct node {
    char line[MAX_LINE_CHAR];
    struct node *prev, *next;
} NODE;

int lineCount = 0;
NODE *HEAD = NULL, *TAIL = NULL;

// Predefined sets of words
const char *adjectives[] = {"Quick", "Silent", "Bright", "Dark", "Clever", "Funky", "Smooth", "Mighty", "Swift", "Brave"};
const char *nouns[] = {"Fox", "River", "Mountain", "Forest", "Ocean", "Star", "Storm", "Valley", "Sunset", "Desert"};

// Global variable to store the filename
char globalFileName[MAX_FILENAME_LENGTH];
char fullPath[MAX_FILENAME_LENGTH];


NODE *getNode(char *);
void insertLine(char *);
void edit(char *, int);
void deleteLine(int);
void display();
void saveFile();
void generateRandomFileName();
void reset();

int main() {

    int choise, linePosition;
    char newLine[MAX_LINE_CHAR];
    system("clear");
    do {
        printf("\n========== TEXT EDITOR ==========\n");
        printf("1. Insert New Line\n");
        printf("2. Edit Line\n");
        printf("3. Delete Line\n");
        printf("4. Display File\n");
        printf("5. Save File\n");
        printf("6. Reset File\n");
        printf("7. Exit File\n");
        printf("Enter your choise : ");
        scanf("%d", &choise);

        if (choise == 7) {
            break;
        }

        switch (choise) {
        case 1:
            printf("Enter the text : ");
            scanf(" %[^\n]", newLine);
            insertLine(newLine);
            break;
        case 2:
            printf("Enter the line number : ");
            scanf("%d", &linePosition);
            printf("Enter the new text : ");
            scanf(" %[^\n]", newLine);
            edit(newLine, linePosition);
            break;
        case 3:
            printf("Enter the position : ");
            scanf("%d", &linePosition);
            deleteLine(linePosition);
            break;
        case 4:
            display();
            break;
        case 5:
            saveFile();
            break;
        case 6:
            reset();
            break;
        default:
            printf("\n========== INVALID CHOISE ==========\n");
            break;
        }

        printf("DO YOU WANT TO REPET [1/0] : ");
        scanf("%d", &choise);
        if (choise == 0) {
            break;
        } else {
            system("clear");
        }
    } while (1);

    return 0;
}

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

void display() {

    if (HEAD == NULL) {
        printf("\n========== EMPTY FILE ==========\n");
    }

    NODE *TEMP = HEAD;
    for (int i = 1; TEMP != NULL; i++) {
        printf("%d %s\n", i, TEMP->line);
        TEMP = TEMP->next;
    }
    free(TEMP);
    return;
}

void edit(char *string, int lineNumber) {

    if (lineNumber == 1 && (HEAD == NULL || TAIL == NULL)) {
        insertLine(string);
        return;
    }

    if (lineNumber > lineCount) {
        printf("\n========== LINE NOT EXSIST ==========\n");
        return;
    }

    NODE *TEMP;
    TEMP = (lineNumber <= lineCount / 2) ? HEAD : TAIL;

    // Traverse to the desired line
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
    free(TEMP);
    return;
}

void deleteLine(int lineNumber) {
    if (lineNumber > lineCount) {
        printf("\n========== LINE NOT EXSIST ==========\n");
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

    TEMP->next->prev = TEMP->prev;
    TEMP->prev->next = TEMP->next;
    free(TEMP);
    return;
}

void generateRandomFileName() {
    srand((unsigned int)time(NULL));

    int adjIndex = rand() % WORD_COUNT;
    int nounIndex = rand() % WORD_COUNT;

    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", tm_info);

    snprintf(globalFileName, sizeof(globalFileName), "%s_%s_%s.txt", adjectives[adjIndex], nouns[nounIndex], timestamp);

    snprintf(fullPath, sizeof(fullPath), "%s/%s", DIRECTORY_PATH, globalFileName);
}

void saveFile() {
    if (HEAD == NULL) {
        printf("\n========== FILE IS EMPTY ==========\n");
        return;
    }
    generateRandomFileName();

    FILE *file = fopen(fullPath, "w");
    if (file == NULL) {
        printf("Could not open file for writing\n");
        return;
    }
    NODE *temp = HEAD;
    while (temp != NULL) {
        fprintf(file, "%s\n", temp->line);
        temp = temp->next;
    }
    fclose(file);
    printf("File saved successfully at %s\n", fullPath);
}

void reset() {
    NODE *current = HEAD;
    NODE *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    // Reset HEAD and TAIL pointers
    HEAD = NULL;
    TAIL = NULL;
    lineCount = 0;
    return;
}