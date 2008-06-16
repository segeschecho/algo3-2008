#include "Dibujo.h"
#include <assert.h>
#include <iostream>

/*
 *  Clase Dibujo
 */

// Funciones Publicas

Dibujo :: Dibujo(GrafoBipartito* grafo, const vector<nodo>& l1, const vector<nodo>& l2) {
    g = grafo;
    assert(l1.size() + l2.size() <= g->n);

    nodosL1 = l1;
    nodosL2 = l2;
/*    nodosL1 = vector<nodo> (l1.size());
    list<nodo>::const_iterator it (l1.begin());

    for(unsigned int i = 0; i < l1.size(); i++) {
        nodosL1[i] = *it;
        it++;
    }

    nodosL2 = vector<nodo> (l2.size());
    it = l2.begin();

    for(unsigned int i = 0; i < l2.size(); i++) {
      nodosL2[i] = *it;
      it++;
    }
    */
}

Dibujo :: ~Dibujo() {
}

bool Dibujo :: perteneceAP1(nodo v) const {
    for(unsigned int i = 0; i < nodosL1.size(); i++) {
        if(nodosL1[i] == v) {
            return true;
        }
    }

    return false;
}

bool Dibujo :: perteneceAP2(nodo v) const {
  for(unsigned int i = 0; i < nodosL2.size(); i++) {
    if(nodosL2[i] == v) {
      return true;
    }
  }

  return false;
}

unsigned int Dibujo :: grado(nodo v) const {
    return g->grado(v);
}

const vector<nodo>& Dibujo :: nodosEnP1(void) const {
    return nodosL1;
}

const vector<nodo>& Dibujo :: nodosEnP2(void) const {
  return nodosL2;
}

const GrafoBipartito& Dibujo :: grafo(void) const {
    return *g;
}

void Dibujo :: cargar(const string& s) {
}

void Dibujo :: guardar(const string&) {
}
