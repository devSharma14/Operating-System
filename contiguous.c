#include<stdio.h>
#include<stdbool.h>

typedef struct F {
    char name;
    int start;
    int size;
    bool allocated;
} F;

typedef struct B {
    int blocks[200];
} B;

int main() {
    int n;
    printf("Enter the no of files : ");
    scanf("%d", &n);
    F f[n];
    B b;
    for(int i = 0; i < 200; i++) {
        b.blocks[i] = false;
    }
    for(int i = 0; i < n; i++) {
        getchar();
        printf("\nEnter name of file : ");
        scanf("%c", &f[i].name);
        
        printf("Enter starting block of file : ");
        scanf("%d", &f[i].start);
        
        printf("Enter no of blocks file : ");
        scanf("%d", &f[i].size);
        
        bool flag = true;
        int taken = -1;
        
        for(int j = f[i].start; j < f[i].start + f[i].size; j++) {
            if(b.blocks[j] == true) {  // Corrected here
                flag = false;
                taken = j;
                f[i].allocated = false;
                break;
            }
        }
        
        if(flag == false && taken != -1) {
            printf("Couldn't allocate memory to file %c since block %d is already occupied. \n", f[i].name, taken);
        } else {
            f[i].allocated = true;
            for(int j = f[i].start; j < f[i].start + f[i].size; j++) {
                b.blocks[j] = true;
            }
            printf("Memory successfully allocated to file %c. \n", f[i].name);
        }
    }
    
    getchar();
    char key;
    printf("Enter the name of file to be searched : ");
    scanf("%c", &key);
    bool found = false;
    for(int i = 0; i < n; i++) {
        if(f[i].name == key && f[i].allocated == true) {
            found = true;
            printf("File found. Details : \n");
            printf("Name : %c \t Starting block : %d \t Size : %d \n", f[i].name, f[i].start, f[i].size);
            printf("Blocks occupied : ");
            for(int j = f[i].start; j < f[i].start + f[i].size; j++) {
                printf("%d ", j);
            }
        }
    }
    if(!found) {
        printf("Could not find file : %c since no memory was allocated to it. \n", key);
    }
    printf("\nCode executed successfully. \n");
    return 0;
}