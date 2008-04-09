#include "SolucionPosible.h"

SolucionPosible ::SolucionPosible(unsigned cantcosas ){
    operaciones++;
    cantCosas = cantcosas;
    operaciones++;
    operaciones = operaciones + cantCosas;
    operaciones+=cantCosas;
    guardo = new bool[cantCosas];
    operaciones++;
    operaciones++;
    operaciones++;
    for(unsigned i = 0; i < cantCosas; i++){
        operaciones++;
        guardo[i] = false;
        operaciones++;
        operaciones++;
    }
    operaciones++;
    operaciones++;
    valor = 0;
    peso = 0;
}

void SolucionPosible :: agregar(unsigned i,unsigned cost, unsigned val){
    operaciones++;
    guardo[i] = true;
    operaciones = operaciones + 2;
    valor = valor + val;
    operaciones = operaciones + 2;
    peso = peso + cost;
}

void SolucionPosible :: sacar(unsigned i,unsigned cost, unsigned val){
    operaciones++;
    guardo[i] = false;
    operaciones++;
    operaciones++;
    valor = valor - val;
    operaciones++;
    operaciones++;
    peso = peso - cost;
}

/*std::ostream& operator<< (std::ostream& o, const SolucionPosible& s) {
    for(unsigned i = 0; i < s.cantCosas; i++){
        if (s.guardo[i] == true){
         o<<s.cosas[i]<<endl;
        }
     }
     o<<"costo total:"<<s.peso<<endl;
     o<<"valor total:"<<s.valor<<endl;
     return o;

}*/

SolucionPosible&  SolucionPosible ::  operator=(const SolucionPosible &otro){
    operaciones++;
    operaciones++;
    operaciones++;
    for(unsigned i = 0; i < otro.cantCosas; i++){
        operaciones++;
        guardo[i] = otro.guardo[i];
        operaciones++;
        operaciones++;
    }
    operaciones++;
    valor = otro.valor;
    operaciones++;
    peso = otro.peso;
    operaciones++;
    return *this;
}

SolucionPosible :: ~SolucionPosible(){
    operaciones+=cantCosas;
    delete []guardo;
}
