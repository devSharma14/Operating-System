#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    int b, n;
    printf("Enter the number of blocks available: ");
    scanf("%d", &b);
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int blocks[b];
    int process[n];
    printf("Enter sizes of blocks: ");
    for (int i = 0; i < b; i++)
    {
        scanf("%d", &blocks[i]);
    }
    printf("Enter sizes of processes: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &process[i]);
    }
    for (int i = 0; i < n; i++)
    {
        int requiredSize = process[i];
        int minIdx = -1; 
        int minDiff = 1e8; 
        bool flag = false;
        for (int j = 0; j < b; j++)
        {
            if (blocks[j] >= requiredSize)
            {
                flag = true;
                if (blocks[j] - requiredSize < minDiff)
                {
                    minDiff = blocks[j] - requiredSize;
                    minIdx = j;
                }
            }
        }
        if (flag && minIdx != -1)
        {
            blocks[minIdx] -= requiredSize;
            printf("Process %d (%d) allocated to block %d.\n", i + 1, process[i], minIdx + 1);
        }
        else
        {
            printf("Could not allocate block to process %d.\n", i + 1);
        }
    }
    return 0;
}