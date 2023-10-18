#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
sem_t empty, full;

void* producer(void* arg) {
    int item;
    for (int i = 0; i < NUM_ITEMS; i++) {
        item = rand() % 100; // Generate a random item
        sem_wait(&empty);    // Wait if the buffer is full
        buffer[i % BUFFER_SIZE] = item;
        printf("Produced: %d\n", item);
        sem_post(&full);     // Signal that an item has been produced
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    int item;
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full);     // Wait if the buffer is empty
        item = buffer[i % BUFFER_SIZE];
        printf("Consumed: %d\n", item);
        sem_post(&empty);    // Signal that an item has been consumed
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    sem_init(&empty, 0, BUFFER_SIZE); // Initialize empty semaphore to buffer size
    sem_init(&full, 0, 0);           // Initialize full semaphore to 0

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for the threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
