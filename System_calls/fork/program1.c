#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    printf("Srinitish Srinivasan 21BAI1394");

    for (int i = 0; i < 4; i++)
    {
        if (fork() == 0)
        {
            printf("Child ID is %d\n", getpid());
            printf("Parent ID is %d\n", getppid());
            exit(0);
        }
    }
    for (int i = 0; i < 4; i++)
    {
        wait(NULL);
    }
    return 0;
}