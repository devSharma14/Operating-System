#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main() {
    pid_t pid;
    pid = fork();
    if(pid < 0) {
        printf("Fork failed: Unable to create a child process \n");
        return 1;
    }
    else if(pid == 0) {
        printf("Parent process: \n");
        printf("Process ID: %d \n", getpid());
        printf("Child process ID: %d \n", pid);
        printf("Child process has finished execution \n");
    }
    return 0;
}