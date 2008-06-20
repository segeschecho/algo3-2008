#include "Grasp.h"

Grasp :: Grasp(Dibujo& original) {
    d = &original;
}

Dibujo Grasp :: resolver(float alfa) {
    Dibujo mejorSolucion (HeuristicaConstructiva(*d).construirSolucion(alfa));
    mejorSolucion = BusquedaLocal(*d).hallarMinimoLocal(mejorSolucion);

    vector<unsigned int> indicesP1, indicesP2;
    armarIndices(mejorSolucion.nodosEnP1(), indicesP1);
    armarIndices(mejorSolucion.nodosEnP2(), indicesP2);
    unsigned int crucesMejor = contadorDeCruces(mejorSolucion.nodosEnP1(),mejorSolucion.nodosEnP2(), d->grafo()->ejes(), indicesP1, indicesP2);
    int sinMejorar = 0;

    while (sinMejorar < 100) {
        Dibujo nuevaSolucion (HeuristicaConstructiva(*d).construirSolucion(alfa));
        nuevaSolucion = BusquedaLocal(*d).hallarMinimoLocal(nuevaSolucion);
        armarIndices(nuevaSolucion.nodosEnP1(), indicesP1);
        armarIndices(nuevaSolucion.nodosEnP2(), indicesP2);
        unsigned int crucesNueva = contadorDeCruces(nuevaSolucion.nodosEnP1(),nuevaSolucion.nodosEnP2(), d->grafo()->ejes(), indicesP1, indicesP2);
        if (crucesNueva < crucesMejor) {
            mejorSolucion = nuevaSolucion;
            crucesMejor = crucesNueva;
            sinMejorar = 0;
        }
        else {
            sinMejorar++;
        }
    }

    return mejorSolucion;
}

Grasp :: ~Grasp() {
}

