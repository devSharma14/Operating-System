#include<stdio.h>
#include<stdbool.h>
#include<math.h>

int main() {
    int n , b;
    printf("Enter the no of blocks : ");
    scanf("%d", &b);
    printf("Enter the no of processes : ");
    scanf("%d", &n);
    printf("Enter the size of blocks : ");
    int block[b] , p[n];
    for(int i=0; i<b; i++) {
        scanf("%d", &block[i]);
    }
    printf("Enter the size of processes : ");
    for(int i=0; i<n; i++) {
        scanf("%d", &p[i]);
    }
    for(int i=0; i<n; i++) {
        int reqSize = p[i];
        bool found = false;
        int idx = -1;
        int maxDiff = -1e8;
        for(int j=0; j<b; j++) {
            if(block[j] >= reqSize) {
                found = true;
                if(block[j] - reqSize > maxDiff) {
                    maxDiff = block[j] - reqSize;
                    idx = j;
                }
            }
        }
        if(found && idx != -1) {
            block[idx] -= reqSize;
            printf("%d <-> %d (idx : %d) \n", p[i], block[idx], idx+1);
        }
        else {
            printf("Could not allocate block to process %d.\n", p[i]);
        }
    }
}