#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int main()
{
    pid_t child_pid;

    child_pid = fork();

    if (child_pid > 0)
    {
        printf("I am the parent having parent ID: %d, and i have a child having child ID :%d\n", getpid(), child_pid);
        printf("I am the child having child ID %d, and i have a parent having parent ID:%d\n", child_pid, getpid());
        sleep(10);
    }
    else if (child_pid == 0)
    {
        exit(0);
    }
    else
    {
        printf("Fork failed.");
        return 1;
    }
    printf("I am the parent having parent ID: %d, and i have a zombie process having zombie ID :%d\n", getpid(), child_pid);

    return 0;
}