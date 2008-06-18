#ifndef _Dibujo_H
#define _Dibujo_H

#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "GrafoBipartito.h"

unsigned int contadorDeCruces (const vector<nodo>& p1, const vector<nodo>& p2, const vector< list<nodo> >& ejes, const vector<nodo>& indicesP1, const vector<nodo>& indicesP2);
unsigned int crucesEntre (nodo x, nodo y, const vector<nodo>& p2, const vector< list<nodo> >& ejes, const vector<nodo>& indicesP2);
unsigned int crucesPorAgregarEnLosBordes (bool agregoAdelante, const vector<nodo>& p1, const vector<nodo>& p2, const vector< list<nodo>& > ejes, nodo x, const vector<nodo>& indicesP2);

unsigned int crucesPorAgregarAdelante(const list<nodo>& p1, const list<nodo>& p2, const vector< list<nodo> >& ejes, const vector<nodo>& indicesP2);

unsigned int crucesPorAgregarAtras(const list<nodo>& p1, const list<nodo>& p2, const vector< list<nodo> >& ejes, const vector<nodo>& indicesP2);


class Dibujo {
  public:
    //aclaracion sobre el constructor: se produce aliasing con el GrafoBipartito
    //aclaracion sobre el destructor: no borra GrafoBipartito
    Dibujo(GrafoBipartito* g, const vector<nodo>& l1, const vector<nodo>& l2);
    Dibujo(GrafoBipartito* g, const list<nodo>& l1, const list<nodo>& l2);
    Dibujo(const string& nombreArchivo);
    Dibujo(const Dibujo& d);
    ~Dibujo();

    bool perteneceAP1(nodo) const;
    bool perteneceAP2(nodo) const;
    unsigned int grado(nodo) const;

    const vector<nodo>& nodosEnP1(void) const;
    const vector<nodo>& nodosEnP2(void) const;
    GrafoBipartito* grafo(void);

    void guardar(const string& nombreArchivo);

    void operator= (const Dibujo& d);

    unsigned contarCruces();

    //private:
    GrafoBipartito* g;
    vector<nodo> nodosL1, nodosL2;
};

#endif
