


# Compiler
CC=gcc

# Compiler flags
CFLAGS=-Wextra -Wall

# Compiler mode
MODE=-g

INCLUDE=-I../../papi/include
PAPILIB=../src/libpapi.a

SRCS = 	papi_time.c \
		perf_time.c \
		no_count_time.c

PROGS = $(SRCS:.c=)

.PHONY : all

all : $(PROGS)

$(PROGS): % : %.c blackscholes.o
	$(CC) $(CFLAGS) $(MODE) $< blackscholes.o -o $@ $(INCLUDE) $(PAPILIB) -lm

sifive_u74_test: sifive_u74_test.c sifive_u74_events.h
	$(CC) $(CFLAGS) $(MODE) $< -o $@ $(INCLUDE) $(PAPILIB)

blackscholes.o : blackscholes.c
	$(CC) $(CFLAGS) $(MODE) $< -c $@ -lm

clean:
	rm -f $(PROGS) blackscholes.o

