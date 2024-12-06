#include <stdio.h>
#include <stdbool.h>

#define MAX 100

bool isPresent(int page, int set[], int size) {
    for (int i = 0; i < size; i++) {
        if (set[i] == page)
            return true;
    }
    return false;
}

void printQueue(int set[], int size) {
    printf("Queue state: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", set[i]);
    }
    printf("\n");
}

int pageFaults(int pages[], int n, int capacity) {
    int set[MAX];        
    int front = 0;       
    int page_faults = 0; 
    int size = 0;        
    for (int i = 0; i < n; i++) {
        if (!isPresent(pages[i], set, size)) {
            page_faults++; 
            if (size == capacity) {
                front = (front + 1) % capacity; 
            } else {
                size++; 
            }
            set[(front + size - 1) % capacity] = pages[i];
        }
        printQueue(set, size);
    }
    return page_faults;
}

int main() {
    int pages[MAX], n, capacity;
    printf("Enter number of frames available: ");
    scanf("%d", &capacity);
    printf("Enter number of requests: ");
    scanf("%d", &n);
    printf("Enter the page requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    int faults = pageFaults(pages, n, capacity);
    printf("Total number of page faults: %d\n", faults);
    return 0;
}
