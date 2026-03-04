CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC = src/guardian.c src/cpu.c src/memory.c src/logger.c

guardian:
	$(CC) $(CFLAGS) $(SRC) -o guardian

clean:
	rm -f guardian