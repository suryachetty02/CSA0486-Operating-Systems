#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_FRAMES 3

int pageQueue[MAX_FRAMES]; // Frames in memory
int pageFaults = 0;        // Counter for page faults
int pageHits = 0;          // Counter for page hits

// Initialize the page queue with a sentinel value -1
void initializePageQueue() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        pageQueue[i] = -1;
    }
}

// Find the optimal page to replace
int findOptimalPage(int startIndex, int pages[], int numPages) {
    int index = -1;
    int farthest = -1;

    for (int i = 0; i < MAX_FRAMES; i++) {
        int j;
        for (j = startIndex; j < numPages; j++) {
            if (pageQueue[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == numPages) {
            return i; // The page is not used anymore, so replace it
        }
    }

    if (index == -1) {
        index = 0;
    }

    return index;
}

// Simulate the Optimal Page Replacement algorithm
void simulateOptimal(int pages[], int numPages) {
    for (int i = 0; i < numPages; i++) {
        int page = pages[i];

        bool pageFound = false;
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (pageQueue[j] == page) {
                pageFound = true;
                pageHits++;
                break;
            }
        }

        if (!pageFound) {
            int index = findOptimalPage(i + 1, pages, numPages); // Find the page to replace
            pageQueue[index] = page;                                // Replace the page
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
    simulateOptimal(pages, numPages);

    printf("Total Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", pageHits);

    return 0;
}
