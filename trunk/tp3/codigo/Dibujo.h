#ifndef _DIBUJO_H_
#define _DIBUJO_H_

#include "GrafoBipartito.h"
#include <vector>
class Dibujo {
  public:
    //aclaracion sobre el constructor: se produce aliasing con el GrafoBipartito
    Dibujo(GrafoBipartito* g, list<nodo> l1, list<nodo> l2);
    ~Dibujo();

    bool perteneceAP1(nodo) const;
    bool perteneceAP2(nodo) const;
    unsigned int grado(nodo) const;
    const vector<nodo> nodosEnP1(void) const;
    const vector<nodo> nodosEnP2(void) const;

  private:
    GrafoBipartito* grafo;
    vector<nodo> nodosL1, nodosL2;
};

#endif