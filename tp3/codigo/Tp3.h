#ifndef Tp3_h
#define Tp3_h

#include <vector>
#include <list>

#include "Dibujo.h"
#include "HeuristicaConstructiva.h"
#include "BusquedaLocal.h"

using namespace std;

class Tp3{
public:
  Tp3(Dibujo& entrada,unsigned v1Inic,unsigned v2Inic, unsigned IV1In, unsigned IV2In);
	   Dibujo reconstruirDibujo(Dibujo& limpio);
       Dibujo* dibujoLimpio;
  ~Tp3(){delete dibujoLimpio; delete grafoLimpio;delete nuevoP1;delete nuevoP2;delete nuevoV1; delete nuevoV2;delete losEjesNuevos;};

private:
        vector<nodo> marcados1,marcados2;
        vector<nodo> traduccion;
        list<nodo> nulos1, nulos2;
        GrafoBipartito *grafoOriginal;
        GrafoBipartito* grafoLimpio;
	    vector<nodo>* nuevoP1;
        vector<nodo>* nuevoP2;
        list<nodo>* nuevoV1;
        list<nodo>* nuevoV2;
        list<eje> * losEjesNuevos;
        unsigned v1,v2,IV1,IV2;
};

#endif
