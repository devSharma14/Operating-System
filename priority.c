#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct process
{
    int pid, at, bt, rt, wt, tat, st, ct, priority;
} process;

int comparator(const void *a, const void *b)
{
    if (((process *)a)->at != ((process *)b)->at)
    {
        return ((process *)a)->at - ((process *)b)->at;
    }
    return ((process *)a)->priority - ((process *)b)->priority;
}

int main()
{
    int n;
    printf("Enter the no of processes : ");
    scanf("%d", &n);
    process p[n];
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
    }
    for (int i = 0; i < n; i++)
    {
        printf("Enter details of process %d: \n", i + 1);
        printf("Arrival time | Burst time | Priority -> ");
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
    }
    qsort((void *)p, n, sizeof(process), comparator);
    int completed = 0, sum_tat = 0, sum_wt = 0;
    bool isCompleted[n];
    for (int i = 0; i < n; i++)
        isCompleted[i] = false;
    int curtime = 0;
    int gantt[100];
    int gantt_time[101];
    int iter = 0;
    while (completed != n)
    {
        int idx = -1;
        int mini = 1e8;
        for (int i = 0; i < n; i++)
        {
            if (isCompleted[i] == false && p[i].at <= curtime)
            {
                if (p[i].priority < mini)
                {
                    idx = i;
                    mini = p[i].priority;
                }
            }
        }
        if (idx == -1)
        {
            curtime++;
            continue;
        }
        gantt[iter] = p[idx].pid;
        gantt_time[iter] = curtime;
        iter++;

        p[idx].st = curtime;
        p[idx].ct = p[idx].st + p[idx].bt;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        completed++;
        isCompleted[idx] = true;
        curtime = p[idx].ct;
        sum_tat += p[idx].tat;
        sum_wt += p[idx].wt;
    }
    gantt_time[iter] = curtime;
    printf("\nGantt's chart:\n");
    for (int i = 0; i < iter; i++)
    {
        printf("   P%d   ", gantt[i]);
    }
    printf("\n");
    for (int i = 0; i <= iter; i++)
    {
        printf("%d       ", gantt_time[i]);
    }
    printf("\n\nAverage turnaround time : %f \n", (float)sum_tat / n);
    printf("Average waiting time : %f \n", (float)sum_wt / n);
    return 0;
}
