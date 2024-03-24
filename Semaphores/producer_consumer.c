#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;

int empty = 10;
int x = 0;

void producer()
{
    --mutex;
    ++full;
    --empty;
    x++;

    printf("\n Producer produces item %d\n", x);
    ++mutex;
}

void consumer()
{
    --mutex;
    --full;
    ++empty;

    printf("Consumer consumes item %d\n", x);
    x--;

    ++mutex;
}

int main()
{
    int n, i;
    printf("1------Producer\n");
    printf("2------Consumer\n");
    printf("3------Exit\n");

    while (1)
    {
        printf("Enter your choice\n");
        scanf("%d", &n);

        switch (n)
        {
        case 1:
            if ((mutex == 1) && empty != 0)
            {
                producer();
            }
            else
            {
                printf("Buffer is full");
            }
            break;
        case 2:
            if (mutex == 1 && full != 0)
            {
                consumer();
            }
            else
            {
                printf("Buffer is empty");
            }
            break;
        case 3:
            return 0;
        }
    }

    return 0;
}