# Originally created by Joel Adams, Calvin University
# Modified by Steven McKelvey, Calvin University
# Re-Utilized by Ryan Deaton, Calvin University for birthday Monte Carlo
# To build, enter: make

# name of the binary
PROGRAM   = Birthday

# source files
SRCS      = birthday.c lcrng.c

# object files from source files
OBJS      = $(SRCS:.c=.o)

# which compiler to use
CC        = mpicc

# flags for compilation and linking 
CFLAGS    = -I/usr/X11R6/include -Wall -fPIE
LFLAGS    = -L/usr/X11R6/lib -lm -fopenmp -fPIE

# Rules
.PHONY: clean

# valid file suffixes 
.SUFFIXES: .c .o .cpp

# Link object files
$(PROGRAM): $(OBJS)
	@echo "Linking $@..."
	@$(CC) $^ $(LFLAGS) -o $@ \
	|| { echo "Linking failed for $@"; exit 1; }
	@echo "Finished building $@"
	@echo " "

# command to build .o files from .c files
%.o: %.c
	@echo "Compiling $< to $@..."
	@$(CC) $(CFLAGS) -c $< -o $@ \
	|| { echo "Compiliation failed for $<"; exit 1; }
	@echo "Finished compiling $<"
	@echo " "

# other dependencies (based on #includes)
lcrng.o: lcrng.h

clean:
	/bin/rm -f $(OBJS) $(PROGRAM) *~ *#

