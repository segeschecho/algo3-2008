PARAMS=-Wall

all: barcos

# objetos
Grafo.o: Grafo.cpp Grafo.h
	g++ -c $(PARAMS) Grafo.cpp

BuscadorCaminoTCI.o: BuscadorCaminoTCI.cpp BuscadorCaminoTCI.h Grafo.h
	g++ -c $(PARAMS) BuscadorCaminoTCI.cpp

# binarios
barcos: Grafo.o BuscadorCaminoTCI.o main.cpp
	g++ $(PARAMS) Grafo.o BuscadorCaminoTCI.o main.cpp -o barcos

clean:
	rm -f *.o
	rm -f barcos
