#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct File
{
    char name;
    int startBlock;
    int numBlocks;
    int blocks[200]; // Stores the actual block numbers
} File;

int main()
{
    int n;
    printf("Enter the number of files: ");
    scanf("%d", &n);

    File files[n];
    bool memoryBlocks[200] = {false}; // Represents the availability of memory blocks

    for (int i = 0; i < n; i++)
    {
        getchar(); // Clear the buffer
        printf("Enter name of the file: ");
        scanf(" %c", &files[i].name);
        printf("Enter the starting block of the file: ");
        scanf("%d", &files[i].startBlock);
        printf("Enter the number of blocks in the file: ");
        scanf("%d", &files[i].numBlocks);

        printf("Enter the blocks for the file: ");
        for (int j = 0; j < files[i].numBlocks; j++)
        {
            int block;
            scanf("%d", &block);
            if (!memoryBlocks[block])
            {
                memoryBlocks[block] = true;
                files[i].blocks[j] = block;
            }
            else
            {
                printf("Block %d is already occupied. Allocation failed.\n", block);
                files[i].blocks[j] = -1; // Mark as invalid block
            }
        }
        printf("Memory successfully allocated for file %c.\n", files[i].name);
    }

    char searchFile;
    getchar(); // Clear the buffer
    printf("Enter the file name to be searched: ");
    scanf(" %c", &searchFile);

    bool found = false;
    for (int i = 0; i < n; i++)
    {
        if (files[i].name == searchFile)
        {
            found = true;
            printf("File Name\tStart Block\tNo. of Blocks\tBlocks Occupied\n");
            printf("%c\t\t%d\t\t%d\t\t", files[i].name, files[i].startBlock, files[i].numBlocks);
            for (int j = 0; j < files[i].numBlocks; j++)
            {
                if (files[i].blocks[j] != -1)
                {
                    printf("%d ", files[i].blocks[j]);
                }
            }
            printf("\n");
            break;
        }
    }

    if (!found)
    {
        printf("File not found.\n");
    }

    return 0;
}
