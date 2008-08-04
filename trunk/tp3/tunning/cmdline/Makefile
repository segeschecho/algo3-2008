FLAGS=-g

all: cmdline.o

cmdline.o: CmdLine.h CmdLine.cpp
	g++ -c $(FLAGS) CmdLine.cpp -o cmdline.o

clean:
	rm -f cmdline.o
