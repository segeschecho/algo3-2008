CC = g++
FLAGS=-g

all: cruces

# ejecutables
cruces: main.cpp GrafoBipartito.o Dibujo.o
	$(CC) $(FLAGS) -o cruces main.cpp GrafoBipartito.o Dibujo.o 

# objetos
Dibujo.o: Dibujo.cpp Dibujo.h GrafoBipartito.h
	$(CC) $(FLAGS) -c Dibujo.cpp

GrafoBipartito.o: GrafoBipartito.cpp GrafoBipartito.h
	$(CC) $(FLAGS) -c GrafoBipartito.cpp

clean:
	rm -f *.o
	rm -f cruces
