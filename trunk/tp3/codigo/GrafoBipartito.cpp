#include "GrafoBipartito.h"

/*
 *  Clase GrafoBipartito
 */

// Funciones Publicas

GrafoBipartito :: GrafoBipartito(unsigned int cardinalV1, unsigned int cardinalV2, const list<eje>& ejes) {
    cantNodosV1 = cardinalV1;
    cantNodosV2 = cardinalV2;

    diccEjes = new list<nodo> [cardinalV1 + cardinalV2];
    list<eje>::const_iterator it;
	it = ejes.begin();
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
    delete [] diccEjes;
}

unsigned int GrafoBipartito :: gradoDe(nodo v) const {
	return diccEjes[v].size();
}

void GrafoBipartito :: operator= (const GrafoBipartito& g) {
	cantNodosV1 = g.cantNodosV1;
	cantNodosV2 = g.cantNodosV2;

    diccEjes = new list<nodo> [cantNodosV1 + cantNodosV2];
    for(unsigned int i = 0; i < g.cantNodosV1 + g.cantNodosV2; i++) {
        list<nodo>::iterator it = g.diccEjes[i].begin();
	    while (it != g.diccEjes[i].end()) {
			diccEjes[i].push_back(*it);
			it++;
		}
    }
}

// Funciones Privadas
