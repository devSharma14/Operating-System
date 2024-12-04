#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int main() {
    int n,r;
    printf("Enter no of resources : ");
    scanf("%d",&n);
    printf("Enter the no of process : ");
    scanf("%d",&r);
    int resources[r];
    printf("Enter resource vector : \n");
    for(int i=0; i<r; i++) {
        scanf("%d",&resources[i]);
    }
    int allocated[n][r];
    bool vis[n];
    for(int i=0; i<n; i++)  vis[i] = false;
    printf("Enter allocation matrix : \n");
    for(int i=0; i<n; i++) {
        for(int j=0; j<r; j++) {
            scanf("%d",&allocated[i][j]);
        }
    }
    int required[n][r];
    int safe[100];
    int iter = 0;
    printf("Enter required matrix : \n");
    for(int i=0; i<n; i++) {
        for(int j=0; j<r; j++) {
            scanf("%d",&required[i][j]);
        }
    }
    int remaining[n][r];
    for(int i=0; i<n; i++) {
        for(int j=0; j<r; j++) {
            remaining[i][j] = required[i][j] - allocated[i][j];

        }
    }

    int completed = 0;
    while(completed != n) {
        int idx = -1;
        for(int i=0; i<n; i++) {
            bool flag = true;
            for(int j=0; j<r; j++) {
                if(resources[j] < remaining[i][j]) {
                    flag = false;
                    break;
                }
            }
            if(flag) {
                idx = i;
            }
        }
        if(idx == -1) {
            printf("Deadlock occured \n");
        }
        vis[idx] = true;
    }
}