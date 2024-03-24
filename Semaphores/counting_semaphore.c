#include <stdio.h>
#include <pthread.h>

typedef struct
{
    int count;
    pthread_mutex_t lock;
    pthread_cond_t cond;

} counting_semaphore_t;

void counting_semaphore_init(counting_semaphore_t *sem, int initial_count)
{
    sem->count = initial_count;
    pthread_mutex_init(&sem->count, NULL);
    pthread_cond_init(&sem->cond, NULL);
}

void counting_semaphore_wait(counting_semaphore_t *sem)
{
    pthread_mutex_lock(&sem->lock);
    while (sem->count <= 0)
    {
        pthread_cond_wait(&sem->cond, &sem->lock);
    }

    sem->count--;
    pthread_mutex_unlock(&sem->lock);
}

void counting_semaphore_signal(counting_semaphore_t *sem)
{
    pthread_mutex_lock(&sem->lock);
    sem->count++;

    pthread_cond_signal(&sem->cond);
    pthread_mutex_unlock(&sem->lock);
}

void *thread_func(void *arg)
{
    counting_semaphore_t *sem = (counting_semaphore_t *)arg;

    printf("Thread waiting on semaphore\n");
    counting_semaphore_wait(sem);
    printf("Thread acquired semaphore\n");
    printf("Thread releasing semaphore\n");

    counting_semaphore_signal(sem);
    return NULL;
}

int main()
{
    counting_semaphore_t sem;
    counting_semaphore_init(&sem, 3);
    pthread_t threads[5];

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&threads[i], NULL, thread_func, &sem);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}