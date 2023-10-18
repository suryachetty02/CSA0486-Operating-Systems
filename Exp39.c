#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

void cscan(int requests[], int n, int head, int direction) {
    int seek_sequence[SIZE];
    int seek_count = 0;

    // Sort the request array in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    int start, end;
    if (direction == 1) {
        start = head;
        end = SIZE - 1;
    } else {
        start = 0;
        end = head;
    }

    // Move the head to the end of the disk in the specified direction
    for (int i = start; i <= end; i++) {
        seek_sequence[seek_count++] = requests[i];
    }

    if (direction == 1) {
        seek_sequence[seek_count++] = SIZE - 1;
        seek_sequence[seek_count++] = 0;
    } else {
        seek_sequence[seek_count++] = 0;
        seek_sequence[seek_count++] = SIZE - 1;
    }

    // Move the head to the beginning of the disk in the specified direction
    for (int i = end; i >= start; i--) {
        seek_sequence[seek_count++] = requests[i];
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

    cscan(requests, n, head, direction);

    return 0;
}
