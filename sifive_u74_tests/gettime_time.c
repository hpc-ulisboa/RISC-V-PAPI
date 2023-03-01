#include <stdio.h>
#include <time.h>

void subTimespec(struct timespec t1, struct timespec t2, struct timespec *td)
{
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec = t2.tv_sec - t1.tv_sec;
    if (td->tv_nsec < 0)
    {
        td->tv_nsec += 1000000000;
        td->tv_sec--;
    }
}

int main(int argc, char **argv)
{
    struct timespec start, finish, delta, dummy_start, dummy_finish;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    clock_gettime(CLOCK_MONOTONIC_RAW, &dummy_start);

    clock_gettime(CLOCK_MONOTONIC_RAW, &dummy_finish);
    clock_gettime(CLOCK_MONOTONIC_RAW, &finish);

    subTimespec(start, finish, &delta);
    printf("%d.%.9ld\n", (int)delta.tv_sec, delta.tv_nsec);
}