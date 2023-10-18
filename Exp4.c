#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;            // Process ID
    int burst_time;    // Burst time
    int priority;      // Priority
};

// Function to perform Priority Scheduling
void priorityScheduling(struct Process processes[], int n) {
    int total_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // Sort the processes based on priority (smallest priority first)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                // Swap the processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    printf("Process Execution Order:\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst_time, total_time, total_time + processes[i].burst_time);
        total_waiting_time += total_time;
        total_turnaround_time += total_time + processes[i].burst_time;
        total_time += processes[i].burst_time;
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for Process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    priorityScheduling(processes, n);

    return 0;
}

