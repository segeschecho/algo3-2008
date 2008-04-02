#ifndef _SolucionPosible_h
#define _SolucionPosible_h

#include <list>
#include <iostream>

#include "Camion.h"

class SolucionPosible {
    public:
        unsigned cantCosas;
        //false: no lo llevo, true lo llevo
        bool* guardo;
        //guardo el valor acumulado de la sol, para no repetir calculos
        unsigned valor;
        //idem pero para el costo
        unsigned costo;

        SolucionPosible(unsigned cantCosas );
        ~SolucionPosible();
        SolucionPosible&  operator=(const SolucionPosible &otro);

        void agregar(unsigned i,unsigned cost, unsigned val);
        void sacar(unsigned i,unsigned cost, unsigned val);

        friend std::ostream& operator<< (ostream&, const SolucionPosible&);
};

#endif /*_SolucionPosible_h*/
