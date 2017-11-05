TARGET = main
OBJS =  main.o            # main.o md5.o FileReader.o FileWriter.o Util.o ValidateInput.o                        This is for object-files
DEPS =  main.h            # md5.h makefile FileReader.h FileWriter.h main.h Util.h ValidateInput.h               This is for header-files

CFLAGS = -O0

%.o: %.c $(DEPS)
	gcc -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

.phony:	clean
clean:
	rm -f *.o $(TARGET)
