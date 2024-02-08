CC=gcc
CFLAGS=-Wall -Wextra -pedantic -ansi
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
TARGET=othello.exe

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)