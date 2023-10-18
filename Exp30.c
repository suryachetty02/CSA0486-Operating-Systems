#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* threadFunction(void* arg) {
    int threadNumber = *(int*)arg;
    printf("Thread %d created. Thread ID: %lu\n", threadNumber, pthread_self());

    // Simulate work by sleeping for a user-specified time
    unsigned int sleepTime;
    printf("Enter sleep time for Thread %d (in seconds): ", threadNumber);
    scanf("%u", &sleepTime);
    sleep(sleepTime);

    printf("Thread %d finished.\n", threadNumber);
    pthread_exit(NULL);
}

int main() {
    int numThreads;

    printf("Enter the number of threads: ");
    scanf("%d", &numThreads);

    pthread_t threads[numThreads];
    int threadNumbers[numThreads];

    for (int i = 0; i < numThreads; i++) {
        threadNumbers[i] = i;
        if (pthread_create(&threads[i], NULL, threadFunction, &threadNumbers[i]) != 0) {
            printf("Failed to create Thread %d.\n", i);
            exit(1);
        }
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
        printf("Thread %d joined and finished.\n", i);
    }

    return 0;
}
