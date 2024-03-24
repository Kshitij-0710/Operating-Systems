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
    int no;
    int st;
    int et;
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
    struct job min_bt;
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
            min_bt = j[k];
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
            if (cjob.bt < min_bt.bt)
            {
                min_bt = cjob;
            }
        }
    }
    return min_bt;
}

struct gaant *sjf_npremptive(struct job *j, int n, int total)
{
    qsort(j, n, sizeof(struct job), comparator);

    int rq_size = 9999999;
    struct job *ready_queue = (struct job *)malloc(sizeof(struct job) * rq_size);
    struct gaant *g = (struct gaant *)malloc(sizeof(struct gaant) * n);
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
    g[ctr].no = ready_queue[0].jno;

    while (t != total)
    {
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
        }

        // end the current running process
        g[ctr].et = t;
        completed[c] = g[ctr].no;
        c += 1;

        // check if all processes are completed
        if (t != total)
        {
            // get the next job for execution-shortest burst time
            executing = minimum(ready_queue, queue_counter, completed, c);
            ctr += 1;
            g[ctr].st = t;
            g[ctr].no = executing.jno;
        }
    }
    return g;
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
    f = sjf_npremptive(j, n, total_time);

    printf("Job    Start     End\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d      %d       %d\n", f[i].no + 1, f[i].st, f[i].et);
    }
}
