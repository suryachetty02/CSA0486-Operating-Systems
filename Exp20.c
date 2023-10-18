#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t readSemaphore, writeSemaphore;
int data = 0;
int readersCount = 0;

void *reader(void *arg) {
    int readerID = *((int *)arg);
    while (1) {
        sleep(1); // Simulate reading

        sem_wait(&readSemaphore);
        readersCount++;
        if (readersCount == 1) {
            sem_wait(&writeSemaphore);
        }
        sem_post(&readSemaphore);

        printf("Reader %d is reading data: %d\n", readerID, data);

        sem_wait(&readSemaphore);
        readersCount--;
        if (readersCount == 0) {
            sem_post(&writeSemaphore);
        }
        sem_post(&readSemaphore);
    }
    return NULL;
}

void *writer(void *arg) {
    int writerID = *((int *)arg);
    while (1) {
        sleep(1); // Simulate writing

        sem_wait(&writeSemaphore);
        data++;
        printf("Writer %d is writing data: %d\n", writerID, data);
        sem_post(&writeSemaphore);
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int readerIDs[NUM_READERS];
    int writerIDs[NUM_WRITERS];

    sem_init(&readSemaphore, 0, 1);
    sem_init(&writeSemaphore, 0, 1);

    for (int i = 0; i < NUM_READERS; i++) {
        readerIDs[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &readerIDs[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        writerIDs[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writerIDs[i]);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&readSemaphore);
    sem_destroy(&writeSemaphore);

    return 0;
}

