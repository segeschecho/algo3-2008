#include "Dibujo.h"
#include <assert.h>

/*
 *  Clase Dibujo
 */

// Funciones Publicas

Dibujo :: Dibujo(GrafoBipartito* g, list<nodo>& l1, list<nodo>& l2) {
    grafo = g;
    cantNodosL1 = l1.size();
    cantNodosL2 = l2.size();

    assert(cantNodosL1 + cantNodosL2 < g->n);

    nodosV1 = vector<nodo> (cantNodosL1);
    list<nodo>::const_iterator it (l1.begin());

    for(unsigned int i = 0; i < cantNodosL1; i++) {
        nodosV1[i] = *it;
        it++;
    }

    nodosV2 = vector<nodo> (cantNodosL1);
    list<nodo>::const_iterator it (l2.begin());

    for(unsigned int i = 0; i < cantNodosL2; i++) {
      nodosV2[i] = *it;
      it++;
    }
}

Dibujo :: ~Dibujo() {
}

bool Dibujo :: perteneceAP1(nodo v) const {
    for(unsigned int = 0; i < cantNodosL1; i++) {
        if(nodosL1[i] == v) {
            return true;
        }
    }

    return false;
}

bool Dibujo :: perteneceAP2(nodo v) const {
  for(unsigned int = 0; i < cantNodosL2; i++) {
    if(nodosL2[i] == v) {
      return true;
    }
  }

  return false;
}

unsigned int Dibujo :: grado(nodo v) const {
    return g.grado(v);
}

const vector<nodo>& Dibujo :: nodosEnP1(void) const {
    return nodosL1;
}

const vector<nodo>& Dibujo :: nodosEnP2(void) const {
  return nodosL2;
}
