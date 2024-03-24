#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t *wrt = 1;
int mutex = 1;

int readers_count = 0;

void wait(sem_t *s)
{
    while (s == 0)
        ;
    s = s - 1;
}

void signal(sem_t *s)
{
    s = s + 1;
}

void writer()
{
    while (1)
    {
        wait(wrt);

        signal(wrt);
    }
}

void reader()
{
    while (1)
    {
        wait(mutex);

        readers_count++;
        if (readers_count == 1)
        {
            wait(wrt);
        }

        signal(mutex);

        wait(mutex);

        readers_count--;

        if (readers_count == 0)
        {
            signal(wrt);
        }
    }
    signal(mutex);
}

int main()
{
    int n;
    printf("1------Reader\n");
    printf("2------Writer\n");
    printf("3-------exit\n");

    while (1)
    {
        printf("enter your choice\n");
        scanf("%d", &n);

        switch (n)
        {
        case 1:
            reader();
            break;
        case 2:
            writer();
            break;
        case 3:
            return 0;
        }
    }

    return 0;
}