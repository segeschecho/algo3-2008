CC = g++
FLAGS=-g

all: ej1

# ejecutables
ej1: main.cpp Grafo.o 
	$(CC) $(FLAGS) main.cpp Grafo.o -o torneo

# objetos
Grafo.o: Grafo.cpp Grafo.h
	$(CC) $(FLAGS) -c Grafo.cpp

clean:
	rm -f *.o
	rm -f ej1
