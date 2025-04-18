#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_LENGTH 256
#define DATA_FILE "files.txt"
#define TRASH_FILE "trash.txt"

// Load data from file into array
int loadFromFile(const char *filename, char data[MAX_ITEMS][MAX_LENGTH]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return 0;

    int count = 0;
    while (fgets(data[count], MAX_LENGTH, file) != NULL && count < MAX_ITEMS) {
        char *newline = strchr(data[count], '\n');
        if (newline != NULL) {
            *newline = '\0'; // Remove newline
        }
        if (strlen(data[count]) > 0) {
            count++;
        }
    }

    fclose(file);
    return count;
}

// Save array to file
void saveToFile(char data[MAX_ITEMS][MAX_LENGTH], int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }
   int i;
for (i = 0; i < count; i++) {
    fprintf(file, "%s\n", data[i]);
}

    fclose(file);
}

// Show list of items
void showList(char data[MAX_ITEMS][MAX_LENGTH], int count, const char *title) {
    printf("\n--- %s ---\n", title);
    if (count == 0) {
        printf("No items found.\n");
    } else {
    	int i;
        for (i = 0; i < count; i++) {
            printf("%d. %s\n", i + 1, data[i]);
        }
    }
}

// Delete item (move to trash)
void deleteItem() {
    char files[MAX_ITEMS][MAX_LENGTH];
    char trash[MAX_ITEMS][MAX_LENGTH];

    int fileCount = loadFromFile(DATA_FILE, files);
    int trashCount = loadFromFile(TRASH_FILE, trash);

    showList(files, fileCount, "Available Files");

    printf("Enter the number to delete: ");
    int choice;
    scanf("%d", &choice);

    if (choice >= 1 && choice <= fileCount) {
        strcpy(trash[trashCount], files[choice - 1]);
        trashCount++;
        int i;
        for (i = choice - 1; i < fileCount - 1; i++) {
            strcpy(files[i], files[i + 1]);
        }
        fileCount--;

        saveToFile(files, fileCount, DATA_FILE);
        saveToFile(trash, trashCount, TRASH_FILE);

        printf("Moved to Trash.\n");
    } else {
        printf("Invalid choice.\n");
    }
}

// Restore item from trash
void restoreItem() {
    char files[MAX_ITEMS][MAX_LENGTH];
    char trash[MAX_ITEMS][MAX_LENGTH];

    int fileCount = loadFromFile(DATA_FILE, files);
    int trashCount = loadFromFile(TRASH_FILE, trash);

    showList(trash, trashCount, "Trash");

    printf("Enter the number to restore: ");
    int choice;
    scanf("%d", &choice);

    if (choice >= 1 && choice <= trashCount) {
        strcpy(files[fileCount], trash[choice - 1]);
        fileCount++;
         int i;
        for (i = choice - 1; i < trashCount - 1; i++) {
            strcpy(trash[i], trash[i + 1]);
        }
        trashCount--;

        saveToFile(files, fileCount, DATA_FILE);
        saveToFile(trash, trashCount, TRASH_FILE);

        printf("Restored successfully.\n");
    } else {
        printf("Invalid choice.\n");
    }
}

// Main menu
int main() {
    int option;

    while (1) {
        printf("\n====== Trash Bin Menu ======\n");
        printf("1. Show Files\n");
        printf("2. Show Trash\n");
        printf("3. Delete File\n");
        printf("4. Restore File\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1: {
                char files[MAX_ITEMS][MAX_LENGTH];
                int fileCount = loadFromFile(DATA_FILE, files);
                showList(files, fileCount, "Files");
                break;
            }
            case 2: {
                char trash[MAX_ITEMS][MAX_LENGTH];
                int trashCount = loadFromFile(TRASH_FILE, trash);
                showList(trash, trashCount, "Trash");
                break;
            }
            case 3:
                deleteItem();
                break;
            case 4:
                restoreItem();
                break;
            case 5:
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("Invalid option.\n");
        }
    }

    return 0;
} 