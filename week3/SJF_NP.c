#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid;    // process id
    int at;     // arrival time
    int bt;     // burst time   
    int st;     // start time
    int ct;     // completion time
    int tat;    // turn around time
    int wt;     // waiting time
};

typedef struct process process;

int comparator(const void *a, const void *b) {
    process *p1 = (process *)a;
    process *p2 = (process *)b;
    return p1->at - p2->at; 
}

void printGanttChart(process arr[], int n) {
    printf("\nGantt's Chart: \n");
    for(int i=0; i<n; i++) {
        printf(" P%d |", arr[i].pid);
    }
    printf("\n");
    printf("0");
    for(int i=0; i<n; i++) {
        printf("    %d", arr[i].ct);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of processes -> ");
    scanf("%d", &n);

    process arr[n];

    for(int i=0; i<n; i++) {
        printf("Enter details of process %d: \n", i+1);
        printf("Process ID -> ");
        scanf("%d", &arr[i].pid);
        printf("Arrival time -> ");
        scanf("%d", &arr[i].at);
        printf("Burst time -> ");
        scanf("%d", &arr[i].bt);
    }

    // sorting acc to at
    qsort(arr, n, sizeof(process), comparator);

    int completed = 0, curTime = 0;
    float total_wt = 0.0 , total_tat = 0.0;

    int isCompleted[n]; // checks whether a process has been completed or not

    for(int i=0; i<n; i++) {
        isCompleted[i] = 0;
    }

    while(completed != n) {
        int min_bt = 1e9;
        int selected = -1;

        for(int i=0; i<n; i++) {
            if(arr[i].at <= curTime && isCompleted[i] == 0) {
                if(arr[i].bt < min_bt) {
                    min_bt = arr[i].bt;
                    selected = i;
                }
            }
        }

        if(selected == -1) {
            curTime++;
        }
        else {
            arr[selected].st = curTime;
            arr[selected].ct = arr[selected].st + arr[selected].bt;
            arr[selected].tat = arr[selected].ct - arr[selected].at;
            arr[selected].wt = arr[selected].tat - arr[selected].bt;

            total_wt += arr[selected].wt;
            total_tat += arr[selected].tat;

            curTime = arr[selected].ct;
            isCompleted[selected] = 1;
            completed++;
        }
    }

    printf("\nProcess\tAT\tBT\tST\tCT\tTAT\tWT\n");
    for(int i=0; i<n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", arr[i].pid, arr[i].at, arr[i].bt, arr[i].st, arr[i].ct, arr[i].tat, arr[i].wt);
    }

    printGanttChart(arr, n);

    printf("\nAverage turnaround time : %.2f \n", total_tat/n);
    printf("\nAverage waiting time : %.2f \n", total_wt/n);

    return 0;
}
