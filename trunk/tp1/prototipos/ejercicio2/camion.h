#ifndef _camion_h
#define _camion_h

#include "cosa.h"
#include <list>
#include <iostream>

class Camion{
    public:
        unsigned cantCosas;
        Cosa* cosas;
        unsigned capacidad;
        Camion(Cosa* cs, unsigned cap,unsigned cant);
        friend std::ostream& operator<< (ostream&, const Camion&);

};
#endif /*_camion_h*/
