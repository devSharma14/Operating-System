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
    int blocks[b], process[n];
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
    int lastAllocatedBlock = 0; // Keeps track of the last allocated block
    for (int i = 0; i < n; i++)
    {
        int requiredSize = process[i];
        bool allocated = false;
        // Start searching from the last allocated block
        for (int j = 0; j < b; j++)
        {
            int idx = (lastAllocatedBlock + j) % b; // Wrap around using modulo
            if (blocks[idx] >= requiredSize)
            {
                blocks[idx] -= requiredSize;
                printf("Process %d (%d) allocated to block %d. Remaining block size: %d\n",
                       i + 1, process[i], idx + 1, blocks[idx]);
                lastAllocatedBlock = idx; // Update last allocated block
                allocated = true;
                break;
            }
        }
        if (!allocated)
        {
            printf("Could not allocate block to process %d.\n", i + 1);
        }
    }
    return 0;
}
