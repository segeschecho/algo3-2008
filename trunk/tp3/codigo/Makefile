CC = g++
FLAGS=-g

all: cruces

# ejecutables
cruces: main.cpp GrafoBipartito.o Dibujo.o conteoDeCruces.o BusquedaLocal.o
	$(CC) $(FLAGS) -o cruces main.cpp GrafoBipartito.o Dibujo.o conteoDeCruces.o BusquedaLocal.o

# objetos
conteoDeCruces.o: conteoDeCruces.cpp
	$(CC) $(FLAGS) -c conteoDeCruces.cpp

Dibujo.o: Dibujo.cpp Dibujo.h GrafoBipartito.h
	$(CC) $(FLAGS) -c Dibujo.cpp

GrafoBipartito.o: GrafoBipartito.cpp GrafoBipartito.h
	$(CC) $(FLAGS) -c GrafoBipartito.cpp

BusquedaLocal.o: BusquedaLocal.cpp BusquedaLocal.h Dibujo.h GrafoBipartito.h 
	$(CC) $(FLAGS) -c BusquedaLocal.cpp 

clean:
	rm -f *.o
	rm -f cruces
