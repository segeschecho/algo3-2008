#include "Camion.h"


Camion :: Camion(Cosa* cs, unsigned cap, unsigned cant){
    operaciones++;
    operaciones++;
    operaciones++;
    cosas = cs;
    capacidad = cap;
    cantCosas = cant;
    //operaciones = 10000000LL;
}

std::ostream& operator<< (std::ostream& o, const Camion& m) {
     o << "Camion con peso: "<<m.capacidad<<endl;
     o<<"Las cosas a llevar son: "<<endl;

     for(unsigned i = 0; i < m.cantCosas; i++){
         o<<m.cosas[i]<<endl;
     }
     return o;
}

