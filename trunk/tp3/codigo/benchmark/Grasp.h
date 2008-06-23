#ifndef _GRASP_H_
#define _GRASP_H_

#include "HeuristicaConstructiva.h"
#include "BusquedaLocal.h"

class Grasp {
public:
    Grasp (Dibujo& original);
    Dibujo resolver(float alfa);
    Dibujo resolver1(float alfa);
	Dibujo resolver2(float alfa);
	Dibujo resolver3(float alfa);
	Dibujo resolver4(float alfa);
	Dibujo resolver5(float alfa);
	Dibujo resolver6(float alfa);
	Dibujo resolver7(float alfa);
    Dibujo resolver8(float alfa);
	~Grasp();
private:
    Dibujo* d;
};

#endif
