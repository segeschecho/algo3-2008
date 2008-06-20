#include "GrafoBipartito.h"

GrafoBipartito :: GrafoBipartito(const vector<nodo>& p1, const vector<nodo>& p2, const list<eje>& ejes) {
    assert(p1.size() > 0 && p2.size() > 0);
    n = p1.size() + p2.size();
    m = ejes.size();
    listEjes = ejes;

    V1 = p1;
    V2 = p2;
    
    diccEjes = vector< list<nodo> > (p1.size() + p2.size());
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
    listEjes = g.listEjes;
}

const list<eje>& GrafoBipartito :: listaEjes(void) {
    return listEjes;
}

const vector<nodo>& GrafoBipartito :: nodosEnP1(void) {
    return V1;
}

const vector<nodo>& GrafoBipartito :: nodosEnP2(void) {
    return V2;
}

const vector< list<nodo> >& GrafoBipartito :: ejes(void) {
    return diccEjes;
}
