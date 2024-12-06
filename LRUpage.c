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

int findLRUIndex(int set[], int req[], int size, int curIdx)
{
    int lruIdx = -1;
    int mini = curIdx;
    for (int i = 0; i < size; i++)
    {
        int lastUsedIndex = -1;
        // find the idx at which set[i] was last time used
        for (int j = curIdx - 1; j >= 0; j--)
        {
            if (req[j] == set[i])
            {
                lastUsedIndex = j;
                break;
            }
        }
        // if it was not used earlier then this is the least recently used
        if (lastUsedIndex == -1)
        {
            return i;
        }
        if (lastUsedIndex < mini)
        {
            mini = lastUsedIndex;
            lruIdx = i;
        }
    }
    return lruIdx;
}

int pageFaults(int pages[], int req, int capacity)
{
    int set[capacity];
    int size = 0;
    int totalFaults = 0;
    for (int i = 0; i < req; i++)
    {
        int curPage = pages[i];
        if (isPagePresent(curPage, set, size) == true)
        {
            continue;
        }
        totalFaults++;
        if (size < capacity)
        {
            set[size++] = curPage;
        }
        else
        {
            int lruIndex = findLRUIndex(set, pages, size, i);
            set[lruIndex] = curPage;
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