TARGET = KeyValueDB
OBJS =  KeyValueDB.o                   # This is for object-files
DEPS =  KeyValueDB.h makefile           # This is for header-files

CFLAGS = -O0

%.o: %.c $(DEPS)
	gcc -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

.phony:	clean
clean:
	rm -f *.o $(TARGET)
