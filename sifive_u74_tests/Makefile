


# Compiler
CC=gcc

# Compiler flags
CFLAGS=-Wextra -Wall

# Compiler mode
MODE=-O0

INCLUDE=-I../../papi/include
PAPILIB=../src/libpapi.a

SRCS = 	gettime_time.c \
		kernel_time.c \
		papi_close_time.c \
		papi_count_time.c \
		papi_init_time.c \
		papi_start_time.c \
		papi_stop_time.c \
		papi_total_time.c \
		perf_close_time.c \
		perf_count_time.c \
		perf_init_time.c \
		perf_start_time.c \
		perf_stop_time.c \
		perf_total_time.c

PROGS = $(SRCS:.c=)

.PHONY : all

all : $(PROGS)

$(PROGS): % : %.c blackscholes.o gemm.o
	$(CC) $(CFLAGS) $(MODE) $< blackscholes.o gemm.o -o $@ $(INCLUDE) $(PAPILIB) -lm

sifive_u74_test: sifive_u74_test.c sifive_u74_events.h
	$(CC) $(CFLAGS) $(MODE) $< -o $@ $(INCLUDE) $(PAPILIB)

blackscholes.o : blackscholes.c
	$(CC) $(CFLAGS) $(MODE) $< -c $@ -lm

gemm.o : gemm.c gemm.h
	$(CC) $(CFLAGS) $(MODE) $< -c $@ -lm

clean:
	rm -f $(PROGS) blackscholes.o gemm.o

