#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

void printQueue(int set[], int size)
{
    printf("\nState of queue : \n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", set[i]);
    }
    printf("\n");
}

bool isPagePresent(int page, int set[], int size)
{
    bool flag = false;
    for (int i = 0; i < size; i++)
    {
        if (set[i] == page)
        {
            return true;
        }
    }
    return false;
}

int pageFaults(int pages[], int req, int capacity)
{
    int set[capacity];
    int size = 0;
    int totalFaults = 0;
    int front = 0;
    for (int i = 0; i < req; i++)
    {
        int curPage = pages[i];
        if (isPagePresent(curPage, set, size) == true)
        {
            continue;
        }
        else
        {
            // check if queue is full or not
            totalFaults++;
            if (size == capacity)
            {
                front = (front + 1) % capacity;
            }
            else
            {
                size++;
            }
            set[(front + size - 1) % capacity] = curPage;
        }
        printQueue(set, size);
    }
    return totalFaults;
}

int main()
{
    int n;
    printf("Enter no of frames available : ");
    scanf("%d", &n);
    int req;
    printf("Enter the number of page requests : ");
    scanf("%d", &req);
    int pages[req];
    printf("Enter the page requests : \n");
    for (int i = 0; i < req; i++)
    {
        scanf("%d", &pages[i]);
    }
    int result = pageFaults(pages, req, n);
    printf("Total no of page faults : %d \n", result);
}