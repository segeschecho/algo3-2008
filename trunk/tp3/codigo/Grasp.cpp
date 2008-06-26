#include "Grasp.h"

Grasp :: Grasp(Dibujo& original) {
    d = &original;
}

Dibujo Grasp :: resolver(float alfa) {
    alfa = 0.95;
	//primero una greedy a secas
    Dibujo mejorSolucion (HeuristicaConstructiva(*d).construirSolucion());
    mejorSolucion = BusquedaLocal(*d).hallarMinimoLocal(mejorSolucion);

    vector<unsigned int> indicesP1, indicesP2;
    armarIndices(mejorSolucion.nodosEnP1(), indicesP1);
    armarIndices(mejorSolucion.nodosEnP2(), indicesP2);
    unsigned int crucesMejor = contadorDeCruces(mejorSolucion.nodosEnP1(),mejorSolucion.nodosEnP2(), d->grafo()->ejes(), indicesP1, indicesP2);
    unsigned maxIteraciones = mejorSolucion.nodosEnP1().size()+mejorSolucion.nodosEnP2().size();
    unsigned iteraciones = 0;
    while (iteraciones < maxIteraciones) {
        Dibujo nuevaSolucion (HeuristicaConstructiva(*d).construirSolucion(alfa,true));
        nuevaSolucion = BusquedaLocal(*d).hallarMinimoLocal(nuevaSolucion);
        armarIndices(nuevaSolucion.nodosEnP1(), indicesP1);
        armarIndices(nuevaSolucion.nodosEnP2(), indicesP2);
        unsigned int crucesNueva = contadorDeCruces(nuevaSolucion.nodosEnP1(),nuevaSolucion.nodosEnP2(), d->grafo()->ejes(), indicesP1, indicesP2);
        if (crucesNueva < crucesMejor) {
            mejorSolucion = nuevaSolucion;
            crucesMejor = crucesNueva;
			maxIteraciones = maxIteraciones / 2;
        }
		else{
			alfa = min(0.0,alfa-0.02);
		}
        iteraciones++;
    }

    return mejorSolucion;
}

Grasp :: ~Grasp() {
}

