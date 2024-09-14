CC = gcc
CFLAGS = -Wall -g
TARGET = clox

SRCS = main.c chunk.c memory.c debug.c
OBJS = main.o chunk.o memory.o debug.o

# Rule to build the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean rule to remove compiled files
clean:
	rm -f $(OBJS) $(TARGET)