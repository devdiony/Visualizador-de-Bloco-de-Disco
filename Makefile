CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -g
TARGET=blkdump

all: $(TARGET)

$(TARGET): blkdump.c
	$(CC) $(CFLAGS) -o $(TARGET) blkdump.c

clean:
	rm -f $(TARGET)

