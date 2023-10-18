#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function to be executed by multiple threads
void *threadFunction(void *arg) {
    int thread_id = *((int *)arg);
    printf("Thread %d is running\n", thread_id);
    pthread_exit(NULL);
}

int main() {
    int num_threads = 5;
    pthread_t threads[num_threads];
    int thread_args[num_threads];

    // Create and run multiple threads
    for (int i = 0; i < num_threads; i++) {
        thread_args[i] = i;
        if (pthread_create(&threads[i], NULL, threadFunction, &thread_args[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < num_threads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    printf("All threads have completed.\n");

    return 0;
}

