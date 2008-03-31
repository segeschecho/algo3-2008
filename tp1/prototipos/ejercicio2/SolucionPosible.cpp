#include "SolucionPosible.h"

SolucionPosible ::SolucionPosible(Cosa* cs,unsigned cantcosas ){
    cantCosas = cantcosas;
    cosas = new Cosa[cantCosas];
    guardo = new bool[cantCosas];
    for(unsigned i = 0; i < cantCosas; i++){
        guardo[i] = false;
        cosas[i] = cs[i];
    }
    valor = 0;
    costo = 0;
}

void SolucionPosible :: agregar(unsigned i){
    guardo[i] = true;
    valor = valor + cosas[i].valor;
    costo = costo + cosas[i].costo;
}

void SolucionPosible :: sacar(unsigned i){
    guardo[i] = false;
    valor = valor - cosas[i].valor;
    costo = costo - cosas[i].costo;
}

std::ostream& operator<< (std::ostream& o, const SolucionPosible& s) {
    for(unsigned i = 0; i < s.cantCosas; i++){
        if (s.guardo[i] == true){
         o<<s.cosas[i]<<endl;
        }
     }
     o<<"costo total:"<<s.costo<<endl;
     o<<"valor total:"<<s.valor<<endl;
     return o;

}

SolucionPosible&  SolucionPosible ::  operator=(const SolucionPosible &otro){
    for(unsigned i = 0; i < otro.cantCosas; i++){
        guardo[i] = otro.guardo[i];
    }
    valor = otro.valor;
    costo = otro.costo;
    return *this;
}

SolucionPosible :: ~SolucionPosible(){
    delete cosas;
    delete guardo;
}
