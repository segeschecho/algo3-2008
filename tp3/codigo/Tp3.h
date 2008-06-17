#ifndef Tp3_h
#define Tp3_h

#include "Dibujo.h"
#include <vector>
#include <list>

using namespace std;

class Tp3{
public:
  Tp3(Dibujo& entrada,unsigned v1Inic,unsigned v2Inic, unsigned IV1In, unsigned IV2In);
	   Dibujo reconstruirDibujo(Dibujo& limpio);
       Dibujo* dibujoLimpio;
  ~Tp3(){delete dibujoLimpio; delete grafoLimpio;};
	   
private:
        vector<nodo> marcados1,marcados2;
        vector<nodo> traduccion;
        list<nodo> nulos1, nulos2;
        GrafoBipartito *grafoOriginal;
        GrafoBipartito* grafoLimpio;
	
        unsigned v1,v2,IV1,IV2;
};

#endif
