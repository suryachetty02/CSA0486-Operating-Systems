#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100

// Data structure for a file
struct File {
    char name[100]; // File name
    char records[MAX_RECORDS][100]; // Array to store records
    int numRecords; // Number of records in the file
};

struct File files[10]; // Array to hold files (up to 10 files)

// Create a new file
int createFile(char name[]) {
    for (int i = 0; i < 10; i++) {
        if (strlen(files[i].name) == 0) {
            strcpy(files[i].name, name);
            files[i].numRecords = 0;
            return i;
        }
    }
    return -1; // No free slots for a new file
}

// Add a record to a file
int addRecord(int fileIndex, char record[]) {
    struct File* file = &files[fileIndex];
    if (file->numRecords < MAX_RECORDS) {
        strcpy(file->records[file->numRecords], record);
        file->numRecords++;
        return 1;
    }
    return 0; // No space for a new record
}

// Display all records in a file
void displayFileRecords(int fileIndex) {
    struct File* file = &files[fileIndex];
    printf("File: %s\n", file->name);
    printf("Records:\n");
    for (int i = 0; i < file->numRecords; i++) {
        printf("%s\n", file->records[i]);
    }
}

int main() {
    int choice, fileIndex;
    char name[100], record[100];

    while (1) {
        printf("1. Create a file\n2. Add a record\n3. Display file records\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the file name: ");
                scanf("%s", name);
                fileIndex = createFile(name);
                if (fileIndex != -1) {
                    printf("File created with index %d\n", fileIndex);
                } else {
                    printf("No free slots for a new file\n");
                }
                break;
            case 2:
                printf("Enter the file index: ");
                scanf("%d", &fileIndex);
                printf("Enter the record: ");
                scanf("%s", record);
                if (addRecord(fileIndex, record)) {
                    printf("Record added to the file\n");
                } else {
                    printf("No space for a new record\n");
                }
                break;
            case 3:
                printf("Enter the file index: ");
                scanf("%d", &fileIndex);
                displayFileRecords(fileIndex);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
