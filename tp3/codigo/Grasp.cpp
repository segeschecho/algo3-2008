#include "Grasp.h"

Grasp :: Grasp(Dibujo& original) {
    d = &original;
}

Dibujo Grasp :: resolver() {
    float alfa = 0.95;
    
    Dibujo mejorSolucion (HeuristicaConstructiva(*d).construirSolucion(1, false));
    mejorSolucion = BusquedaLocal(*d).hallarMinimoLocal(mejorSolucion);

    vector<unsigned int> indicesP1, indicesP2;
    armarIndices(mejorSolucion.nodosEnP1(), indicesP1, mejorSolucion.grafo()->cantNodos());
    armarIndices(mejorSolucion.nodosEnP2(), indicesP2, mejorSolucion.grafo()->cantNodos());
    unsigned int crucesMejor = contadorDeCruces(mejorSolucion.nodosEnP1(),mejorSolucion.nodosEnP2(), d->grafo()->ejes(), indicesP1, indicesP2);
    unsigned maxIteraciones = mejorSolucion.nodosEnP1().size()+mejorSolucion.nodosEnP2().size();
    unsigned iteraciones = 0;
    
    while (iteraciones < maxIteraciones) {
        Dibujo nuevaSolucion (HeuristicaConstructiva(*d).construirSolucion(alfa,true));
        nuevaSolucion = BusquedaLocal(*d).hallarMinimoLocal(nuevaSolucion);
        armarIndices(nuevaSolucion.nodosEnP1(), indicesP1, nuevaSolucion.grafo()->cantNodos());
        armarIndices(nuevaSolucion.nodosEnP2(), indicesP2, nuevaSolucion.grafo()->cantNodos());
        unsigned int crucesNueva = contadorDeCruces(nuevaSolucion.nodosEnP1(),nuevaSolucion.nodosEnP2(), d->grafo()->ejes(), indicesP1, indicesP2);
        if (crucesNueva < crucesMejor) {
            mejorSolucion = nuevaSolucion;
            crucesMejor = crucesNueva;
			maxIteraciones = maxIteraciones / 2;
        }
		else{
			alfa = min(0.2,alfa-0.02);
            iteraciones++;
		}
    }
    return mejorSolucion;
}

