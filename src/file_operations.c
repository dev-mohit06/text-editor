// file_operations.c
#include "file_operations.h"

const char *adjectives[] = {"Quick", "Silent", "Bright", "Dark", "Clever", "Funky", "Smooth", "Mighty", "Swift", "Brave"};
const char *nouns[] = {"Fox", "River", "Mountain", "Forest", "Ocean", "Star", "Storm", "Valley", "Sunset", "Desert"};

char globalFileName[MAX_FILENAME_LENGTH];
char fullPath[MAX_FILENAME_LENGTH];

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

    // Create the directory if it doesn't exist
    struct stat st = {0}; // Initialize stat structure
    if (stat(DIRECTORY_PATH, &st) == -1) {
        // Directory does not exist, so create it
        if (mkdir(DIRECTORY_PATH, 0700) != 0) {
            perror("Could not create directory");
            return;
        }
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