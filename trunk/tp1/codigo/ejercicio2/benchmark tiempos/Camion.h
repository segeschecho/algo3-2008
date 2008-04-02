#ifndef _camion_h
#define _camion_h

#include <list>
#include <iostream>

#include "Cosa.h"

class Camion {
    public:
        unsigned cantCosas;
        unsigned capacidad;

        Cosa* cosas;
        Camion(Cosa* cs, unsigned cap,unsigned cant);

        friend std::ostream& operator<< (ostream&, const Camion&);
};
#endif /*_camion_h*/
