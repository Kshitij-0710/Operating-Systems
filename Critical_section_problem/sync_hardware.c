#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

bool lock_state = false;

bool test_and_set(bool *lock)
{
    bool old_value = *lock;
    *lock = true;

    return old_value;
}

void modify_shared_resource(int value)
{
    while (test_and_set(&lock_state))
        ;
    printf("Adding %d to the shared resource\n", value);

    lock_state = false;
}

int main()
{
    pid_t pid1, pid2;
    printf("This is some text\n");

    int val1 = 1;
    int val2 = 2;

    pid1 = fork();

    if (pid1 == 0)
    {
        modify_shared_resource(val1);
    }
    else
    {
        pid2 = fork();

        if (pid2 == 0)
        {
            modify_shared_resource(val2);
        }
        else
        {
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);

            printf("Final state of shared resource: %d,%d\n", val1, val2);
        }
    }
    return 0;
}