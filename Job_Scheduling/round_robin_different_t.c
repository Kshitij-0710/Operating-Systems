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

int comparator(const void *p0, const void *p1)
{
    struct job *ps0 = (struct job *)p0;
    struct job *ps1 = (struct job *)p1;

    return ps0->at >= ps1->at;
}

void round_robin(struct job *j, int n, int total)
{
    qsort(j, n, sizeof(struct job), comparator);

    int time_quantum = 3;
    int ctr = 0;
    struct job *ready_queue = (struct job *)malloc(sizeof(struct job) * 100);
    struct gaant *g = (struct gaant *)malloc(sizeof(struct gaant));

    int queue_counter = 0;
    int i = 0;

    // get first job
    ready_queue[queue_counter] = j[0];
    struct job executing = ready_queue[queue_counter];

    queue_counter += 1;
    int t = executing.at;
    g[ctr].st = t;
    g[ctr].jno = executing.jno;

    while (t != total)
    {
        if (executing.bt <= time_quantum)
        {
            for (int i = 1; i <= executing.bt; i++)
            {
                t += 1;

                // check for arrival of a new job
                for (int k = 0; k < n; k++)
                {
                    if (j[k].at == t)
                    {
                        // add the new process to ready queue
                        ready_queue[queue_counter] = j[k];
                        queue_counter += 1;
                    }
                }
            }
            // end the current executing process
            g[ctr].et = t;
        }
        else
        {
            for (int i = 1; i <= time_quantum; i++)
            {
                t += 1;

                // check for arrival of new job and add to ready queue.
                for (int k = 0; k < n; k++)
                {
                    if (j[k].at == t)
                    {
                        // add the new process to ready queue
                        ready_queue[queue_counter] = j[k];
                        queue_counter += 1;
                    }
                }
            }
            // add the time step to the process
            executing.bt = executing.bt - time_quantum;
            g[ctr].et = t;

            // add the current process to ready queue
            ready_queue[queue_counter] = executing;
            queue_counter += 1;
        }

        if (t != total)
        {
            ctr += 1;
            i += 1;

            // get the next process from ready queue
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