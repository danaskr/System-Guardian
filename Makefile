CC      = gcc
CFLAGS  = -Wall -Wextra -pedantic -std=c11
TARGET  = guardian
SRCDIR  = src
SRCS    = $(SRCDIR)/guardian.c $(SRCDIR)/cpu.c $(SRCDIR)/memory.c $(SRCDIR)/logger.c
OBJS    = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(SRCDIR) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) guardian.log