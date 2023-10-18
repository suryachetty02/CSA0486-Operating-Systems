#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3

int pageQueue[MAX_FRAMES]; // Frames in memory
int pageCounter = 0;       // Counter for page usage
int pageFaults = 0;        // Counter for page faults
int pageHits = 0;          // Counter for page hits

// Initialize the page queue with sentinel values -1
void initializePageQueue() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        pageQueue[i] = -1;
    }
}

// Find the least recently used page to replace
int findLRUPage(int pages[]) {
    int minPageCounter = pageCounter;
    int index = 0;

    for (int i = 0; i < MAX_FRAMES; i++) {
        int page = pageQueue[i];
        int j;

        for (j = 0; j < MAX_FRAMES; j++) {
            if (page == pages[j] && pageCounter < minPageCounter) {
                minPageCounter = pageCounter;
                index = i;
                break;
            }
        }
    }

    return index;
}

// Simulate the LRU Page Replacement algorithm
void simulateLRU(int pages[], int numPages) {
    for (int i = 0; i < numPages; i++) {
        int page = pages[i];

        bool pageFound = false;
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (pageQueue[j] == page) {
                pageFound = true;
                pageHits++;
                pageCounter = i;
                break;
            }
        }

        if (!pageFound) {
            int index = findLRUPage(pages); // Find the least recently used page to replace
            pageQueue[index] = page;         // Replace the page
            pageCounter = i;
            pageFaults++;
        }

        printf("Page Queue: ");
        for (int j = 0; j < MAX_FRAMES; j++) {
            printf("%d ", pageQueue[j]);
        }
        printf("\n");
    }
}

int main() {
    int numPages;

    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &numPages);

    int pages[numPages];

    printf("Enter the page reference string:\n");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    initializePageQueue();
    int pageCounter[numPages];

    for (int i = 0; i < numPages; i++) {
        pageCounter[i] = -1;
    }

    simulateLRU(pages, numPages);

    printf("Total Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", pageHits);

    return 0;
}
