#include <iostream>
#include "Dibujo.h"
#include "GrafoBipartito.h"
#include <math.h>
#include "BusquedaLocal.h"
#include "Tp3.h"
#include "HeuristicaConstructiva.h"
using namespace std;
#define print(a) cout<<a<<endl;

int main(int argc, char* argv[]) {
    //cargamos un dibujo
	Dibujo d ("Tp3.in");
    // Tp3 se encarga de limpiar el grafo. ya se q el nombre es choto
    Tp3 tp3(d);
   //generamos un heuristica constructiva con el grafo ya limpio
    HeuristicaConstructiva hc(*tp3.dibujoLimpio);
   //tomamos la solucion que nos da le heuristica
    Dibujo dib =hc.construirSolucion();
    cout<<"dib tiene: "<<dib.contarCruces()<<" cruces"<<endl;
	//a partir del dibujo limpio tambien armamos la busqueda local
    BusquedaLocal bl(*tp3.dibujoLimpio);
	//pedimos que nos mejore el dibujo de la heur constructiva
	//nos da uno nuevo
    Dibujo carlos = bl.hallarMinimoLocal(dib);
    cout<<"carlos tiene "<<carlos.contarCruces()<<" cruces"<<endl;
	//construimos un nuevo dibujo con el orden dado por la heuristica, pero los nombres de nodos correctos
    Dibujo fabian =tp3.reconstruirDibujo(carlos);
   //luego de todo tenemos estos cruces
	cout<<"luego de pasarlo tenemos"<<fabian.contarCruces()<<" cruces (debe ser igual que carlos :P)"<<endl;
	//lo guardamos en un aromatico archivo
    fabian.guardar("caca.txt");
	//esto lo pone emilio sino el visual c++ le cierra la consola :P
    system("PAUSE");
    return 0;
}
