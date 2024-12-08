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

int findLRUIndex(int size, int curIdx, int page[], int set[]) {
    int lruIdx = -1;
    int minIdx = curIdx;
    for(int i=0; i<size; i++) {
        int lastUsed = -1;
        for(int j=curIdx-1; j>=0; j--) {
            if(page[j] == set[i]) {
                lastUsed = j;
                break;
            }
        }
        if(lastUsed == -1) {
            return i;
        }
        if(lastUsed < minIdx) {
            lruIdx = i;
            minIdx = lastUsed;
        }
    }
    return lruIdx;
}

int pageFaults(int n, int req, int page[]) {
    int set[n];
    int size = 0;
    int total = 0;
    for(int i=0; i<req; i++) {
        int curPage = page[i];
        if(isPresent(curPage, size, set)) {
            continue;
        }
        total++;
        if(size < n) {
            set[size] = curPage;
            size++;
        }
        else {
            int lruIdx = findLRUIndex(size, i, page, set);
            set[lruIdx] = curPage;
        }
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