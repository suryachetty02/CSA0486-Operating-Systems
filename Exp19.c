#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Define a global mutex
pthread_mutex_t mutex;

// Shared resource
int sharedResource = 0;

// Function for the first thread
void *thread1_function(void *arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex); // Lock the mutex

        // Critical section: Increment the shared resource
        sharedResource++;
        printf("Thread 1: Incremented sharedResource to %d\n", sharedResource);

        pthread_mutex_unlock(&mutex); // Unlock the mutex

        // Simulate some work
        sleep(1);
    }

    return NULL;
}

// Function for the second thread
void *thread2_function(void *arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex); // Lock the mutex

        // Critical section: Decrement the shared resource
        sharedResource--;
        printf("Thread 2: Decremented sharedResource to %d\n", sharedResource);

        pthread_mutex_unlock(&mutex); // Unlock the mutex

        // Simulate some work
        sleep(1);
    }

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialize the mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Mutex initialization failed.\n");
        return 1;
    }

    // Create threads
    if (pthread_create(&thread1, NULL, thread1_function, NULL) != 0 ||
        pthread_create(&thread2, NULL, thread2_function, NULL) != 0) {
        printf("Thread creation failed.\n");
        return 1;
    }

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    printf("Both threads have completed.\n");
    return 0;
}

