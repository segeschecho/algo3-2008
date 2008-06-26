#ifndef _GRASP_H_
#define _GRASP_H_

#include "HeuristicaConstructiva.h"
#include "BusquedaLocal.h"

class Grasp {
public:
    Grasp (Dibujo& original);
    Dibujo resolver();

private:
    Dibujo* d;
};

#endif
