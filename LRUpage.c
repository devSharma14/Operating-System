#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

void printQueue(int set[], int size) {
    printf("\nState of queue: \n");
    for(int i=0; i<size; i++) {
        printf("%d ",set[i]);
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

int findLRUIndex(int set[], int curIdx, int size, int page[]) {
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
            minIdx = lastUsed;
            lruIdx = i;
        }
    }
    return lruIdx;
}

int pageFaults(int capacity, int req, int pages[]) {
    int set[capacity];
    int size = 0;
    int total = 0;
    for(int i=0; i<req; i++) {
        int curPage = pages[i];
        if(isPresent(curPage, size, set)) {
            // if page is already isPresent
            continue;
        }
        else {
            // inr page fault
            total++;
            if(size < capacity) {
                set[size] = curPage;
                size++;
            }
            else {
                // replace krna padega
                int lruIdx = findLRUIndex(set, i, size, pages);
                set[lruIdx] = curPage;
            }
        }
        printQueue(set, size);
    }
    return total;
}

int main() {
    int n;
    printf("Enter no of frames : ");
    scanf("%d", &n);
    int req;
    printf("Enter the no of page requests : ");
    scanf("%d", &req);
    printf("Enter page requests : ");
    int page[req];
    for(int i=0; i<req; i++) {
        scanf("%d", &page[i]);
    }
    int result = pageFaults(n, req, page);
    printf("Total no of page faults are : %d \n", result);
    return 0;
}
