/* This file attempts to test the performance of the EXCEPTION_TAKEN event */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "papi.h"

int main(int argc, char **argv) {

        int retval = 0;
        int eventset = PAPI_NULL;
        long long count[1];

        retval = PAPI_library_init(PAPI_VER_CURRENT);
        if (retval != PAPI_VER_CURRENT) {
                fprintf(stderr, "PAPI library init failed\n");
                exit(EXIT_FAILURE);
        }

        retval=PAPI_create_eventset(&eventset);
        if (retval!=PAPI_OK) {
                fprintf(stderr, "Eventset creation failed\n");
                exit(EXIT_FAILURE);
        }

        retval=PAPI_add_named_event(eventset,"INTEGER_LOAD_RETIRED");
        if (retval!=PAPI_OK) {
                fprintf(stderr, "Faield to add event to eventset\n");
                exit(EXIT_FAILURE);
        }

        /* TEST CODE */
        
        PAPI_reset(eventset);
        PAPI_start(eventset);

        // Some test code here

        retval = PAPI_stop(eventset, count);

        if (retval != PAPI_OK) {
                fprintf(stderr, "Failed to read INTEGER LOAD RETIRED count");
                exit(EXIT_FAILURE);
        }

        printf("Exeptions taken : %lld \n", count[0]);

        exit(EXIT_SUCCESS);
}
