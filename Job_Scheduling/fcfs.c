#include <stdio.h>
#include <stdlib.h>

struct gaant
{
    int jno;
    int st;
    int et;
};

struct job
{
    int jno;
    int at;
    int bt;
};

int comparator(const void *p0, const void *p1)
{
    struct job *ps0 = (struct job *)p0;
    struct job *ps1 = (struct job *)p1;

    return ps0->at >= ps1->at;
}

struct gaant *fcfs(struct job *j, int n)
{
    qsort(j, n, sizeof(struct job), comparator);

    struct gaant *f = (struct gaant *)malloc(sizeof(struct gaant) * n);
    int prev = 0;

    // For the first job
    f[0].st = j[0].at;
    f[0].et = j[0].bt;
    f[0].jno = j[0].jno;

    // From 2nd job onwards
    for (int i = 1; i < n; i++)
    {
        f[i].jno = j[i].jno;
        f[i].st = f[i - 1].et;
        f[i].et = f[i].st + j[i].bt;
    }

    return f;
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
    }

    struct gaant *f = (struct gaant *)malloc(sizeof(struct gaant) * n);
    f = fcfs(j, n);

    printf("Job    Start     End\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d      %d       %d\n", f[i].jno + 1, f[i].st, f[i].et);
    }
}
