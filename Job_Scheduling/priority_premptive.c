#include <stdio.h>
#include <stdlib.h>

struct job
{
    int at;
    int bt;
    int jno;
    int priority;
};

struct gaant
{
    int st;
    int et;
    int jno;
};

int comparator(const void *p0, const void *p1)
{
    struct job *ps0 = (struct job *)p0;
    struct job *ps1 = (struct job *)p1;

    return ps0->at >= ps1->at;
}

struct job minimum(struct job *j, int size, int completed[], int csize)
{

    // initialize minimum with not completed job
    struct job min_p;
    for (int k = 0; k < size; k++)
    {
        int iflag = 0;
        for (int c = 0; c < csize; c++)
        {
            if (completed[c] == k)
            {
                iflag = 1;
                break;
            }
        }
        if (iflag == 0)
        {
            min_p = j[k];
            break;
        }
    }

    for (int i = 0; i < size; i++)
    {
        int flag = 0;
        struct job cjob = j[i];
        for (int c = 0; c < csize; c++)
        {
            if (completed[c] == cjob.jno)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            if (cjob.priority <= min_p.priority)
            {
                min_p = cjob;
            }
        }
    }
    return min_p;
}

void priority_premptive(struct job *j, int n, int total)
{
    qsort(j, n, sizeof(struct job), comparator);

    int rq_size = 9999999;
    int g_size = 99999;
    struct job *ready_queue = (struct job *)malloc(sizeof(struct job) * rq_size);
    struct gaant *g = (struct gaant *)malloc(sizeof(struct gaant) * g_size);
    int completed[n];

    int c = 0;
    int ctr = 0;

    // First job
    ready_queue[0] = j[0];
    int queue_counter = 1;

    // start time
    int t = ready_queue[0].at;
    struct job executing = ready_queue[0];

    g[ctr].st = t;
    g[ctr].jno = ready_queue[0].jno;

    while (t != total)
    {
        int completed_flag = 0;
        // Execution of current process
        for (int i = 1; i <= executing.bt; i++)
        {
            t += 1;

            // Check if a job arrives to ready queue during a process execution
            for (int k = 0; k < n; k++)
            {
                if (t == j[k].at)
                {
                    ready_queue[queue_counter] = j[k];
                    queue_counter += 1;
                }
            }

            // Check their burst times
            executing.bt = executing.bt - 1;

            if (executing.bt != 0)
            {
                struct job min = minimum(ready_queue, queue_counter, completed, c);

                if (min.priority < executing.priority)
                {
                    // Add remaining part of job back to ready queue
                    ready_queue[queue_counter] = executing;

                    queue_counter += 1;

                    // add executed part to gaant chart
                    g[ctr].et = t;
                    ctr += 1;
                    g[ctr].st = t;
                    g[ctr].jno = min.jno;

                    // Bring lowest priority job for processing
                    executing = min;
                    break;
                }
            }
            else
            {
                completed_flag = 1;
            }
        }

        // end the current running process
        if (completed_flag == 1)
        {
            g[ctr].et = t;
            completed[c] = g[ctr].jno;
            c += 1;

            // check if all processes are completed and get next job
            if (t != total)
            {
                // get the next job for execution-Highest priority
                executing = minimum(ready_queue, queue_counter, completed, c);
                ctr += 1;
                g[ctr].st = t;
                g[ctr].jno = executing.jno;
            }
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

    printf("Enter Priorities\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &j[i].priority);
    }

    struct gaant *f = (struct gaant *)malloc(sizeof(struct gaant) * n);
    priority_premptive(j, n, total_time);
}