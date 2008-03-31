#include <iostream>
#include "SolucionPosible.h"
using namespace std;
void camionAux(SolucionPosible& candActual, Cosa* cosas, unsigned capacidad,unsigned indice, unsigned cant,SolucionPosible& mejorSol);

void camion(Camion& c,SolucionPosible& mejorSol){
    // s es variable auxiliar para ir guardando las soluciones q se van armando
    SolucionPosible * s = new SolucionPosible(c.cosas, c.cantCosas);
    //mejor sol va a guardar la solucion optima
    camionAux(*s,c.cosas,c.capacidad,0,c.cantCosas,mejorSol);
    delete s;
}

/*
capacidad: capacidad del camion
cosas: arreglo con las cosas q hay para llevar
indice: posicion del arreglo q estoy tratando de meter
cant es el tamaño del arreglo cosas
candActual es la solucion q voy construyendo
mejorSol guarda la mejor encontrada hasta ahora
*/
void camionAux(SolucionPosible& candActual, Cosa* cosas, unsigned capacidad,unsigned indice, unsigned cant,SolucionPosible& mejorSol){
    //cuando ya llegue hasta el ultimo elemento paro, pero me fijo si consegui una mejor sol
    if(indice == cant && candActual.valor > mejorSol.valor){
        mejorSol = candActual;
        return;
    }
    if(indice == cant)
        return;

    while(indice < cant){
        if(candActual.costo + cosas[indice].costo <= capacidad){
            candActual.agregar(indice);
            camionAux(candActual,cosas, capacidad, indice+1, cant, mejorSol);
            //sacamos el elemento agregado, para hacer backtracking
            candActual.sacar(indice);
        }

        indice  = indice + 1;

    }
    if(candActual.valor > mejorSol.valor){
        mejorSol = candActual;
    }

}


int main()
{
    Cosa* c= new Cosa[3];
    c[0] = Cosa(199,2);
    c[1] = Cosa(2999,3);
    c[2] = Cosa(39,4);
    Camion cam = Camion(c,400,3);
    SolucionPosible* s = new SolucionPosible(cam.cosas, cam.cantCosas);
    camion(cam,*s);
    cout<<*s<<endl;
    delete c;
    delete s;
    return 0;
}
