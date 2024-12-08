#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

void printQueue(int size, int set[]) {
    printf("\nState of queue : ");
    for(int i=0; i<size; i++) {
        printf("%d ", set[i]);
    }
    printf("\n");
}

bool isPresent(int page, int size, int set[]) {
    for(int i=0; i<size; i++) {
        if(set[i] == page) {
            return true;
        }
    }
    return false;
}

int pageFaults(int n, int req, int page[]) {
    int set[n];
    int size = 0;
    int total = 0;
    int front = 0;
    for(int i=0; i<req; i++) {
        int curPage = page[i];
        if(isPresent(curPage, size, set)) {
            continue;
        }
        total++;
        if(size == n) {
            front = (front + 1) % n;
        }
        else {
            size++;
        }
        set[(front + size - 1) % n] = curPage;
        printQueue(size, set);
    }
    return total;
}

int main() {
    int n, req;
    printf("Enter no of frames : ");
    scanf("%d", &n);
    printf("Enter no of page requests : ");
    scanf("%d", &req);
    printf("Enter the size of page requests : ");
    int page[req];
    for(int i=0; i<req; i++) {
        scanf("%d", &page[i]);
    }
    int res = pageFaults(n, req, page);
    printf("Total no of page faults are : %d \n", res);
}