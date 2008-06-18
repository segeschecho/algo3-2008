#ifndef Tp3_h
#define Tp3_h

#include "Dibujo.h"
#include <vector>
#include <list>

using namespace std;

class Tp3{
public:
  Tp3(Dibujo& entrada);
	   Dibujo reconstruirDibujo(Dibujo& limpio);
       Dibujo* dibujoLimpio;
  ~Tp3(){delete dibujoLimpio; delete grafoLimpio;delete nuevoP1;delete nuevoP2;delete nuevoV1; delete nuevoV2;delete losEjesNuevos;delete p1Posta; delete p2Posta;};

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
        list<nodo>* p1Posta;
        list<nodo>* p2Posta;
};

#endif
