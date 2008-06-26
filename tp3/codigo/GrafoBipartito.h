#ifndef _Grafo_Bipartito_H
#define _Grafo_Bipartito_H

#include <list>
#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;

#define nodo unsigned int

struct eje {
    nodo primero;
    nodo segundo;
};

nodo maxElem(const vector<nodo>& p);

class GrafoBipartito {
    
    friend class Dibujo;

public:
    GrafoBipartito(const vector<nodo>& Part1, const vector<nodo>& Part2, const list<eje> & ejes);
    GrafoBipartito(const GrafoBipartito& g);
    ~GrafoBipartito();

    unsigned int cantNodos(void) const;
    unsigned int cantEjes(void) const;
    unsigned int grado(nodo v) const;
    void operator = (const GrafoBipartito& g);
    const vector< list<nodo> >& ejes(void);
    const list<eje>& listaEjes(void);
    const vector<nodo>& nodosEnP1(void);
    const vector<nodo>& nodosEnP2(void);

private:
    vector<nodo> V1, V2;
    unsigned int m, n;
    vector< list<nodo> > diccEjes;
    list<eje> listEjes;
};

#endif
