#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>
#include "CmergeSort.h"
#include "SolucionPosible.h"

using namespace std;

void camionAux(SolucionPosible& candActual,Camion&c,unsigned indice,SolucionPosible& mejorSol,unsigned valorOptimo);

unsigned sumar(Cosa* c, unsigned int cant){
    unsigned valor = 0;
    for(int i = 0; i < cant; i++){
        valor += c[i].valor;
    }
    return valor;
}


void camion(Camion& c,SolucionPosible& mejorSol,int* indices) {
    operaciones = 0;
    SolucionPosible * s = new SolucionPosible(c.cantCosas);
    CMergeSort sort=CMergeSort(c.cosas,c.cantCosas,indices);
    operaciones += sort.sort();
    unsigned valorOptimo = sumar(c.cosas, c.cantCosas);
    camionAux(*s,c,0,mejorSol,valorOptimo);
    delete s;
}


// Variables utilizadas:
// capacidad: capacidad del camion
// cosas: arreglo con las cosas que hay para llevar
// indice: posicion del arreglo que estoy tratando de meter
// cant: tama�o del arreglo cosas
// candActual: la solucion que voy construyendo
// mejorSol: la mejor solucion encontrada hasta ahora

void camionAux(SolucionPosible& candActual, Camion& c,unsigned indice,SolucionPosible& mejorSol,unsigned valorOptimo){
    // cuando ya llegue hasta el ultimo elemento paro, pero me fijo si consegui una mejor solucion
    operaciones = operaciones + 3;

    if(indice == c.cantCosas && candActual.valor > mejorSol.valor) {
        operaciones ++;
        mejorSol = candActual;
    }
    if(candActual.valor + valorOptimo < mejorSol.valor){
        return;
    }
    else {
        // caso base: indice == c.cantCosas
        operaciones++;
        if(indice != c.cantCosas) {
            // caso recursivo
                operaciones = operaciones + 2;
                if(candActual.peso + c.cosas[indice].peso <= c.capacidad) {
                    candActual.agregar(indice,c.cosas[indice].peso,c.cosas[indice].valor);
                    camionAux(candActual,c, indice+1, mejorSol,valorOptimo);

                    //sacamos el elemento agregado para hacer backtracking
                    candActual.sacar(indice,c.cosas[indice].peso, c.cosas[indice].valor);
                }

   		        else{
                    operaciones++;
		   	        if(candActual.valor > mejorSol.valor) {
                        operaciones = operaciones + 2;
           		        mejorSol = candActual;
      			    }
                    return;
  		       }
               camionAux(candActual,c, indice+1, mejorSol,valorOptimo - c.cosas[indice].valor);
               operaciones++;
               if(candActual.valor > mejorSol.valor) {
                   operaciones++;
                   mejorSol = candActual;
               }
        }
    }
}


int main(int argc, char* argv[]) {

    // leo los datos de entrada
    string ruta;
    if(argc >= 2) {
        ruta = argv[1];
    } else {
        ruta="Tp1Ej2.in";
    }
    fstream f (ruta.c_str());
    assert(f.is_open());
    string caso;
    f >> caso;

    // preparo el archivo de salida
    string salida;
    if(argc > 2) {
        salida = argv[2];
    } else {
        salida = "Tp1Ej2.out";
    }
    ofstream o (salida.c_str());

    // leo la secuencia de cosas
    while(caso != "Fin"){
        unsigned cantElem, capacidad;
        f >> cantElem;
        f >> capacidad;
	int* indices = new int[cantElem];
        Cosa* cs = new Cosa[cantElem];
        for(unsigned i = 0; i < cantElem; i++) {
            unsigned peso, valor;
            f >> valor;
            f >> peso;
            cs[i] = Cosa(valor,peso);
	    indices[i] = i;
        }

        // resuelvo este caso
        Camion cam = Camion(cs,capacidad,cantElem);
        SolucionPosible* s = new SolucionPosible(cam.cantCosas);
        operaciones = 0;
        camion(cam,*s,indices);

        // almaceno la salida del programa
        o << s->valor << " ";

        unsigned contador = 0;
	bool * indicesPosta = new bool[cantElem];
        for(unsigned int i = 0; i < cam.cantCosas; i++) {
            if(s->guardo[i]) {
                contador++;
            }
        }

        o << contador << " ";
        for(unsigned int i = 0; i < cam.cantCosas; i++) {
            if(s->guardo[i]) {
		indicesPosta[indices[i]] = true;
                //o << indices[i]+1 << " ";
            }
	    else{
		indicesPosta[indices[i]] = false;
	    }
        }
	delete[] indices;
	for(unsigned int i = 0; i < cam.cantCosas; i++) {
            if(indicesPosta[i]) {
		o << i+1 << " ";
            }
	}
        o << endl;
        cout << operaciones << endl;
        delete [] cs;
        delete s;
	delete [] indicesPosta;

        f >> caso;
    }
    return 0;
}
