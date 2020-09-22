CC = gcc
CFLAGS = -Wall -g
LDLIBS = -lm -lncurses
binaries = tellstones

all: tellstones

tellstones: tellstones.o

clean:
	rm -rf *.o

purge: clean
	rm -rf $(binaries)