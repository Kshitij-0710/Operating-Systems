#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define THREADS_COUNT 2

sem_t binary_semaphore;

void *thread_function(void *arg)
{
    sem_wait(&binary_semaphore);

    printf("Thread %ld accquired the semaphore\n", (long)arg);
    printf("Thread %ld released the semaphore \n", (long)arg);

    sem_post(&binary_semaphore);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[THREADS_COUNT];
    int rc;

    sem_init(&binary_semaphore, 0, 1);

    for (long i = 0; i < THREADS_COUNT; i++)
    {
        rc = pthread_create(&threads[i], NULL, thread_function, (void *)i);
        if (rc)
        {
            fprintf(stderr, "error: unable to create thread %ld\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < THREADS_COUNT; i++)
    {
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&binary_semaphore);
    return 0;
}