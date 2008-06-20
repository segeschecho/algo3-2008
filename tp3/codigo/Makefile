CC = g++
FLAGS=-g -Wall

all: cruces

# ejecutables
cruces: main.cpp GrafoBipartito.o Dibujo.o conteoDeCruces.o FiltroGrafos.o HeuristicaConstructiva.o BusquedaLocal.o SolucionExacta.o Grasp.o
	$(CC) $(FLAGS) -o cruces main.cpp GrafoBipartito.o Dibujo.o conteoDeCruces.o FiltroGrafos.o HeuristicaConstructiva.o BusquedaLocal.o SolucionExacta.o Grasp.o

testSolucionExacta: testSolucionExacta.cpp GrafoBipartito.o Dibujo.o conteoDeCruces.o FiltroGrafos.o HeuristicaConstructiva.o BusquedaLocal.o SolucionExacta.o Grasp.o
	$(CC) $(FLAGS) -o testSolucionExacta testSolucionExacta.cpp GrafoBipartito.o Dibujo.o conteoDeCruces.o FiltroGrafos.o HeuristicaConstructiva.o BusquedaLocal.o SolucionExacta.o Grasp.o

# objetos
conteoDeCruces.o: conteoDeCruces.cpp conteoDeCruces.h
	$(CC) $(FLAGS) -c conteoDeCruces.cpp

HeuristicaConstructiva.o: HeuristicaConstructiva.cpp HeuristicaConstructiva.h
	$(CC) $(FLAGS) -c HeuristicaConstructiva.cpp

Dibujo.o: Dibujo.cpp Dibujo.h GrafoBipartito.h
	$(CC) $(FLAGS) -c Dibujo.cpp

GrafoBipartito.o: GrafoBipartito.cpp GrafoBipartito.h
	$(CC) $(FLAGS) -c GrafoBipartito.cpp

SolucionExacta.o: SolucionExacta.cpp SolucionExacta.h HeuristicaConstructiva.h
	$(CC) $(FLAGS) -c SolucionExacta.cpp

BusquedaLocal.o: BusquedaLocal.cpp BusquedaLocal.h
	$(CC) $(FLAGS) -c BusquedaLocal.cpp 

Grasp.o: Grasp.cpp Grasp.h
	$(CC) $(FLAGS) -c Grasp.cpp

FiltroGrafos.o: FiltroGrafos.cpp FiltroGrafos.h Dibujo.h GrafoBipartito.h 
	$(CC) $(FLAGS) -c FiltroGrafos.cpp 

clean:
	rm -f *.o
	rm -f cruces
	rm -f testSolucionExacta
