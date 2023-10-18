#include <stdio.h>

// Process structure to store process information
struct Process {
    int pid;     // Process ID
    int burst;   // Burst time
};

int main() {
    // Define the processes
    struct Process processes[3];
    processes[0].pid = 1;
    processes[0].burst = 6;
    processes[1].pid = 2;
    processes[1].burst = 8;
    processes[2].pid = 3;
    processes[2].burst = 7;

    // Calculate completion times
    int n = sizeof(processes) / sizeof(processes[0]);
    int completionTime[n];
    int currentTime = 0;
    
    for (int i = 0; i < n; i++) {
        currentTime += processes[i].burst;
        completionTime[i] = currentTime;
    }

    // Calculate turnaround time and waiting time
    int turnaroundTime[n];
    int waitingTime[n];

    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = completionTime[i];
        waitingTime[i] = turnaroundTime[i] - processes[i].burst;
    }

    // Calculate average turnaround time and average waiting time
    float avgTurnaroundTime = 0;
    float avgWaitingTime = 0;

    for (int i = 0; i < n; i++) {
        avgTurnaroundTime += turnaroundTime[i];
        avgWaitingTime += waitingTime[i];
    }

    avgTurnaroundTime /= n;
    avgWaitingTime /= n;

    // Display the results
    printf("Process\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst, completionTime[i], turnaroundTime[i], waitingTime[i]);
    }

    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", avgWaitingTime);

    return 0;
}

