CC = gcc
CFLAGS = -g -fsanitize=address -fno-omit-frame-pointer -O3
TARGET = clox

SRCS = main.c chunk.c object.c memory.c debug.c value.c vm.c compiler.c scanner.c table.c
OBJS = main.o chunk.o object.o memory.o debug.o value.o vm.o compiler.o scanner.o table.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)