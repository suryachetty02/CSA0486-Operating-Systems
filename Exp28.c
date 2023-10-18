#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grep(const char *pattern, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open the file '%s'\n", filename);
        return;
    }

    char line[256]; // You can adjust the buffer size as needed
    int lineNum = 0;

    while (fgets(line, sizeof(line), file)) {
        lineNum++;

        if (strstr(line, pattern) != NULL) {
            printf("%s:%d: %s", filename, lineNum, line);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[1];
    const char *filename = argv[2];

    grep(pattern, filename);

    return 0;
}
