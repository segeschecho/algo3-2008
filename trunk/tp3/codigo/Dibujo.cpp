#include "Dibujo.h"
#include <assert.h>
#include <iostream>
#include <fstream>

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

Dibujo :: Dibujo(const string& nombreArchivo) {
    ifstream entrada (nombreArchivo.c_str());
    assert(entrada.is_open());

    vector<nodo> nodosV1, nodosV2;
    list<eje> ejes;
    unsigned int cantLineas;

    entrada >> cantLineas;
    while(cantLineas > 0) {
        nodo v;
        entrada >> v;
        nodosL1.push_back(v);
        nodosV1.push_back(v);
        cantLineas--;
    }

    entrada >> cantLineas;
    while(cantLineas > 0) {
        nodo v;
        entrada >> v;
        nodosL2.push_back(v);
        nodosV1.push_back(v);
        cantLineas--;
    }

    entrada >> cantLineas;
    while(cantLineas > 0) {
        nodo v;
        eje e;

        entrada >> v;
        e.primero = v;
        entrada >> v;
        e.segundo = v;

        ejes.push_back(e);
        cantLineas--;
    }

    entrada >> cantLineas;
    while(cantLineas > 0) {
        nodo v;
        entrada >> v;
        nodosV1.push_back(v);
        cantLineas--;
    }

    entrada >> cantLineas;
    while(cantLineas > 0) {
        nodo v;
        entrada >> v;
        nodosV1.push_back(v);
        cantLineas--;
    }

    entrada >> cantLineas;
    while(cantLineas > 0) {
        nodo v;
        eje e;

        entrada >> v;
        e.primero = v;
        entrada >> v;
        e.segundo = v;

        ejes.push_back(e);
        cantLineas--;
    }

    g = new GrafoBipartito(nodosV1, nodosV2, ejes);
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

void Dibujo :: guardar(const string& nombreArchivo) {
    ofstream salida (nombreArchivo.c_str());
    assert(salida.is_open());
    assert(nodosL1.size() == g->V1.size() && nodosL2.size() == g->V2.size());

    salida << contadorDeCruces(nodosL1, nodosL2, g->diccEjes) << endl;
    salida << nodosL1.size() << endl;
    vector<nodo>::const_iterator it (nodosL1.begin());

    while(it != nodosL1.end()) {
        salida << *it << endl;
        it++;
    }

    salida << nodosL2.size() << endl;
    it = nodosL2.begin();

    while(it != nodosL2.end()) {
        salida << *it << endl;
        it++;
    }
}