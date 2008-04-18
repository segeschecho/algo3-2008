#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>

#include "SolucionPosible.h"

using namespace std;
void mergeSort(int pri, int ult,Cosa* cosas, int cantElem, int* indices);
void mergeSortConIndices(Cosa* cos, int cantElem, int* inds);
void merge(int pri, int ult,Cosa* cosas, int cantElem, int* indices) ;

/* ordena el arreglo de cosas por peso, y deja en indices la posicion actual de los elementos,
   es decir luego de la funcion, indices[i] indica en que posicion quedo el elemento i */
void mergeSortConIndices(Cosa* cos, int cantElem, int* inds){
    for(int i = 0; i < cantElem; i++){
        inds[i] = i;
    }
    mergeSort(0,cantElem-1,cos,cantElem,inds);
}

/* hace el mergeSort propiamente dicho */
void mergeSort(int pri, int ult,Cosa* cosas, int cantElem, int* indices) {
    if(pri < ult) {
        int pmedio = (pri + ult)/2;
        mergeSort(pri, pmedio,cosas,cantElem,indices);
        mergeSort(pmedio+1, ult,cosas,cantElem,indices);
        merge(pri,ult,cosas,cantElem,indices);
    }
}

/* realiza el merge para los dos arreglos, el de cosas y el de indices */
void merge(int pri, int ult,Cosa* cosas, int cantElem, int* indices) {
    int i,j, cont = 0;
    int tamano = ult - pri + 1;
    int pmedio = (pri + ult)/2;

    Cosa *tmp=new Cosa[tamano];
    int * indicesAux = new int[tamano];
    for(i = pri; i <= pmedio; i++)
    {
        tmp[cont] = cosas[i];
        indicesAux[cont] = indices[i];
        cont++;
    }

    for(i = ult; i > pmedio; i--)
    {
        tmp[cont] = cosas[i];
    	indicesAux[cont] = indices[i];
        cont++;
    }

    cont = pri;
    for(i = 0, j = tamano - 1; i <= j;)
    {
        if(tmp[i].peso <= tmp[j].peso)
        {
            cosas[cont]=tmp[i];
            indices[cont] = indicesAux[i];
            i++;
        }
        else
        {
            cosas[cont] = tmp[j];
            indices[cont] = indicesAux[j];
            j--;
        }
        cont++;
    }
    delete[] indicesAux;
    delete[] tmp;
}


void camionAux(SolucionPosible& candActual,Camion&c,unsigned indice,SolucionPosible& mejorSol,unsigned valorOptimo);

// obtiene el valor todas las cosas del camion
unsigned sumar(Cosa* c, unsigned int cant){
    unsigned valor = 0;
    for(int i = 0; i < cant; i++){
        valor += c[i].valor;
    }
    return valor;
}

//elige que cosas llevar en el camion
void camion(Camion& c,SolucionPosible& mejorSol,int* indices) {
    SolucionPosible * s = new SolucionPosible(c.cantCosas);
    mergeSortConIndices(c.cosas,c.cantCosas,indices);
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
//arma la solucion de que llevar mediante backtracking
void camionAux(SolucionPosible& candActual, Camion& c,unsigned indice,SolucionPosible& mejorSol,unsigned valorOptimo){
    // cuando ya llegue hasta el ultimo elemento paro, pero me fijo si consegui una mejor solucion

    if(indice == c.cantCosas && candActual.valor > mejorSol.valor) {
        mejorSol = candActual;
    }

    if(candActual.valor + valorOptimo < mejorSol.valor){
        //la rama no tiene potencial
        return;
    }
    else {
        // caso base: indice == c.cantCosas
        if(indice != c.cantCosas) {
            // caso recursivo
                if(candActual.peso + c.cosas[indice].peso <= c.capacidad) {
                    candActual.agregar(indice,c.cosas[indice].peso,c.cosas[indice].valor);
                    camionAux(candActual,c, indice+1, mejorSol,valorOptimo);
                    //sacamos el elemento agregado para hacer backtracking
                    candActual.sacar(indice,c.cosas[indice].peso, c.cosas[indice].valor);
                }

   		        else{
		   	        if(candActual.valor > mejorSol.valor) {
           		        mejorSol = candActual;
      			    }
                    return;
  		       }
               camionAux(candActual,c, indice+1, mejorSol,valorOptimo - c.cosas[indice].valor);
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
		//indices va  a guardar los indices luego de ordenar el arreglo
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
        camion(cam,*s,indices);

        // almaceno la salida del programa
        o << s->valor << " ";

        unsigned contador = 0;
		//indices posta usa el diccionario de indices para armar el verdadero arreglo de bools que representa a la solucion
		bool * indicesPosta = new bool[cantElem];
		//cuento cantidad de elementos
        for(unsigned int i = 0; i < cam.cantCosas; i++) {
            if(s->guardo[i]) {
                contador++;
            }
        }
        o << contador << " ";
		// restablezco los indices
        for(unsigned int i = 0; i < cam.cantCosas; i++) {
            if(s->guardo[i]) {
				indicesPosta[indices[i]] = true;
            }
			else{
				indicesPosta[indices[i]] = false;
			}
        }
	    delete[] indices;
		//saco la solucion al archivo con el formato pedido
		for(unsigned int i = 0; i < cam.cantCosas; i++) {
            if(indicesPosta[i]) {
				o << i+1 << " ";
            }
		}
        o << endl;
        delete [] cs;
        delete s;
	delete [] indicesPosta;

        f >> caso;
    }
    return 0;
}
