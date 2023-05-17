#
# Copyright (c) 2023 INESC-ID, Instituto Superior Técnico, Universidade de Lisboa
# Created by Tiago Rocha <tiagolopesrocha@tecnico.ulisboa.pt>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy 
# of this software and associated documentation files (the "Software"), to deal 
# in the Software without restriction, including without limitation the rights 
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
# of the Software, and to permit persons to whom the Software is furnished to do so, 
# subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all 
# copies or substantial portions of the Software.  
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
# INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
# CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
# OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#


# Compiler
CC=gcc

# Compiler flags
CFLAGS=-Wextra -Wall

# Compiler mode
MODE=-O0

INCLUDE=-I${PAPI_INCLUDE}
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

