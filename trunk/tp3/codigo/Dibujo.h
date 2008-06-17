#ifndef _DIBUJO_H_
#define _DIBUJO_H_

#include "GrafoBipartito.h"
#include <vector>

unsigned int contadorDeCruces (const vector<nodo>& p1, const vector<nodo>& p2, const vector< list<nodo> >& ejes, vector<nodo>* indicesP1 = NULL, vector<nodo>* indicesP2 = NULL);
unsigned int crucesEntre (nodo x, nodo y, const vector<nodo>& p2, const vector< list<nodo> >& ejes, vector<nodo>* indicesP2 = NULL);
unsigned int crucesPorAgregarEnLosBordes (bool agregoAdelante, const vector<nodo>& p1, const vector<nodo>& p2, const vector< list<nodo> > ejes, nodo* x = NULL, vector<nodo>* indicesP2 = NULL);

unsigned int crucesPorAgregarAdelante(const vector<nodo>& p1, const vector<nodo>& p2, const vector< list<nodo> > ejes, nodo* x, vector<nodo>* indicesP2);

unsigned int crucesPorAgregarAtras(const vector<nodo>& p1, const vector<nodo>& p2, const vector< list<nodo> > ejes, nodo* x, vector<nodo>* indicesP2);


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
