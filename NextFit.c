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
    int lastIdx = 0;
    for(int i=0; i<n; i++) {
        int reqSize = p[i];
        bool found = false;
        for(int j=0; j<b; j++) {
            int idx = (j + lastIdx) % b;
            if(block[idx] >= reqSize) {
                found = true;
                lastIdx = (idx + 1) % b;
                printf("%d <-> %d (idx : %d) \n", p[i], block[idx], idx+1);
                block[idx] -= reqSize;
                break;
            }
        }
        if(!found) {
            printf("Could not memory to process : %d \n", p[i]);
        }
        
    }
}