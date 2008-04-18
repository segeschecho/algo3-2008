#include "SolucionPosible.h"

SolucionPosible ::SolucionPosible(unsigned cantcosas ){
    cantCosas = cantcosas;
    guardo = new bool[cantCosas];
    for(unsigned i = 0; i < cantCosas; i++){
        guardo[i] = false;
    }
    valor = 0;
    peso = 0;
}

void SolucionPosible :: agregar(unsigned i,unsigned cost, unsigned val){
    guardo[i] = true;
    valor = valor + val;
    peso = peso + cost;
}

void SolucionPosible :: sacar(unsigned i,unsigned cost, unsigned val){
    guardo[i] = false;
    valor = valor - val;
    peso = peso - cost;
}

SolucionPosible&  SolucionPosible ::  operator=(const SolucionPosible &otro){
    for(unsigned i = 0; i < otro.cantCosas; i++){
        guardo[i] = otro.guardo[i];
    }
    valor = otro.valor;
    peso = otro.peso;
    return *this;
}

SolucionPosible :: ~SolucionPosible(){
    delete []guardo;
}
