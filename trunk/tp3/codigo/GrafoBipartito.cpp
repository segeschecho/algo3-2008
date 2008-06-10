#include "GrafoBipartito.h"

/*
 *  Clase GrafoBipartito
 */

// Funciones Publicas

GrafoBipartito :: GrafoBipartito(unsigned int cardinalV1, unsigned int cardinalV2, const list< eje >& ejes) {
    cantNodosV1 = cardinalV1;
    cantNodosV2 = cardinalV2;

    _ejes = new list<nodo> [cardinalV1 + cardinalV2];
    list< eje >::const_iterator it;

    while (it != ejes.end()) {
        _ejes[it->primero].push_back(it->segundo);
        _ejes[it->segundo].push_back(it->primero);
        it++;
    }
}

GrafoBipartito :: GrafoBipartito(const GrafoBipartito& g) {
}

GrafoBipartito :: ~GrafoBipartito() {
}

bool GrafoBipartito :: perteneceAV1(nodo) const {
}

unsigned int GrafoBipartito :: grado(nodo v) const {
}

GrafoBipartito GrafoBipartito :: operator = (const GrafoBipartito&) {
}

// Funciones Privadas
