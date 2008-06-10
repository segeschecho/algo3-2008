#ifndef _DIBUJO_H_
#define _DIBUJO_H_

#include "GrafoBipartito.h"

class Dibujo {
  public:
    Dibujo(GrafoBipartito* g, nodo* l1, nodo* l2);
    Dibujo(const Dibujo& d);
    ~Dibujo();

    bool estaFijo(nodo) const;
    bool perteneceAV1(nodo v) const;
    unsigned int grado(nodo v) const;
    const nodo* fijosEnV(bool) const;
    const nodo* ejesYaPuestosNodo(nodo v) const;
    const nodo* ejesAPonerDeNodo(nodo v) const;
    unsigned int contarCruces() const;
    Dibujo operator = (const Dibujo& d);

  private:
    GrafoBipartito* g;
    unsigned int cantFijosV1, cantFijosV2;
    nodo* ordenFijosV1, ordenFijosV2;
    nodo** ejesYaPuestosDe, ejesAPonerDe;
};

#endif
