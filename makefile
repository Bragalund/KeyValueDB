TARGET = Main
OBJS =  Main.o NodeMethods.o Utils.o         # This is for object-files
DEPS =  Main.h NodeMethods.h Utils.h         # This is for header-files

CFLAGS = -O0

%.o: %.c $(DEPS)
	gcc -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

.phony:	clean
clean:
	rm -f *.o $(TARGET)
