/* This file attempts to test the performance of the EXCEPTION_TAKEN event */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "papi.h"
#include "sifive_u74_events.h"

int main(int argc, char **argv)
{
        int retval = 0;
        int eventset = PAPI_NULL;
        long long count;
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char fileName[100];
        sprintf(fileName, "EventCounts_%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

        // Open file to write results with date and time on the file name
        FILE *f = fopen(fileName, "w");

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

        for (int i = 0; i < 35; i++)
        {
                // Add event from event list
                retval = PAPI_add_named_event(eventset, event_list[i]);
                if (retval != PAPI_OK)
                {
                        fprintf(stderr, "Faield to add %s to eventset\n", event_list[i]);
                        exit(EXIT_FAILURE);
                }

                // Reset counter value
                PAPI_reset(eventset);

                // Start counting
                PAPI_start(eventset);

                // Test code
                system("stress-ng --cpu 1 --cpu-method trig -t 60s");

                // Stop counting and read the count value
                retval = PAPI_stop(eventset, &count);

                if (retval != PAPI_OK)
                {
                        fprintf(stderr, "Failed to read %s count\n", event_list[i]);
                        exit(EXIT_FAILURE);
                }

                fprintf(f, "%s : %lld\n", event_list[i], count);

                // Clean event set for next event
                retval = PAPI_cleanup_eventset(eventset);
                if (retval != PAPI_OK)
                {
                        fprintf(stderr, "Eventset cleanup failed\n");
                        exit(EXIT_FAILURE);
                }
        }

        exit(EXIT_SUCCESS);
}
