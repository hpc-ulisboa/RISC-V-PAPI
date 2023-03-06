


# Compiler
CC=gcc

# Compiler flags
CFLAGS=-Wextra -Wall

# Compiler mode
MODE=-O0

INCLUDE=-I../../papi/include
PAPILIB=../src/libpapi.a

SRCS = 	gettime_time.c \
		papi_overhead.c \
		papi_total_time.c \
		perf_overhead.c \
		perf_total_time.c

PROGS = $(SRCS:.c=)

.PHONY : all

all : $(PROGS)

$(PROGS): % : %.c gemm.o
	$(CC) $(CFLAGS) $(MODE) $< gemm.o -o $@ $(INCLUDE) $(PAPILIB) -lm

sifive_u74_test: sifive_u74_test.c sifive_u74_events.h
	$(CC) $(CFLAGS) $(MODE) $< -o $@ $(INCLUDE) $(PAPILIB)

gemm.o : gemm.c gemm.h
	$(CC) $(CFLAGS) $(MODE) $< -c $@ -lm

clean:
	rm -f $(PROGS) gemm.o

