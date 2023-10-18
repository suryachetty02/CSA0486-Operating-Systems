#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define EATING_TIME 1
#define THINKING_TIME 2

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int philosopher_id = *(int *)arg;
    int left_fork = philosopher_id;
    int right_fork = (philosopher_id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking\n", philosopher_id);
        sleep(THINKING_TIME);

        // Pick up forks
        pthread_mutex_lock(&forks[left_fork]);
        pthread_mutex_lock(&forks[right_fork);

        // Eating
        printf("Philosopher %d is eating\n", philosopher_id);
        sleep(EATING_TIME);

        // Put down forks
        pthread_mutex_unlock(&forks[left_fork]);
        pthread_mutex_unlock(&forks[right_fork]);
    }
}

int main() {
    int i;
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize mutexes for forks
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        if (pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    // Wait for philosopher threads to finish (which will never happen in this simulation)
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (pthread_join(philosophers[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    return 0;
}

