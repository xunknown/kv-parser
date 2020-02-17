TARGET=kv-parser.elf
SRC=$(wildcard ./*.c)
OBJ=$(patsubst ./%.c, ./%.o, $(SRC))

CC=gcc
CFLAGS=
LDFLAGS=

.PHONY:all clean

all:clean $(TARGET)

$(TARGET):$(OBJ)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
