#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 10

typedef struct
{
    int buffer[BUFFER_SIZE];
    pthread_mutex_t mutex;
    int count;

    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} monitor_t;

void monitor_init(monitor_t *monitor)
{
    monitor->count = 0;
    pthread_mutex_init(&monitor->mutex, NULL);
    pthread_cond_init(&monitor->not_empty, NULL);
    pthread_cond_init(&monitor->not_full, NULL);
}

void monitor_insert(monitor_t *monitor, int value)
{
    pthread_mutex_lock(&monitor->mutex);

    while (monitor->count >= BUFFER_SIZE)
    {
        pthread_cond_wait(&monitor->not_full, &monitor->mutex);
    }
    monitor->buffer[monitor->count++] = value;
    pthread_cond_signal(&monitor->not_empty);

    pthread_mutex_unlock(&monitor->mutex);
}

int monitor_remove(monitor_t *monitor)
{
    int value;
    pthread_mutex_lock(&monitor->mutex);

    while (monitor->count == 0)
    {
        pthread_cond_wait(&monitor->not_empty, &monitor->mutex);
    }
    value = monitor->buffer[--monitor->count];
    pthread_cond_signal(&monitor->not_full);
    pthread_mutex_unlock(&monitor->mutex);

    return value;
}

void *producer(void *arg)
{
    monitor_t *monitor = (monitor_t *)arg;

    for (int i = 0; i < BUFFER_SIZE * 2; i++)
    {
        monitor_insert(monitor, i);
        printf("Producer inserted : %d\n", i);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    monitor_t *monitor = (monitor_t *)arg;
    int value;

    for (int i = 0; i < BUFFER_SIZE * 2; i++)
    {
        value = monitor_remove(monitor);
        printf("Consumer removed : %d\n", value);
    }
    pthread_exit(NULL);
}

int main()
{
    monitor_t monitor;
    pthread_t producer_thread, consumer_thread;

    monitor_init(&monitor);
    pthread_create(&producer_thread, NULL, producer, &monitor);
    pthread_create(&consumer_thread, NULL, consumer, &monitor);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
}
