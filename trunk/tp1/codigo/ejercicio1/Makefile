CC = g++
FLAGS = -g

all: primos

# ejecutables
primos: main.cpp FabricaCandidatos.o
	$(CC) $(FLAGS) main.cpp FabricaCandidatos.o -o primos

# objetos
FabricaCandidatos.o: FabricaCandidatos.cpp FabricaCandidatos.h
	$(CC) $(FLAGS) -c FabricaCandidatos.cpp

clean:
	rm -f *.o
	rm -f primos
