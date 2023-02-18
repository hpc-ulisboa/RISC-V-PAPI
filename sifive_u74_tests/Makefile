


# Compiler
CC=gcc

# Compiler flags
CFLAGS=-Wextra -Wall

# Compiler mode
MODE=-g

INCLUDE=-I../papi/include

ALL = event_exception_taken event_integer_load_retired

PAPILIB=../papi-risc-v/src/libpapi.a

.PHONY : all

all: $(ALL)

event_exception_taken: event_exception_taken.c
	$(CC) $(CFLAGS) $(MODE) event_exception_taken.c -o event_exception_taken $(INCLUDE) $(PAPILIB)

event_integer_load_retired: event_integer_load_retired.c
	$(CC) $(CFLAGS) $(MODE) event_integer_load_retired.c -o event_integer_load_retired $(INCLUDE) $(PAPILIB)

clean:
	rm -f $(ALL)
