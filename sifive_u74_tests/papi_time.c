/* This file attempts to test the performance of the EXCEPTION_TAKEN event */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#include "papi.h"

int main(int argc, char **argv)
{
        int retval = 0;
        int eventset = PAPI_NULL;
        long long count;
        struct timeval begin, end;
        long seconds, microseconds;
        double elapsed;

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
        retval = PAPI_add_named_event(eventset, "PAPI_TOT_INS");
        if (retval != PAPI_OK)
        {
                fprintf(stderr, "Faield to add %s to eventset\n", "PAPI_TOT_INS");
                exit(EXIT_FAILURE);
        }

        // Reset counter value
        PAPI_reset(eventset);

        // Start counting
        PAPI_start(eventset);

        gettimeofday(&begin, 0);

        // TODO: Test code

        gettimeofday(&end, 0);

        // Stop counting and read the count value
        retval = PAPI_stop(eventset, &count);

        if (retval != PAPI_OK)
        {
                fprintf(stderr, "Failed to read %s count\n", "PAPI_TOT_INS");
                exit(EXIT_FAILURE);
        }

        printf("%lld\n", count);

        seconds = end.tv_sec - begin.tv_sec;
        microseconds = end.tv_usec - begin.tv_usec;
        elapsed = seconds + microseconds * 1e-6;
        printf("%.3f\n", elapsed);

        PAPI_shutdown();

        exit(EXIT_SUCCESS);
}
