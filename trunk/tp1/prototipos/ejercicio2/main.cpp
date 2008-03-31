#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>
#include "SolucionPosible.h"
using namespace std;
void camionAux(SolucionPosible& candActual, Cosa* cosas, unsigned capacidad,unsigned indice, unsigned cant,SolucionPosible& mejorSol);

void camion(Camion& c,SolucionPosible& mejorSol){
    // s es variable auxiliar para ir guardando las soluciones q se van armando
    SolucionPosible * s = new SolucionPosible(c.cantCosas);
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
            candActual.agregar(indice,cosas[indice].costo,cosas[indice].valor);
            camionAux(candActual,cosas, capacidad, indice+1, cant, mejorSol);
            //sacamos el elemento agregado, para hacer backtracking
            candActual.sacar(indice,cosas[indice].costo, cosas[indice].valor);
        }

        indice  = indice + 1;

    }
    if(candActual.valor > mejorSol.valor){
        mejorSol = candActual;
    }

}


int main(int argc, char* argv[])
{
    string ruta;
    if(argc >= 2){
        ruta = argv[1];
    }
    else{
        ruta="Tp1Ej2.in";
    }
    fstream f (ruta.c_str());
    string salida;
    if(argc > 2)
        salida = argv[2];
    else
        salida = "Tp1Ej2.out";

    ofstream o (salida.c_str());
    assert(f.is_open());
    string caso;
    f >> caso;
    while(caso != "Fin"){
        unsigned cantElem, capacidad;
        f >> cantElem;
        f >> capacidad;
        Cosa* cs = new Cosa[cantElem];
        for(unsigned i = 0; i < cantElem; i++){
            unsigned costo,valor;
            f>>valor;
            f>>costo;
            cs[i] = Cosa(valor,costo);
        }
        Camion cam = Camion(cs,capacidad,cantElem);
        SolucionPosible* s = new SolucionPosible(cam.cantCosas);
        camion(cam,*s);
    o<<s->valor<<" ";
    unsigned contador=0;
    for(unsigned int i = 0; i < cam.cantCosas; i++){
        if(s->guardo[i]){
            contador++;
        }
    }
    o<<contador<<" ";
    for(unsigned int i = 0; i < cam.cantCosas; i++){
        if(s->guardo[i]){
            o<<i+1<<" ";
        }
    }
    o<<endl;
    delete cs;
    delete s;
    f>>caso;
    }

}
