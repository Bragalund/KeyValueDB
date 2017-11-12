TARGET = KeyValueDB
OBJS =  KeyValueDB.o NodeMethods.o Utils.o         # This is for object-files
DEPS =  KeyValueDB.h NodeMethods.h Utils.h         # This is for header-files

CFLAGS = -O0

%.o: %.c $(DEPS)
	gcc -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

.phony:	clean
clean:
	rm -f *.o $(TARGET)
