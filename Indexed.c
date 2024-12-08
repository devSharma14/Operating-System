#include<stdio.h>
#include<stdbool.h>
#include<math.h>

typedef struct F {
    char name;
    int start;
    int size;
    int blocks[10];
    bool isAllocated;
} F;

int main() {
    int n;
    printf("Enter the no of files : ");
    scanf("%d", &n);
    F f[n];
    bool allocated[200];
    for(int i=0; i<200; i++) {
        allocated[i] = false;
    }
    for(int i=0; i<n; i++) {
        bool flag = true;
        getchar();
        printf("\nEnter name of file : ");
        scanf("%c", &f[i].name);
        
        printf("Enter starting block of file : ");
        scanf("%d", &f[i].start);
        
        printf("Enter no of blocks file : ");
        scanf("%d", &f[i].size);
        
        printf("Enter blocks of file : ");
        for(int j=0; j<f[i].size; j++) {
            int temp;
            scanf("%d", &temp);
            if(allocated[temp] == false) {
                allocated[temp] = true;
                f[i].blocks[j] = temp;
            }
            else {
                printf("Could not allocate block %d since it is already occupied. \n", temp);
                f[i].blocks[j] = -1;
                flag = false;
                break;
            }
        }
        if(flag) {
            f[i].isAllocated = true;
            printf("\nMemory successfully allocated of file %c.\n", f[i].name);
        }
        else {
            f[i].isAllocated = false;
            printf("\nMemory could not be allocated to file %c. \n", f[i].name);
        }
    }
    
    bool found = false;
    
    getchar();
    char key;
    printf("\nEnter the name of file to be searched : ");
    scanf("%c", &key);
    for(int i=0; i<n; i++) {
        if(f[i].name == key && f[i].isAllocated == true) {
            found = true;
            printf("File found. Details : \n");
            printf("Name : %c \t Starting block : %d \t Size : %d \n", f[i].name, f[i].start, f[i].size);
            printf("Blocks occupied : ");
            for(int j=0; j<f[i].size; j++) {
                if(f[i].blocks[j] != -1) {
                    printf("%d ", f[i].blocks[j]);
                }
            }
        }
    }
    if(!found) {
        printf("\nFile could not be found since it was not allocated any memory.\n");
    }
    printf("\nCode executed successfully. \n");
}