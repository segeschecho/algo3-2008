#ifndef _Busqueda_Local2_h
#define _Busqueda_Local2_h

#include <vector>
#include "Dibujo.h"
#include "GrafoBipartito.h"
#include <iostream>
#include "conteoDeCruces.h"

using namespace std;

class BusquedaLocal {
public:
	BusquedaLocal(Dibujo& original);
	Dibujo hallarMinimoLocal(Dibujo& candidato);
private:
    Dibujo* orig;
    unsigned minimoP2;
    unsigned maximoP2;
	bool esFijo(nodo x);
	bool perteneceAP1(nodo x);
	bool perteneceAP2(nodo x);
	pair<unsigned,unsigned> rango(nodo x, list<nodo>& pi,vector<nodo>& indice);
	void mejorar(list<nodo>& l1, list<nodo>& l2, const  vector< list<nodo> >& diccEjes,vector<nodo>& indice);

};

#endif

