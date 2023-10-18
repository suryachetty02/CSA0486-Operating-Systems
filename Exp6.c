#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;            // Process ID
    int burst_time;    // Burst time
    int priority;      // Priority (lower values indicate higher priority)
    int remaining_time; // Remaining time
};

// Function to perform Preemptive Priority Scheduling
void preemptivePriorityScheduling(struct Process processes[], int n) {
    int total_time = 0;
    int completed = 0;

    while (completed < n) {
        int highest_priority = -1;
        int highest_priority_idx = -1;

        // Find the process with the highest priority among the ready processes
        for (int i = 0; i < n; i++) {
            if (processes[i].burst_time > 0 && processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                highest_priority_idx = i;
            }
        }

        if (highest_priority_idx == -1) {
            // No process is ready to run, increase total_time
            total_time++;
        } else {
            // Execute the process with the highest priority for 1 time unit
            processes[highest_priority_idx].burst_time--;
            total_time++;

            // If the process is completed, calculate turnaround and waiting time
            if (processes[highest_priority_idx].burst_time == 0) {
                completed++;
                int turnaround_time = total_time;
                int waiting_time = turnaround_time - processes[highest_priority_idx].remaining_time;
                printf("Process %d completed (Priority %d): Turnaround Time = %d, Waiting Time = %d\n",
                    processes[highest_priority_idx].id, processes[highest_priority_idx].priority, turnaround_time, waiting_time);
            }
        }
    }
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
        processes[i].remaining_time = processes[i].burst_time;
        printf("Enter priority for Process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    preemptivePriorityScheduling(processes, n);

    return 0;
}

