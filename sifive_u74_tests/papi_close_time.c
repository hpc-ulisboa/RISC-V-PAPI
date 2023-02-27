/* This file attempts to test the performance of the EXCEPTION_TAKEN event */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "papi.h"
#include "blackscholes.h"

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
        int retval = 0;
        int eventset = PAPI_NULL;
        long long count;
        struct timespec start, finish, delta;

        // Initialize PAPI library
        retval = PAPI_library_init(PAPI_VER_CURRENT);
        if (retval != PAPI_VER_CURRENT)
        {
                fprintf(stderr, "PAPI library init failed\n");
                exit(EXIT_FAILURE);
        }

        // Create an eventset
        retval = PAPI_create_eventset(&eventset);
        if (retval != PAPI_OK)
        {
                fprintf(stderr, "Eventset creation failed\n");
                exit(EXIT_FAILURE);
        }

        // Add event from event list
        retval = PAPI_add_named_event(eventset, "PAPI_TOT_CYC");
        if (retval != PAPI_OK)
        {
                fprintf(stderr, "Faield to add %s to eventset\n", "PAPI_TOT_CYC");
                exit(EXIT_FAILURE);
        }

        // Reset counter value
        PAPI_reset(eventset);

        // Start counting
        PAPI_start(eventset);

        // kernel();

        // Stop counting and read the count value
        retval = PAPI_stop(eventset, &count);

        if (retval != PAPI_OK)
        {
                fprintf(stderr, "Failed to read %s count\n", "PAPI_TOT_CYC");
                exit(EXIT_FAILURE);
        }

        printf("%lld\n", count);

        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        PAPI_shutdown();
        clock_gettime(CLOCK_MONOTONIC_RAW, &finish);
        subTimespec(start, finish, &delta);

        printf("%d.%.9ld\n", (int)delta.tv_sec, delta.tv_nsec);

        exit(EXIT_SUCCESS);
}
