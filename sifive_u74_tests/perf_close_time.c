#include <stdlib.h>
#include <linux/perf_event.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

#include "blackscholes.h"

#define READ_BUFFER_SIZE 771

static long
perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags)
{
    int ret;
    ret = syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags);

    return ret;
}

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
    struct perf_event_attr pe;
    long long buffer[READ_BUFFER_SIZE];
    int cnt = 0, fd, retval = 0;

    struct timespec start, finish, delta;

    memset(&pe, 0, sizeof(struct perf_event_attr));
    memset(&buffer, 0, READ_BUFFER_SIZE * sizeof(long long));

    pe.type = PERF_TYPE_HARDWARE;
    pe.config = PERF_COUNT_HW_CPU_CYCLES;
    pe.read_format = 8;

    fd = perf_event_open(&pe, 0, -1, -1, 0);
    if (fd == -1)
    {
        fprintf(stderr, "Error opening leader %lld\n", pe.config);
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    retval = ioctl(fd, PERF_EVENT_IOC_RESET, NULL);
    if (retval == -1)
    {
        fprintf(stderr, "ioctl(PERF_EVENT_RESET) failed");
        exit(EXIT_FAILURE);
    }

    retval = ioctl(fd, PERF_EVENT_IOC_ENABLE, NULL);
    if (retval == -1)
    {
        fprintf(stderr, "ioctl(PERF_EVENT_ENABLE) failed");
        exit(EXIT_FAILURE);
    }

    // kernel();

    retval = ioctl(fd, PERF_EVENT_IOC_DISABLE, NULL);
    if (retval == -1)
    {
        fprintf(stderr, "ioctl(PERF_EVENT_DISABLE) failed");
        exit(EXIT_FAILURE);
    }

    cnt = read(fd, buffer, sizeof(buffer));
    if (cnt == -1)
    {
        printf("%d", errno);
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // printf("%lld\n", buffer[1]);

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    close(fd);
    clock_gettime(CLOCK_MONOTONIC_RAW, &finish);

    subTimespec(start, finish, &delta);
    printf("%d.%.9ld\n", (int)delta.tv_sec, delta.tv_nsec);
}
