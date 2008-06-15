#include "GrafoBipartito.h"
#include <assert.h>
/*
 *  Clase GrafoBipartito
 */

// Funciones Publicas

#define MAX(a,b) (a < b) ? b : a

GrafoBipartito :: GrafoBipartito(const list<nodo>& p1, const list<nodo>& p2, const list<eje>& ejes) {
    assert(p1.size() > 0 && p2.size() > 0);
    n = p1.size() + p2.size();
    m = ejes.size();

    // copio los nodos de V1
    list<nodo>::const_iterator itNodos(p1.begin());
    V1 = vector<nodo> (p1.size());
    vector<nodo>::iterator itVi(V1.begin());
    while (itNodos != p1.end()) {
        *itVi = *itNodos;
        itVi++;
        itNodos++;
    }

    // copio los nodos de V2
    itNodos = p2.begin();
    V2 = vector<nodo> (p2.size());
    itVi = V2.begin();
    while (itNodos != p2.end()) {
        *itVi = *itNodos;
        itVi++;
        itNodos++;
    }

    diccEjes = vector< vector<nodo> > (MAX(maxElem(V1), maxElem(V2)) + 1);
    list<eje>::const_iterator itEjes(ejes.begin());
    while (itEjes != ejes.end()) {
        diccEjes[itEjes->primero].push_back(itEjes->segundo);
        diccEjes[itEjes->segundo].push_back(itEjes->primero);
        itEjes++;
    }
}

GrafoBipartito :: GrafoBipartito(const GrafoBipartito& g) {
    *this = g;
}

GrafoBipartito :: ~GrafoBipartito() {
}

unsigned int GrafoBipartito :: cantNodos(void) const {
    return n;
}

unsigned int GrafoBipartito :: cantEjes(void) const {
    return m;
}

unsigned int GrafoBipartito :: grado(nodo v) const {
	return diccEjes[v].size();
}

void GrafoBipartito :: operator= (const GrafoBipartito& g) {
	V1 = g.V1;
	V2 = g.V2;
    diccEjes = g.diccEjes;
}

nodo maxElem(const vector<nodo>& p) {
    nodo maximo = p[0];
    for(unsigned int i = 1; i < p.size(); i++) {
        if (maximo < p[i]) {
            maximo = p[i];
        }
    }
    return maximo;
}
