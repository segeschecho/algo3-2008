#ifndef _SolucionPosible_h
#define _SolucionPosible_h

#include "camion.h"
#include <list>
#include <iostream>

class SolucionPosible{
    public:

    unsigned cantCosas;
    //false: no lo llevo, true lo llevo
    bool* guardo;
    //guardo el valor acumulado de la sol, para no repetir calculos
    unsigned valor;
    //idem pero para el
    unsigned costo;
    SolucionPosible(unsigned cantCosas );
    void agregar(unsigned i,unsigned cost, unsigned val);
    void sacar(unsigned i,unsigned cost, unsigned val);
    friend std::ostream& operator<< (ostream&, const SolucionPosible&);
    ~SolucionPosible();
    SolucionPosible&  operator=(const SolucionPosible &otro);
};

#endif /*_SolucionPosible_h*/
