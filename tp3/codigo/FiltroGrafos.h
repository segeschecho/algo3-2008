#ifndef Filtro_Grafos_H
#define Filtro_Grafos_H

#include "Dibujo.h"
#include <vector>
#include <list>

using namespace std;

class FiltroGrafos{

public:
    FiltroGrafos(Dibujo& entrada);
	Dibujo reconstruirDibujo(Dibujo& limpio);
    Dibujo* dibujoLimpio;
    ~FiltroGrafos();

private:
    vector<nodo> marcados1,marcados2;
    vector<nodo> traduccion;
    list<nodo> nulos1, nulos2;
    GrafoBipartito *grafoOriginal;
    GrafoBipartito* grafoLimpio;
	vector<nodo> nuevoP1;
    vector<nodo> nuevoP2;
    list<nodo> nuevoV1;
    list<nodo> nuevoV2;
    list<eje>  losEjesNuevos;
    unsigned v1,v2,IV1,IV2;
    list<nodo> p1Posta;
    list<nodo> p2Posta;
};

#endif
