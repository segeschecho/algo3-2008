#ifndef _Dibujo_H
#define _Dibujo_H

#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "conteoDeCruces.h"
#include "GrafoBipartito.h"


class Dibujo {
    friend std::ostream& operator<< (ostream&, Dibujo&);
  public:
    //aclaracion sobre el constructor: se produce aliasing con el GrafoBipartito
    Dibujo(GrafoBipartito* g, const vector<nodo>& l1, const vector<nodo>& l2);
    Dibujo(GrafoBipartito* g, const list<nodo>& l1, const list<nodo>& l2);
    Dibujo(GrafoBipartito* g, const list<nodo>& l1, const list<nodo>& l2, unsigned cruces);
    Dibujo(ifstream& entrada);
    Dibujo(const Dibujo& d);
    Dibujo();
    ~Dibujo();

    bool perteneceAP1(nodo) const;
    bool perteneceAP2(nodo) const;
    unsigned int grado(nodo) const;

    const vector<nodo>& nodosEnP1(void) const;
    const vector<nodo>& nodosEnP2(void) const;
    GrafoBipartito* grafo(void);

    void guardar(ofstream& salida);

    void operator= (const Dibujo& d);

    unsigned contarCruces();

    //private:
    GrafoBipartito* g;
    vector<nodo> nodosL1, nodosL2;
    bool desdeArchivo;
    unsigned cruces;
    bool contado;
};

#endif
