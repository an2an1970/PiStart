TARGET = pistart

CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRCS = pistart.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

distclean: clean
	rm -f *~ *.bak

help:
	@echo "Makefile commands:"
	@echo "  all       - Build the project"
	@echo "  clean     - Remove generated files"
	@echo "  distclean - Remove all generated files and backups"
	@echo "  help      - Show this help message"