#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct process
{
    int at, bt, st, ct, tat, wt, pid, rt;
} process;

int comparatorAT(const void *a, const void *b)
{
    int x = ((process *)a)->at;
    int y = ((process *)b)->at;
    return x - y;
}

int main()
{
    int n;
    printf("Enter the no of processes :  ");
    scanf("%d", &n);
    process p[n];
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
    }
    for (int i = 0; i < n; i++)
    {
        printf("Enter details of process %d: \n", i + 1);
        printf("Process ID | Arrival time | Burst time -> ");
        scanf("%d %d %d", &p[i].pid, &p[i].at, &p[i].bt);
    }
    qsort((void *)p, n, sizeof(process), comparatorAT);
    int curtime = 0, sum_tat = 0, sum_wt = 0;
    int completed = 0;
    int isCompleted[n];
    for (int i = 0; i < n; i++)
    {
        isCompleted[i] = false;
    }
    int gantt[100];
    int gantt_time[101];
    int iter = 0;
    while (completed != n)
    {
        int idx = -1; // selected
        int minbt = 1e8;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= curtime && isCompleted[i] == false)
            {
                if (p[i].bt < minbt)
                {
                    idx = i;
                    minbt = p[i].bt;
                }
            }
        }
        if (idx == -1)
        {
            curtime++;
        }
        else
        {
            gantt[iter] = p[idx].pid;
            gantt_time[iter] = curtime;
            iter++;
            p[idx].st = curtime;
            p[idx].ct = p[idx].st + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            sum_tat += p[idx].tat;
            sum_wt += p[idx].wt;
            curtime = p[idx].ct;
            completed++;
            isCompleted[idx] = true;
        }
    }
    gantt_time[iter] = curtime;
    printf("\nGantt chart:\n");
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
