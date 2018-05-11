CC = clang
CFLAGS = -g

all: driver

clean:
	rm -f driver

driver: driver.c ui.c ui.h matrix.c matrix.h
	$(CC) $(CFLAGS) -o driver driver.c ui.c matrix.c -lncurses