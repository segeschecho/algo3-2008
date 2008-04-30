#include <cassert>
#include "Grafo.h"

Grafo :: Grafo(unsigned nodos, list<pair<unsigned,unsigned> >& relaciones) {
    n = nodos;
    m = 0;

    // pido memoria para la matriz de relaciones
    ejes = new bool*[n];
    for(unsigned i = 0; i < n; i++) {
        ejes[i] = new bool[n];
    }

    // lleno la matriz de falses
    for(unsigned i = 0; i < n; i++) {
        for(unsigned j = 0; j < n; j++) {
            ejes[i][j] = false;
        }
    }

    // almaceno las relaciones (chequeo y si no estaba repetida incremento m)
    int a;
    int b;
    for(list<pair<unsigned,unsigned> >::iterator it = relaciones.begin();
        it != relaciones.end();
        it++) {
        a = it->first;
        b = it->second;
        if (ejes[a][b] != true) {
            m++;
            ejes[a][b] = true;
            ejes[b][a] = true;
        }
    }
}

Grafo :: ~Grafo() {
    for(unsigned i = 0; i < n; i++) {
        delete[] ejes[i];
    }
    delete[] ejes;
}

bool Grafo :: estanConectados(unsigned a, unsigned b) {
    assert(a < n);
    assert(b < n);

    return ejes[a][b];
}
