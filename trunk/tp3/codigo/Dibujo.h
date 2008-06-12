#ifndef _DIBUJO_H_
#define _DIBUJO_H_

#include "GrafoBipartito.h"

class Dibujo {
  public:
    //aclaracion sobre el constructor: se produce aliasing con el parametro GrafoBipartito
    Dibujo(GrafoBipartito* g, nodo* l1, nodo* l2);
    Dibujo(const Dibujo& d);
    ~Dibujo();

    bool estaFijo(nodo) const;
    bool perteneceAV1(nodo v) const;
    unsigned int grado(nodo v) const;
    const nodo* fijosEnV(bool) const;
    const nodo* ejesYaPuestos(nodo v) const;
    const nodo* ejesAPoner(nodo v) const;
    unsigned int contarCruces() const;
    Dibujo operator= (const Dibujo& d);

  private:
    GrafoBipartito* grafo;
    unsigned int cantFijosV1, cantFijosV2;
    nodo* ordenNodosV1, ordenNodosV2;
    nodo** ejesYaPuestosNodo, ejesAPonerNodo;
};

#endif
