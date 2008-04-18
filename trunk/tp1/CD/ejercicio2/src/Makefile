CC = g++
FLAGS=-g

all: camion

# ejecutables
camion: Camion.cpp Camion.o Cosa.o SolucionPosible.o 
	$(CC) $(FLAGS) main.cpp Camion.o Cosa.o SolucionPosible.o -o camion

# objetos
Camion.o: Camion.cpp Camion.h Cosa.h 
	$(CC) $(FLAGS) -c Camion.cpp

Cosa.o: Cosa.cpp Cosa.h 
	$(CC) $(FLAGS) -c Cosa.cpp

SolucionPosible.o: SolucionPosible.cpp SolucionPosible.h Camion.h 
	$(CC) $(FLAGS) -c SolucionPosible.cpp
 
clean:
	rm -f *.o
	rm -f camion
