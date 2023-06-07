CC = gcc
CCFLAGS = -std=c99 -Wall -Wextra -Wpedantic -O2
CCLIBS = -lSDL2
CFILES = $(shell find . -type f -name "*.c")
OUTFILE = ./imgview

all:
	$(CC) $(CFILES) -o $(OUTFILE) $(CCFLAGS) $(CCLIBS)
