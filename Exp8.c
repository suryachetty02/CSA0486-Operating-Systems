#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
struct Process {
    int id;          // Process ID
    int burst_time;  // Burst time
    int remaining_time; // Remaining time to complete
};

// Function to perform Round Robin scheduling
void roundRobinScheduling(struct Process processes[], int n, int time_quantum) {
    int time = 0; // Current time
    int completed = 0; // Number of completed processes

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                // Execute the process for the time quantum or the remaining time, whichever is smaller
                int execute_time = (processes[i].remaining_time < time_quantum) ? processes[i].remaining_time : time_quantum;
                time += execute_time;
                processes[i].remaining_time -= execute_time;

                printf("Process P%d is running for %d time units.\n", processes[i].id, execute_time);

                if (processes[i].remaining_time == 0) {
                    completed++;
                    printf("Process P%d completed.\n", processes[i].id);
                }
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int time_quantum;
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter burst time for Process P%d: ", processes[i].id);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("\nRound Robin Scheduling:\n");
    printf("-----------------------\n");
    printf("Time  Process  Burst Time\n");

    roundRobinScheduling(processes, n, time_quantum);

    return 0;
}
