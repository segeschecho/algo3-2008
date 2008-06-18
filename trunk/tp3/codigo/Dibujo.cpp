#include "Dibujo.h"

/*
 *  Clase Dibujo
 */

// Funciones Publicas

Dibujo :: Dibujo(GrafoBipartito* grafo, const vector<nodo>& l1, const vector<nodo>& l2) {
    g = grafo;
    assert(l1.size() + l2.size() <= g->n);

    nodosL1 = l1;
    nodosL2 = l2;
}


Dibujo :: Dibujo(GrafoBipartito* grafo, const list<nodo>& l1, const list<nodo>& l2) {
    g = grafo;
    assert(l1.size() + l2.size() <= g->n);
    
    nodosL1.assign(l1.begin(), l1.end());
    nodosL2.assign(l2.begin(), l2.end());
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
		v--;
        nodosL1.push_back(v);
        nodosV1.push_back(v);
        cantLineas--;
    }

    entrada >> cantLineas;
    while(cantLineas > 0) {
        nodo v;
        entrada >> v;
        v--;
		nodosL2.push_back(v);
        nodosV2.push_back(v);
        cantLineas--;
    }

    entrada >> cantLineas;
    while(cantLineas > 0) {
        nodo v;
        eje e;

        entrada >> v;
        v--;
		e.primero = v;
        entrada >> v;
        v--;
		e.segundo = v;

        ejes.push_back(e);
        cantLineas--;
    }

    entrada >> cantLineas;
    while(cantLineas > 0) {
        nodo v;
        entrada >> v;
        v--;
		nodosV1.push_back(v);
        cantLineas--;
    }

    entrada >> cantLineas;
    while(cantLineas > 0) {
        nodo v;
        entrada >> v;
        v--;
		nodosV2.push_back(v);
        cantLineas--;
    }

    entrada >> cantLineas;
    while(cantLineas > 0) {
        nodo v;
        eje e;

        entrada >> v;
        v--;
		e.primero = v;
        entrada >> v;
        v--;
		e.segundo = v;

        ejes.push_back(e);
        cantLineas--;
    }
     
#define print(a) cout<<a<<endl;
    unsigned i = 0;
    while(i < nodosV1.size()){
      print(nodosV1[i]);
      i++;
    }
    g = new GrafoBipartito(nodosV1, nodosV2, ejes);
    cout<<"aaaaaaaaaaaaaaaaaaa"<<endl;
}

Dibujo :: Dibujo(const Dibujo& d) {
    *this = d;
}

Dibujo :: ~Dibujo() {
}

bool Dibujo :: perteneceAP1(nodo v) const {
    return v < nodosL1.size();
}

bool Dibujo :: perteneceAP2(nodo v) const {
    return v >= nodosL1.size() && v < nodosL1.size() + nodosL2.size();
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

GrafoBipartito* Dibujo :: grafo(void) {
    return g;
}

unsigned Dibujo :: contarCruces() {
    return 7;
}


void Dibujo :: guardar(const string& nombreArchivo) {
    ofstream salida (nombreArchivo.c_str());
    assert(salida.is_open());
    assert(nodosL1.size() == g->V1.size() && nodosL2.size() == g->V2.size());

//    salida << contadorDeCruces(nodosL1, nodosL2, g->diccEjes) << endl;
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

void Dibujo :: operator= (const Dibujo& d) {
    nodosL1 = d.nodosL1;
    nodosL2 = d.nodosL2;
    g = d.g;
}
