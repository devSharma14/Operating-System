#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
int n = 1000, num_resources;
typedef struct Process
{
    int id;
    int allocated[100];
    int max[100];
    int needed[100];
} process;
void print(process ps[n])
{
    printf("PID \tAllocated \tMaximum \tNeeded\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t", ps[i].id);
        for (int j = 0; j < num_resources; j++)
            printf("%d  ", ps[i].allocated[j]);
        printf("\t");
        for (int j = 0; j < num_resources; j++)
            printf("%d  ", ps[i].max[j]);
        printf("\t");
        for (int j = 0; j < num_resources; j++)
            printf("%d  ", ps[i].needed[j]);
        printf("\n");
    }
}
bool isSafe(process ps[n], int available[num_resources], int sequence[n])
{
    int k = 0;
    bool proceed = true;
    bool finished[n];
    while (proceed)
    {
        proceed = false;
        for (int i = 0; i < n; i++)
        {
            if (finished[i] == false)
            {
                bool flag = true;
                for (int j = 0; j < num_resources; j++)
                {
                    if (ps[i].needed[j] > available[j])
                    {
                        flag = false;
                        break;
                    }
                }
                if (!flag)
                    continue;
                sequence[k++] = i;
                for (int j = 0; j < num_resources; j++)
                    available[j] += ps[i].allocated[j];
                finished[i] = true;
                proceed = true;
            }
        }
    }
    return k == n;
}
int main()
{
    printf("\nName\t: DEV SHARMA\nSection\t: A1\nRoll no : 21\n\n");
    printf("Number of processes : ");
    scanf("%d", &n);
    printf("Number of resources : ");
    scanf("%d", &num_resources);
    process ps[n];
    int total[num_resources], inUse[num_resources], available[num_resources];
    memset(inUse, 0, sizeof(inUse));
    memset(available, 0, sizeof(available));
    printf("Enter the total number of each resource available : ");
    for (int i = 0; i < num_resources; i++)
        scanf("%d", &total[i]);
    printf("Enter the allocated and maximum required resources\n");
    for (int i = 0; i < n; i++)
    {
        ps[i].id = i + 1;
        printf("P%d\t : ", ps[i].id);
        for (int j = 0; j < num_resources; j++)
        {
            scanf("%d", &ps[i].allocated[j]);
            inUse[j] += ps[i].allocated[j];
        }
        for (int j = 0; j < num_resources; j++)
            scanf("%d", &ps[i].max[j]);
        for (int j = 0; j < num_resources; j++)
            ps[i].needed[j] = ps[i].max[j] - ps[i].allocated[j];
    }
    for (int i = 0; i < num_resources; i++)
        available[i] = total[i] - inUse[i];
    print(ps);
    int sequence[n];
    if (isSafe(ps, available, sequence))
    {
        printf("\nSafe Sequence : ");
        for (int i = 0; i < n; i++)
            printf("P%d ", ps[sequence[i]].id);
        printf("\n");
    }
    else
        printf("\nNOT SAFE\n");
    return 0;
}
