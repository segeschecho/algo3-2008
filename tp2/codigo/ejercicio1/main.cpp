#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <assert.h>
#define print cout<<
#include "Grafo.h"
using namespace std;
bool* ejercicio1(Grafo* grafo,unsigned rels, unsigned& cantGanadores);

/* parseo de la entrada, grabacion de la salida */
int main(int argc, char* argv[])
{    // leo los datos de entrada
    string ruta;
    if(argc >= 2) {
        ruta = argv[1];
    } else {
        ruta="Tp2Ej1.in";
    }
    fstream f (ruta.c_str());
    // FIXME: hay que poner un chequeo no-abortante aca
    // y poner un mensaje de error.
    assert(f.is_open());

    // preparo el archivo de salida
    string salida;
    if(argc > 2) {
        salida = argv[2];
    } else {
        salida = "Tp2Ej1.out";
    }
    ofstream o (salida.c_str());
    unsigned buffer, nodos, relaciones;

    while (true) {
	f >> buffer;
        nodos = buffer;
	f >> buffer;
	relaciones = buffer;
	if(nodos == relaciones && nodos == 0){
	    break;
        }
    unsigned rels = relaciones;
	list<pair<unsigned,unsigned> > l;
        while(relaciones > 0){
	    unsigned x, y;
	    f >> x;
	    f >> y;
	    l.push_back(pair<unsigned,unsigned>(x-1,y-1));
	    relaciones --;
	}
	Grafo* g = new Grafo(nodos,l);
	unsigned cantGanadores = 0;
    	bool* sol =ejercicio1(g,rels,cantGanadores);
    	o<<cantGanadores;
    	if( sol != NULL){

            for(unsigned i = 0; i < g->nodos; i++){
                if(sol[i]){
                o<<" "<<i+1;
                }

            }
    	}
        o<<endl;
    	delete g;
    	delete[] sol;
        }
	return 0;
    }

// hace un dfs y asigna en valioso a que nodo le toca la numeracion mas alta
void dfs(Grafo* grafo, unsigned nodo, unsigned& num, bool* visitado, unsigned& valioso){
    visitado[nodo] = true;
    list<unsigned> :: iterator principio = grafo->verticesOut[nodo].begin();
    list<unsigned> :: iterator final = grafo->verticesOut[nodo].end();
    for(list<unsigned> :: iterator each = principio; each != final; each++){
        if (! visitado[*each])
            dfs(grafo,*each,num,visitado,valioso);
    }


    if(num == (grafo -> nodos-1)){
		valioso = nodo;
	}
	// incrementamos num para que el padre de este nodo, tenga numero mas alto
    num += 1;
}

// hace dfs hasta tocar a todos los nodos, y obtener uno con numeracion
// cantidad de nodos - 1
void auxdfs(Grafo* grafo, bool* visitado, unsigned& valioso){
    unsigned num = 0;
        for(unsigned i = 0;  i < grafo->nodos; i++){
            if(! visitado[i]){
                dfs(grafo,i,num,visitado,valioso);
            }
	}
}

// hace dfs partiendo desde un nodo y cuenta a cuantos nodos llegamos
unsigned dfsContador(Grafo* grafo, unsigned nodo, bool* visitado){
    unsigned contador = 1;
    visitado[nodo] = true;
    list<unsigned> :: iterator principio = grafo->verticesOut[nodo].begin();
    list<unsigned> :: iterator final = grafo->verticesOut[nodo].end();
    for(list<unsigned> :: iterator each = principio; each != final; each++){
		if (! visitado[*each])
            contador+=dfsContador(grafo,*each,visitado);
    }
    return contador;
}

// hace dfs pero usando las aristas de salida
// guarda en una lista a todos los nodos que toca
// en el contexto que se usa, determina la componente fuertemente conexa en la que esta el nodo de origen
void dfsReverso(Grafo* grafo, unsigned nodo, bool* visitado,list<unsigned>* listaGanadores){
    visitado[nodo] = true;
    listaGanadores->push_back(nodo);
    list<unsigned> :: iterator principio = grafo->verticesIn[nodo].begin();
    list<unsigned> :: iterator final = grafo->verticesIn[nodo].end();
    for(list<unsigned> :: iterator each = principio; each != final; each++){
        if (! visitado[*each])
            dfsReverso(grafo,*each,visitado,listaGanadores);


    }
}
/* resuelve el ejercicio 1 */
bool* ejercicio1(Grafo* grafo,unsigned rels, unsigned & cantGanadores){
    //caso facil: el grafo subyacente no puede ser conexo
     if(rels < grafo->nodos - 1){
        cantGanadores = 0;
        return NULL;
    }
    bool* visitado = new bool[grafo->nodos];
	for(unsigned i = 0; i < grafo->nodos; i++){
			visitado[i] = false;
     }
     // primero averiguamos quien es el mas valioso
    unsigned valioso;
	auxdfs(grafo,visitado,valioso);
    // reiniciamos el marcador de visitado
     for(unsigned i = 0; i < grafo->nodos; i++){
        visitado[i] = false;
    }
    // verificamos a cuantos les gana nuestro potencial ganador
    unsigned aCuantosLlega = dfsContador(grafo,valioso,visitado);
    // si el no le gana a todos, no hay ganador
    if(aCuantosLlega != grafo->nodos){
        cantGanadores = 0;
		delete[] visitado;
        return NULL;
    }
    else{
        //si les gana a todos, buscamos su componente fuertemente conexa
        for(unsigned i = 0; i < grafo->nodos; i++){
            visitado[i] = false;
        }
        list<unsigned>* listaGanadores = new list<unsigned>();
        //si hacemos dsf al reves, encontramos la componente conexa
        dfsReverso(grafo,valioso,visitado,listaGanadores);
        cantGanadores = listaGanadores->size();
        bool* ganadores = new bool[grafo->nodos];
        //vamos a tener que hacer bucketSort para devolverlos ordenados
        for(int i = 0; i < grafo-> nodos; i++){
        ganadores[i] = false;
        }
        for(list<unsigned> :: iterator it = listaGanadores->begin(); it != listaGanadores->end(); it++){
        ganadores[*it] = true;
        }
		delete[] visitado;
		delete listaGanadores;
        return ganadores;
    }
}
