#ifndef _Busqueda_Local_h
#define _Busqueda_Local_h

#include <vector>
#include "Dibujo.h"
#include "GrafoBipartito.h"
#include <iostream>

using namespace std;

class BusquedaLocal {
public:
	BusquedaLocal(Dibujo& original);
	Dibujo hallarMinimoLocal(Dibujo& candidato);
private:
	unsigned int maximoP1;
	unsigned int minimoP2;
	unsigned int maximoP2;
	vector<bool>  estaEnP1;
	vector<bool>  estaEnP2;
	vector<unsigned> indiceP1;
	vector<unsigned> indiceP2;
	vector<nodo> p1;
	vector<nodo> p2;
	bool esFijo(nodo x);
	bool perteneceAP1(nodo x);
	bool perteneceAP2(nodo x);
	unsigned  obtenerIndice(nodo x, const vector<nodo>& pi);
	pair<unsigned,unsigned> rango(nodo x, vector<nodo>& pi);
	void mejorar(vector<nodo>& l1, vector<nodo>& l2, const  vector< vector<nodo> >& diccEjes);

};

#endif
