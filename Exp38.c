#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

void scan(int requests[], int n, int head, int direction) {
    int seek_sequence[SIZE];
    int seek_count = 0;
    
    int left = 0, right = SIZE - 1;

    if (direction == 1) {
        // Find the rightmost request
        for (int i = 0; i < n; i++) {
            if (requests[i] > head && requests[i] <= right)
                right = requests[i];
        }
    } else {
        // Find the leftmost request
        for (int i = 0; i < n; i++) {
            if (requests[i] < head && requests[i] >= left)
                left = requests[i];
        }
    }

    // Scan in the specified direction
    while (1) {
        if (direction == 1) {
            for (int i = head; i <= right; i++) {
                seek_sequence[seek_count++] = i;
            }
            head = right;
            // No more requests in the right direction
            if (seek_count >= n)
                break;
            // Move to the end
            seek_sequence[seek_count++] = SIZE - 1;
            direction = 0;
        } else {
            for (int i = head; i >= left; i--) {
                seek_sequence[seek_count++] = i;
            }
            head = left;
            // No more requests in the left direction
            if (seek_count >= n)
                break;
            // Move to the beginning
            seek_sequence[seek_count++] = 0;
            direction = 1;
        }
    }

    printf("Seek Sequence: ");
    for (int i = 0; i < seek_count; i++) {
        printf("%d ", seek_sequence[i]);
    }

    printf("\nTotal Seek Time = %d\n", seek_count);
}

int main() {
    int requests[SIZE];
    int n, head, direction;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    if (n > SIZE || n <= 0) {
        printf("Invalid number of requests.\n");
        return 1;
    }

    printf("Enter the request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    if (head < 0 || head >= SIZE) {
        printf("Invalid head position.\n");
        return 1;
    }

    printf("Enter the direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    if (direction != 0 && direction != 1) {
        printf("Invalid direction.\n");
        return 1;
    }

    scan(requests, n, head, direction);

    return 0;
}
