#ifndef _conteo_De_Cruces_H
#define _conteo_De_Cruces_H

#include <math.h>

//#include "Dibujo.h"
#include "GrafoBipartito.h"
nodo maxElem(const vector<nodo>& p);
void radixSort(list<eje>& listaEjes, unsigned int size1, unsigned int size2);
unsigned int acumTree (const list<eje>& l, unsigned int cantHojas);
unsigned int contadorDeCruces (const vector<nodo>& p1, const vector<nodo>& p2, const vector< list<nodo> >& ejes, const vector<nodo>& indicesP1, const vector<nodo>& indicesP2);
unsigned int crucesEntre(nodo x, nodo y, const vector<nodo>& p2, const vector< list<nodo> >& ejes, const vector<nodo>& indicesP2);
unsigned int crucesEntre(nodo x, nodo y, const list<nodo>& p2, const vector< list<nodo> >& ejes, const vector<nodo>& indicesP2);
unsigned int crucesPorAgregarEnLosBordes(bool agregoAdelante, const vector<nodo>& p1, const vector<nodo>& p2, const vector< list<nodo> >& ejes, const vector<nodo>& indicesP2);
unsigned int crucesPorAgregarAdelante(const list<nodo>& p1, const list<nodo>& p2, const vector< list<nodo> >& ejes, const vector<nodo>& indicesP2);
unsigned int crucesPorAgregarAtras(const list<nodo>& p1, const list<nodo>& p2, const vector< list<nodo> >& ejes, const vector<nodo>& indicesP2);

#endif
