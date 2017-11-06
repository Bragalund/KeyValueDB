TARGET = KeyValueDB
OBJS =  KeyValueDB.o sourcefiles/FileWriting.o sourcefiles/FileReading.o                    # This is for object-files
DEPS =  KeyValueDB.h makefile headerfiles/FileReading.h headerfiles/FileWriting.h           # This is for header-files

CFLAGS = -O0

%.o: %.c $(DEPS)
	gcc -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

.phony:	clean
clean:
	rm -f *.o $(TARGET)
