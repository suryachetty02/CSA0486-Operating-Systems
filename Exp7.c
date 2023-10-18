#include <stdio.h>

// Structure to represent a process
struct Process {
    int id;          // Process ID
    int arrival_time; // Arrival time
    int burst_time;   // Burst time
    int completion_time; // Completion time
    int turnaround_time; // Turnaround time
    int waiting_time;   // Waiting time
};

// Function to swap two processes
void swap(struct Process* a, struct Process* b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform SJF scheduling
void sjfScheduling(struct Process processes[], int n) {
    // Sort processes based on arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    int time = 0; // Current time
    int completed = 0; // Number of completed processes

    while (completed < n) {
        int shortest_job = -1;
        int shortest_burst = 9999;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].completion_time == -1) {
                if (processes[i].burst_time < shortest_burst) {
                    shortest_burst = processes[i].burst_time;
                    shortest_job = i;
                }
            }
        }

        if (shortest_job == -1) {
            time++;
        } else {
            processes[shortest_job].completion_time = time + processes[shortest_job].burst_time;
            time = processes[shortest_job].completion_time;
            completed++;
        }
    }

    // Calculate turnaround and waiting times
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for Process P%d: ", processes[i].id);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for Process P%d: ", processes[i].id);
        scanf("%d", &processes[i].burst_time);
        processes[i].completion_time = -1; // Initialize to -1
    }

    sjfScheduling(processes, n);

    printf("\nNon-Preemptive SJF Scheduling:\n");
    printf("-------------------------------\n");
    printf("Process  Arrival Time  Burst Time  Completion Time  Turnaround Time  Waiting Time\n");

    for (int i = 0; i < n; i++) {
        printf("  P%d        %d             %d              %d                  %d               %d\n",
               processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }

    return 0;
}
