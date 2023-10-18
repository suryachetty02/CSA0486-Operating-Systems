#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

void fcfs(int requests[], int n, int head) {
    int seek_sequence[SIZE];
    int seek_count = 0;

    for (int i = 0; i < n; i++) {
        seek_sequence[i] = requests[i];
        seek_count += abs(head - requests[i]);
        head = requests[i];
    }

    printf("Seek Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", seek_sequence[i]);
    }

    printf("\nTotal Seek Time = %d\n", seek_count);
}

int main() {
    int requests[SIZE];
    int n, head;

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

    fcfs(requests, n, head);

    return 0;
}
