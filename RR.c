#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include<math.h>

typedef struct process {
	int pid, bt, at, rt, tat, wt, st, ct;
} process;

typedef struct gantt {
	int pid, start_time, end_time;
} gantt;

int comparatorAT(const void* a, const void * b) {
	int x = ((process*)a)->at;
	int y = ((process*)b)->at;
	return x-y;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int comparatorPID(const void* a, const void * b) {
	int x = ((process*)a)->pid;
	int y = ((process*)b)->pid;
	return x - y;
}

int front = -1, rear = -1;

void enqueue(int q[], int val, int n) {
	if ((rear + 1) % n == front) {
		printf("Queue is full.\n");
		return;
	}
	if (front == -1) {
		front = 0;
	}
	rear = (rear + 1) % n;
	q[rear] = val;
}

bool isEmpty() {
	return front == -1;
}

int dequeue(int q[], int n) {
	if (isEmpty()) {
		printf("Queue is empty.\n");
		return -1;
	}
	int pid = q[front];
	if (front == rear) {
		front = rear = -1;
	} else {
		front = (front + 1) % n;
	}
	return pid;
}

int main() {
	printf("\nName\t: DEV SHARMA\nSection\t: A1\nRoll no : 21\n\n");
	int n;
	printf("Enter the number of processes: ");
	scanf("%d", &n);
	process arr[n];
	for (int i = 0; i < n; i++) {
		printf("Enter AT and BT of process %d separated by space: ", i + 1);
		scanf("%d %d", &arr[i].at, &arr[i].bt);
		arr[i].pid = i + 1;
	}
	qsort((void*)arr, n, sizeof(process), comparatorAT);
	int completed = 0;
	int q[n];
	bool vis[n];
	int remaining_bt[n];
	for (int i = 0; i < n; i++) remaining_bt[i] = arr[i].bt;
	for (int i = 0; i < n + 1; i++) q[i] = -1;
	for (int i = 0; i < n; i++) vis[i] = false;
	int tq;
	printf("Enter the time quantum: ");
	scanf("%d", &tq);
	int cur_time = 0, idx;
	int sum_tat = 0, sum_wt = 0, sum_rt = 0;
	gantt chart[100];
	int gantt_idx = 0;
	enqueue(q, 0, n);
	vis[0] = true;
	while (completed != n) {
		idx = dequeue(q, n);
		if (remaining_bt[idx] == arr[idx].bt) {
			arr[idx].st = max(cur_time, arr[idx].at);
			cur_time = arr[idx].st;
		}
		int start_time = cur_time;
		if (remaining_bt[idx] > tq) {
			remaining_bt[idx] -= tq;
			cur_time += tq;
		} else {
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
		int end_time = cur_time;
		chart[gantt_idx].pid = arr[idx].pid;
		chart[gantt_idx].start_time = start_time;
		chart[gantt_idx].end_time = end_time;
		gantt_idx++;
		for (int i = 0; i < n; i++) {
			if (remaining_bt[i] > 0 && arr[i].at <= cur_time && !vis[i]) {
				enqueue(q, i, n);
				vis[i] = true;
			}
		}
		if (remaining_bt[idx] > 0) {
			enqueue(q, idx, n);
		}
		if (isEmpty()) {
			for (int i = 0; i < n; i++) {
				if (remaining_bt[i] > 0 && !vis[i]) {
					enqueue(q, i, n);
					vis[i] = true;
					break;
				}
			}
		}
	}
	qsort((void*)arr, n, sizeof(process), comparatorPID);
	printf("\nAverage TAT: %.2f\n", (float)sum_tat / n);
	printf("Average WT: %.2f\n", (float)sum_wt / n);
	printf("Average RT: %.2f\n", (float)sum_rt / n);
	printf("\nGantt Chart:\n");
	for (int i = 0; i < gantt_idx; i++) {
		printf("| P%d [%d-%d] ", chart[i].pid, chart[i].start_time, chart[i].end_time);
	}
	printf("|\n");
	return 0;
}
