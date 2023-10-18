#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3

int pageQueue[MAX_FRAMES]; // Frames in memory
int pageQueueFront = 0;    // Index of the front of the page queue
int pageFaults = 0;        // Counter for page faults
int pageHits = 0;          // Counter for page hits

// Initialize the page queue with sentinel values -1
void initializePageQueue() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        pageQueue[i] = -1;
    }
}

// Check if a page is already in memory
bool isPageInMemory(int page) {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (pageQueue[i] == page) {
            return true;
        }
    }
    return false;
}

// Simulate the FIFO Page Replacement algorithm
void simulateFIFO(int pages[], int numPages) {
    for (int i = 0; i < numPages; i++) {
        int page = pages[i];

        if (isPageInMemory(page)) {
            pageHits++;
        } else {
            pageQueue[pageQueueFront] = page;
            pageQueueFront = (pageQueueFront + 1) % MAX_FRAMES; // Move the front to the next frame
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
    simulateFIFO(pages, numPages);

    printf("Total Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", pageHits);

    return 0;
}
