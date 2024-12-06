#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct p
{
    char name;
    int start;
    bool isAllocated;
    int size;
} p;

typedef struct allocationManager
{
    int blocks[200];
} allocationManager;

void allocateFile(p *file, allocationManager *allocManager)
{
    int startIdx = file->start;
    bool flag = true;

    for (int i = startIdx; i < file->start + file->size; i++)
    {
        if (allocManager->blocks[i] == 1)
        {
            flag = false;
            break;
        }
    }

    if (flag)
    {
        for (int i = startIdx; i < file->start + file->size; i++)
        {
            allocManager->blocks[i] = 1;
        }
        printf("Memory successfully allocated to the file.\n");
    }
    else
    {
        printf("Memory could not be allocated to the file.\n");
    }
}

int main()
{
    int n;
    printf("Enter the number of files: ");
    scanf("%d", &n);

    p P[n];
    allocationManager allocManager;

    // Initialize the allocation blocks to 0 (free)
    for (int i = 0; i < 200; i++)
    {
        allocManager.blocks[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        getchar();
        printf("Enter name of the file: ");
        scanf(" %c", &P[i].name);
        printf("Enter the starting block of the file: ");
        scanf("%d", &P[i].start);
        printf("Enter size of the file: ");
        scanf("%d", &P[i].size);
        allocateFile(&P[i], &allocManager);
    }

    char key;
    getchar();
    printf("Enter the name of the file that you want to search: ");
    scanf(" %c", &key);

    bool flag = false;
    for (int i = 0; i < n; i++)
    {
        if (P[i].name == key)
        {
            flag = true;
            printf("Details of file are: \n");
            printf("Name: %c \t Start: %d \t Ending block: %d \n", P[i].name, P[i].start, P[i].start + P[i].size - 1);
            printf("Blocks allocated: ");
            for (int j = P[i].start; j < P[i].start + P[i].size; j++)
            {
                printf("%d ", j);
            }
            printf("\n");
            break;
        }
    }

    if (!flag)
    {
        printf("File not found.\n");
    }

    return 0;
}
