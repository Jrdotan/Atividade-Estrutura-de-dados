TARGET = Stack1

CC = gcc


all: $(TARGET)

$(TARGET): stack1.c sds.c
	$(CC) $(CFLAGS) stack1.c sds.c -o $(TARGET)

clean:
	rm -f $(TARGET)
