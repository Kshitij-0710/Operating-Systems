#include <stdio.h>
#include <stdlib.h>

struct job
{
    int jno;
    int at;
    int bt;
};

struct gaant
{
    int jno;
    int st;
    int et;
};

void round_robin(struct job *j, int n, int total)
{
    int time_quantum = 2;
    int ctr = 0;
    struct job *ready_queue = (struct job *)malloc(sizeof(struct job) * 100);
    struct gaant *g = (struct gaant *)malloc(sizeof(struct gaant) * 100);

    // add all jobs to ready queue
    int queue_counter = 0;
    for (int i = 0; i < n; i++)
    {
        ready_queue[queue_counter] = j[i];
        queue_counter++;
    }

    // get first executing job
    struct job executing = ready_queue[0];
    int t = executing.at;

    g[ctr].st = t;
    g[ctr].jno = executing.jno;

    int i = 0;
    while (t != total)
    {
        if (executing.bt <= time_quantum)
        {
            // end the process
            t = t + executing.bt;
            g[ctr].et = t;
        }
        else
        {
            // add timestep to process
            t = t + time_quantum;
            executing.bt = executing.bt - time_quantum;
            g[ctr].et = t;

            // add current process to ready queue.
            ready_queue[queue_counter] = executing;
            queue_counter += 1;
        }

        if (t != total)
        {
            ctr += 1;
            i += 1;

            // get next process from ready queue.
            executing = ready_queue[i];
            g[ctr].st = t;
            g[ctr].jno = executing.jno;
        }
    }
    printf("Job    Start     End\n");
    for (int i = 0; i < ctr + 1; i++)
    {
        printf("%d      %d       %d\n", g[i].jno + 1, g[i].st, g[i].et);
    }
}

int main()
{
    int n;

    printf("Enter Number of jobs\n");
    scanf("%d", &n);

    int total_time = 0;

    struct job *j = (struct job *)malloc(sizeof(struct job) * n);

    printf("Enter arrival times\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &j[i].at);
        j[i].jno = i;
    }

    printf("Enter burst times\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &j[i].bt);
        total_time += j[i].bt;
    }

    struct gaant *f = (struct gaant *)malloc(sizeof(struct gaant) * n);
    round_robin(j, n, total_time);
}