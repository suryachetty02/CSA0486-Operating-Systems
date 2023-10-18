#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 20
#define MAX_FILENAME_LENGTH 20
#define MAX_DIRECTORIES 10
#define MAX_SUBDIRECTORIES 5

struct File {
    char name[MAX_FILENAME_LENGTH];
    int size;
};

struct Directory {
    struct File files[MAX_FILES];
    int num_files;
};

struct Subdirectory {
    char name[MAX_FILENAME_LENGTH];
    struct Directory directory;
    int used;
};

struct TwoLevelDirectory {
    struct Subdirectory subdirectories[MAX_SUBDIRECTORIES];
    int num_subdirectories;
};

void initializeDirectory(struct Directory *dir) {
    dir->num_files = 0;
}

void initializeTwoLevelDirectory(struct TwoLevelDirectory *twoLevelDir) {
    twoLevelDir->num_subdirectories = 0;
}

void createFile(struct Directory *dir, const char *filename, int size) {
    if (dir->num_files >= MAX_FILES) {
        printf("Directory is full. Cannot create more files.\n");
        return;
    }

    if (strlen(filename) >= MAX_FILENAME_LENGTH) 
	{
        printf("Filename is too long. Maximum length is %d characters.\n", MAX_FILENAME_LENGTH - 1);
		}
       

