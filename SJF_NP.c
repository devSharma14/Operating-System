#include <stdio.h>
#include <stdlib.h>

struct process
{
    int pid; // process id
    int at;  // arrival time
    int bt;  // burst time
    int st;  // start time
    int ct;  // completion time
    int tat; // turn around time
    int wt;  // waiting time
    int rt;  // remaining time
};

typedef struct process process;

int comparator(const void *a, const void *b)
{
    process *p1 = (process *)a;
    process *p2 = (process *)b;
    return p1->at - p2->at;
}

void printGanttChart(process arr[], int n)
{
    printf("\nGantt's Chart: \n");
    for (int i = 0; i < n; i++)
    {
        printf(" P%d |", arr[i].pid);
    }
    printf("\n");
    printf("0");
    for (int i = 0; i < n; i++)
    {
        printf("    %d", arr[i].ct);
    }
    printf("\n");
}

int main()
{
    int n;
    printf("Enter the number of processes -> ");
    scanf("%d", &n);
    process arr[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter details of process %d: \n", i + 1);
        printf("Process ID | Arrival time | Burst time -> ");
        scanf("%d %d %d", &arr[i].pid, &arr[i].at, &arr[i].bt);
        arr[i].rt = arr[i].bt; // Initialize remaining time as burst time
    }
    qsort(arr, n, sizeof(process), comparator);
    int completed = 0, curTime = 0;
    float total_wt = 0.0, total_tat = 0.0;
    int isCompleted[n]; // checks whether a process has been completed or not
    for (int i = 0; i < n; i++)
    {
        isCompleted[i] = 0;
    }
    int lastProcess = -1; // To check if a new process starts
    while (completed != n)
    {
        int min_rt = 1e9;
        int selected = -1;
        for (int i = 0; i < n; i++)
        {
            if (arr[i].at <= curTime && isCompleted[i] == 0)
            {
                if (arr[i].rt < min_rt)
                {
                    min_rt = arr[i].rt;
                    selected = i;
                }
                if (arr[i].rt == min_rt && arr[i].at < arr[selected].at)
                {
                    selected = i;
                }
            }
        }
        if (selected == -1)
        {
            curTime++;
        }
        else
        {
            if (lastProcess != selected)
            {
                arr[selected].st = curTime; // Start time is set only the first time the process is selected
            }
            curTime++;          // Move time forward by 1 unit
            arr[selected].rt--; // Decrement remaining time
            if (arr[selected].rt == 0)
            {
                arr[selected].ct = curTime;                              // Completion time
                arr[selected].tat = arr[selected].ct - arr[selected].at; // Turnaround time
                arr[selected].wt = arr[selected].tat - arr[selected].bt; // Waiting time

                total_wt += arr[selected].wt;
                total_tat += arr[selected].tat;
                isCompleted[selected] = 1; // Mark the process as completed
                completed++;               // Increment completed count
            }
            lastProcess = selected; // Keep track of the currently running process
        }
    }
    printGanttChart(arr, n);
    printf("\nAverage turnaround time : %.2f \n", total_tat / n);
    printf("\nAverage waiting time : %.2f \n", total_wt / n);
    return 0;
}
