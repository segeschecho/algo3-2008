#include "GrafoBipartito.h"

/*
 *  Clase GrafoBipartito
 */

// Funciones Publicas

GrafoBipartito :: GrafoBipartito(const list<nodo>& Part1, const list<nodo>& Part2, const list<eje>& ejes) {
    P1 = Part1;
    P2 = Part2;
    n = P1.size() + P2.size();
    m = ejes.size();

    diccEjes = vector< list<nodo> > (cardinalV1 + cardinalV2);
    list<eje>::const_iterator it(ejes.begin());
    while (it != ejes.end()) {
        diccEjes[it->primero].push_back(it->segundo);
        diccEjes[it->segundo].push_back(it->primero);
        it++;
    }
}

GrafoBipartito :: GrafoBipartito(const GrafoBipartito& g) {
    *this = g;
}

GrafoBipartito :: ~GrafoBipartito() {
}

unsigned int GrafoBipartito :: grado(nodo v) const {
	return diccEjes[v].size();
}

void GrafoBipartito :: operator= (const GrafoBipartito& g) {
	P1 = g.P1;
	P2 = g.P2;

    diccEjes = vector< list<nodo> > (cantNodosV1 + cantNodosV2);
    for(unsigned int i = 0; i < g.cantNodosV1 + g.cantNodosV2; i++) {
        list<nodo>::iterator it = g.diccEjes[i].begin();
	    while (it != g.diccEjes[i].end()) {
			diccEjes[i].push_back(*it);
			it++;
		}
    }
}
