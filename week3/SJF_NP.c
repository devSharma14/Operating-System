#include<stdio.h>
#include<stdlib.h>


typedef struct Process
{
    int pid;
    int at;
    int bt;
    int st,ct,rt,tat,wt;
}P;

int main()
{
    int n;
    printf("Enter number of processes : ");
    scanf("%d",&n);
    P p[n];

    printf("\nEnter attributes of processes : \n");
    for(int i=0;i<n;i++)
    {
        printf("\nEnter PID of process : ");
        scanf("%d",&p[i].pid);
        printf("Enter arrival time of process : ");
        scanf("%d",&p[i].at);
        printf("Enter burst time of process : ");
        scanf("%d",&p[i].bt);
    }   

    int complete_process=0;
    int curr_time=0;
    int is_completed[n];
    int total_rt=0,total_tat=0,total_wt=0;
    for(int i=0;i<n;i++)
    {
        is_completed[i]=0;
    }


    while(complete_process<n)
    {   
        int min_idx=-1;
        int MIN=1e8;
        for(int i=0;i<n;i++)
        {
            if(MIN>p[i].bt&&p[i].at<=curr_time&&is_completed[i]==0)
            {
                MIN=p[i].bt;
                min_idx=i;
            }

            if(MIN==p[i].bt&&is_completed[i]==0)
            {
                if(p[i].at<p[min_idx].at)
                {
                    min_idx=i;
                }
            }
        }
            if(min_idx==-1)
            {
                curr_time++;
            }
            else
            {
                p[min_idx].st=curr_time;
                p[min_idx].ct=curr_time+p[min_idx].bt;
                p[min_idx].rt=p[min_idx].st-p[min_idx].at;
                total_rt+=p[min_idx].rt;
                p[min_idx].tat=p[min_idx].ct-p[min_idx].at;
                total_tat+=p[min_idx].tat;
                p[min_idx].wt=p[min_idx].tat-p[min_idx].bt;
                total_wt+=p[min_idx].wt;
                curr_time+=p[min_idx].bt;
                is_completed[min_idx]=1;
                complete_process++;
            }
    }
    printf("\nAvg. RT : %.2f",(total_rt*1.0)/n);
    printf("\nAvg. TAT : %.2f",(total_tat*1.0)/n);
    printf("\nAvg. WT : %.2f",(total_wt*1.0)/n);
}