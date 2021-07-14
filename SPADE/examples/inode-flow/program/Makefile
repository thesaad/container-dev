CCC = gcc
LIB = -lpthread

compile_reader:
	$(CCC) reader.c $(LIB) -o reader.o

compile_writer:
	$(CCC) writer.c $(LIB) -o writer.o

compile: compile_reader compile_writer

clean:
	rm -f *.o

all: compile

run:
	sudo ./writer.o
	sudo ./reader.o
