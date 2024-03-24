#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *sum_square(void *data)
{
    int n = 10;

    char *name = (char *)data;
    printf("Executing thread %s\n", name);
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", i * i);
    }
    printf("\n");

    return NULL;
}

void *check_odd(void *data)
{
    int n = 20;

    char *name = (char *)data;
    printf("Executing thread %s\n", name);
    if (n % 2 == 0)
    {
        printf("The number is even\n");
    }
    else
    {
        printf("The number is odd\n");
    }

    return NULL;
}

void *average(void *data)
{
    int n = 5;
    char *name = (char *)data;
    printf("Executing thread %s\n", name);

    int arr[] = {
        20, 30, 40, 10, 5};
    int s = 0;
    for (int i = 0; i < n; i++)
    {
        s = s + arr[i];
    }

    // get average
    float avg = (double)(s / n);
    printf("Average : %f\n", avg);

    return NULL;
}

int main(void)
{
    pthread_t thread_1, thread_2, thread_3;
    pthread_create(&thread_1, NULL, sum_square, "Thread1");
    pthread_create(&thread_2, NULL, check_odd, "Thread2");
    pthread_create(&thread_3, NULL, average, "Thread3");
    sleep(10);

    return 0;
}