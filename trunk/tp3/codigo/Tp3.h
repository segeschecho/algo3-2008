#ifndef Tp3_h
#define Tp3_h

#include "Dibujo.h"
#include <vector>
#include <list>

using namespace std;

class TP3{
public:
       Dibujo limpiarDibujo(Dibujo entrada);
	   Dibujo reconstruirDibujo(Dibujo limpio);
	   
private:
        vector<nodo> marcados1,marcados2;
        vector<nodo> traduccion;
        vector<nodo> nulos1, nulos2;
		Dibujo dibujoLimpio;
};

#endif