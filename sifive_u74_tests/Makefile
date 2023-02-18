


# Compiler
CC=gcc

# Compiler flags
CFLAGS=-Wextra -Wall

# Compiler mode
MODE=-g

INCLUDE=-I../../papi/include
PAPILIB=../src/libpapi.a

SRCS = event_exception_taken event_integer_load_retired
PROGS = $(SRCS:.c=)

.PHONY : all

all: $(PROGS)

$(PROGS): % : %.c
        $(CC) $(CFLAGS) $(MODE) $< -o $@ $(INCLUDE) $(PAPILIB)

clean:
      	rm -f $(PROGS)

