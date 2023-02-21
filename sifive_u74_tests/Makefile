


# Compiler
CC=gcc

# Compiler flags
CFLAGS=-Wextra -Wall

# Compiler mode
MODE=-g

INCLUDE=-I../../papi/include
PAPILIB=../src/libpapi.a

SRCS = 	papi_no_time.c \
		papi_time.c \
		perf_no_time.c \
		perf_time.c \
		no_count_no_time.c \
		no_count_time.c

PROGS = $(SRCS:.c=)

.PHONY : all

all : $(PROGS)

$(PROGS): % : %.c black_scholes
	$(CC) $(CFLAGS) $(MODE) $< -o $@ $(INCLUDE) $(PAPILIB)

sifive_u74_test: sifive_u74_test.c sifive_u74_events.h
	$(CC) $(CFLAGS) $(MODE) $< -o $@ $(INCLUDE) $(PAPILIB)

black_scholes : blackscholes.c
	$(CC) $(CFLAGS) $(MODE) $< -o $@ -lm

clean:
	rm -f $(PROGS) black_scholes

