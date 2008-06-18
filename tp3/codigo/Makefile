CC = g++
FLAGS=-g

all: cruces

# ejecutables
cruces: main.cpp GrafoBipartito.o Dibujo.o conteoDeCruces.o Tp3.o HeuristicaConstructiva.o
	$(CC) $(FLAGS) -o cruces main.cpp GrafoBipartito.o Dibujo.o conteoDeCruces.o Tp3.o HeuristicaConstructiva.o


# objetos
conteoDeCruces.o: conteoDeCruces.cpp conteoDeCruces.h
	$(CC) $(FLAGS) -c conteoDeCruces.cpp

HeuristicaConstructiva.o: HeuristicaConstructiva.cpp HeuristicaConstructiva.h
	$(CC) $(FLAGS) -c HeuristicaConstructiva.cpp

Dibujo.o: Dibujo.cpp Dibujo.h GrafoBipartito.h
	$(CC) $(FLAGS) -c Dibujo.cpp

GrafoBipartito.o: GrafoBipartito.cpp GrafoBipartito.h
	$(CC) $(FLAGS) -c GrafoBipartito.cpp

#BusquedaLocal.o: BusquedaLocal.cpp BusquedaLocal.h
#	$(CC) $(FLAGS) -c BusquedaLocal.cpp 

Tp3.o: Tp3.cpp Tp3.h Dibujo.h GrafoBipartito.h 
	$(CC) $(FLAGS) -c Tp3.cpp 

clean:
	rm -f *.o
	rm -f cruces
