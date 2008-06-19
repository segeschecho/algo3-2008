#ifndef _GRASP_H_
#define _GRASP_H_

#include "HeuristicaConstructiva.h"
#include "BusquedaLocal.h"

class Grasp {
public:
    Grasp (const Dibujo& original);
    const Dibujo& resolver(void);
    ~Grasp();
private:
    Dibujo resuelto;
};

#endif
