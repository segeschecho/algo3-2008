#include "Dibujo.h"

/*
 *  Clase Dibujo
 */

// Funciones Publicas

Dibujo :: Dibujo(GrafoBipartito* g, list<nodo>& l1, list<nodo>& l2) {
    grafo = g;

    cantFijosV1 = l1.size();
    cantFijosV2 = l2.size();

    for(unsigned int i = 0; i < cantFijosV1; i++) {

    }
}

Dibujo :: Dibujo(const Dibujo&) {
}

Dibujo :: ~Dibujo() {
}

bool Dibujo :: estaFijo(nodo) const {
}

bool Dibujo :: perteneceAV1(nodo) const {
}

const nodo* Dibujo :: fijosEnV(bool) const {
}

unsigned int Dibujo :: grado(nodo) const {
}

const nodo* Dibujo :: ejesYaPuestos(nodo) const {
}

const nodo* Dibujo :: ejesAPoner(nodo) const {
}

unsigned int Dibujo :: contarCruces() const {
}

Dibujo Dibujo :: operator= (const Dibujo&) {
}
// Funciones Privadas
