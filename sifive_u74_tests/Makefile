


# Compiler
CC=gcc

# Compiler flags
CFLAGS=-Wextra -Wall

# Compiler mode
MODE=-g

INCLUDE=-I../../papi/include
PAPILIB=../src/libpapi.a

.PHONY : sifive_u74_test

sifive_u74_test: sifive_u74_test.c sifive_u74_events.h
	$(CC) $(CFLAGS) $(MODE) $< -o $@ $(INCLUDE) $(PAPILIB)

clean:
	rm -f sifive_u74_test

