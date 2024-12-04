#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main()
{
    int pipefds[2];
    char writeMsg[] = "Message from Child", readMsg[100];
    if (pipe(pipefds) == -1)
        perror("Pipe failed");
    return 1;
    pid_t pid = fork();
    if (pid < 0)
        perror("Fork failed");
    return 1;
    if (pid == 0)
    {
        close(pipefds[0]);
        write(pipefds[1], writeMsg, strlen(writeMsg) + 1);
        close(pipefds[1]);
    }
    else
    {
        close(pipefds[1]);
        read(pipefds[0], readMsg, sizeof(readMsg));
        printf("Parent read: %s\n", readMsg);
        close(pipefds[0]);
    }
    return 0;
}
