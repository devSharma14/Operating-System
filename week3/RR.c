#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>

int front = -1, rear = -1;

typedef struct process {
    int pid;
    int at;
    int bt;
    int st, ct, tat, wt, rt;    // start | completion | turnaround | waiting | response
} process;

int max(int a, int b) {
    return (a>b) ? a : b;
}

int comparatorAT(const void* a, const void* b) {
    int x = ((process*)a)->at;
    int y = ((process*)b)->at;
    return x-y;
}

int comparatorPID(const void* a, const void* b) {
    int x = ((process*)a)->pid;
    int y = ((process*)b)->pid;
    return x-y;
}

bool isEmpty() {
    return front==-1;
}

void enqueue(int q[], int pid, int n) {
    if((rear+1)%n == front) {
        printf("Cannot insert since queue is full. \n");
        return;
    }
    if(front == -1) {
        front = 0;
    }
    rear = (rear+1)%n;
    q[rear] = pid;
}

int dequeue(int q[], int n) {
    if(isEmpty()) {
        return -1;
    }
    int pid = q[front];
    if(front == rear) {
        front = rear = -1;
    }
    else {
        front = (front+1)%n;
    }
    return pid;
}

int main() {
    printf("\n");
    int n;
    printf("Enter the number of processes -> ");
    scanf("%d", &n);
    process arr[n];
    int remaining_bt[n];
    int tq = 0;
    bool vis[n];
    int completed = 0;
    int cur_time = 0;
    bool is_first = true;
    int q[n+1];
    int sum_tat = 0 , sum_wt = 0 , sum_rt = 0;

    for(int i=0; i<n; i++) {
        printf("Enter arrival time and burst time of process : %d separated by a space -> ",i+1);
        scanf("%d", &arr[i].at);
        scanf("%d", &arr[i].bt);
        arr[i].pid = i;
        remaining_bt[i] = arr[i].bt;
    }
    
    printf("Enter the time quantum -> ");
    scanf("%d",&tq);
    
    for(int i=0; i<n; i++) {
        vis[i] = false;
    }

    for(int i=0; i<n+1; i++) {
        q[i] = -1;
    }

    qsort((void*)arr, n, sizeof(process), comparatorAT);

    enqueue(q, arr[0].pid, n);
    vis[0] = true;
    int idx;

    while(completed != n) {
        idx = dequeue(q, n);
        if(idx  == -1) {
            int next_at = 1e8;
            for(int i=0; i<n; i++) {
                if(remaining_bt[i] > 0 && arr[i].at > cur_time) {
                    next_at = max(next_at, arr[i].at);
                }
            }
            cur_time = next_at;
            continue;
        }

        if(remaining_bt[idx] == arr[idx].bt) {
            arr[idx].st = max(cur_time, arr[idx].at);
            is_first = false;
            cur_time = arr[idx].st;
        }

        if(remaining_bt[idx] > tq) {
            remaining_bt[idx] -= tq;
            cur_time += tq;
        }
        else {
            cur_time += remaining_bt[idx];
            remaining_bt[idx] = 0;
            completed++;
            arr[idx].ct = cur_time;
            arr[idx].tat = arr[idx].ct - arr[idx].at;
            arr[idx].wt = arr[idx].tat - arr[idx].bt;
            arr[idx].rt = arr[idx].st - arr[idx].at;

            sum_tat += arr[idx].tat;
            sum_wt += arr[idx].wt;
            sum_rt += arr[idx].rt;
        }

        for(int i=0; i<n; i++) {
            if(arr[i].at <= cur_time && remaining_bt[i] > 0 && vis[i] == false) {
                enqueue(q, i, n);
                vis[i] = true;
            }
        }

        if(remaining_bt[idx] > 0) {
            enqueue(q, idx, n);
        }

        if(isEmpty()) {
            for(int i=1; i<n; i++) {
                if(remaining_bt[i] > 0 && vis[i] == false) {
                    enqueue(q, i, n);
                    vis[i] = true;
                    break;
                }
            }
        }
    }

    qsort((void*)arr, n, sizeof(process), comparatorPID);

    printf("\n");

    printf("PID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\t");
    printf("\n");
    for(int i=0; i<n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", arr[i].pid, arr[i].at, arr[i].bt, arr[i].st, arr[i].ct, arr[i].tat, arr[i].wt, arr[i].rt);
    }

    printf("\nAverage Turnaround Time: %.2f", (float)sum_tat / n);
    printf("\nAverage Waiting Time: %.2f", (float)sum_wt / n);
    printf("\nAverage Response Time: %.2f", (float)sum_rt / n);

    printf("\n");
    return 0;
}