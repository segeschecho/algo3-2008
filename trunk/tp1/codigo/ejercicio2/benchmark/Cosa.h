#ifndef _Cosa_H
#define _Cosa_H

#include <iostream>
#include "operaciones.h"

using namespace std;

class Cosa {
    public:
        Cosa(){};
        Cosa(unsigned c, unsigned v);

        unsigned costo;
        unsigned valor;

        friend std::ostream& operator<< (ostream&, const Cosa&);
};

#endif /*_Cosa_h*/
