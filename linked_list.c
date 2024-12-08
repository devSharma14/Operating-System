#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 200

typedef struct File
{
    char name;
    int startblock;
    int length;
    int Blocks[10];
    int allocated;
}F;


typedef struct Disk
{
    int Blocks[MAX_SIZE];
}D;

D d;

int allocatefile(F f[],int i)
{
    int l=f[i].length;
    for(int j=0;j<l;j++)
    {   
        if(f[i].Blocks[j]>MAX_SIZE||d.Blocks[f[i].Blocks[j]]==1)
        {
            return 0;
        }
    }
    for(int j=0;j<l;j++)
    {   
        d.Blocks[f[i].Blocks[j]]=1;
    }
    return 1;
}



int main()
{
    int n;
    printf("Emter number of files : ");
    scanf("%d",&n);
    F f[n];
    for(int i=0;i<MAX_SIZE;i++)
    {
        d.Blocks[i]=0;
    }
    for(int i=0;i<n;i++)
    {
        getchar();
        printf("\n\nEnter file %d name : ",i+1);
        scanf("%c",&f[i].name);
        printf("Enter file %d start Block : ",i+1);
        scanf("%d",&f[i].startblock);
        printf("Enter number of blocks in file %d : ",i+1);
        scanf("%d",&f[i].length);
        printf("Enter Blocks for file %d : ",i+1);
        for(int j=0;j<f[i].length;j++)
        {
            scanf("%d",&f[i].Blocks[j]);
        }
        int a=allocatefile(f,i);
        if(a)
        {
            printf("File %d allocated",i+1);
            f[i].allocated=1;
        }
        else
        {
            printf("File %d not allocated",i+1);
            f[i].allocated=0;
        }
    }
    getchar();
    char key;
    printf("\n\nEnter name of file which you want to search : ");
    scanf("%c",&key);
    for(int i=0;i<n;i++)
    {
        if(f[i].allocated&&f[i].name==key)
        {
            printf("\nFile name : %c",f[i].name);
            printf("\nFile Staeting Block : %d",f[i].startblock);
            printf("\nNumber of Block in file : %d",f[i].length);
            printf("\nBlocks Occupied by file  : ");
            for(int j=0;j<f[i].length;j++)
            {
                printf("%d  ",f[i].Blocks[j]);
            }
            break;
        }
    }
}