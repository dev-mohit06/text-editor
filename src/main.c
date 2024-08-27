// main.c
#include "common.h"
#include "linked_list.h"
#include "file_operations.h"

int main() {
    int choice, linePosition;
    char  newLine[MAX_LINE_CHAR];
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
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 7) {
            break;
        }

        switch (choice) {
        case 1:
            printf("Enter the text: ");
            scanf(" %[^\n]", newLine);
            insertLine(newLine);
            break;
        case 2:
            printf("Enter the line number: ");
            scanf("%d", &linePosition);
            printf("Enter the new text: ");
            scanf(" %[^\n]", newLine);
            edit(newLine, linePosition);
            break;
        case 3:
            printf("Enter the position: ");
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
            printf("\n========== INVALID CHOICE ==========\n");
            break;
        }

        printf("DO YOU WANT TO REPEAT [1/0]: ");
        scanf("%d", &choice);
        if (choice == 0) {
            break;
        } else {
            system("clear");
        }
    } while (1);

    return 0;
}