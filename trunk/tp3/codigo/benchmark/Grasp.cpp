#include "Grasp.h"

Grasp :: Grasp(Dibujo& original) {
    d = &original;
}

Dibujo Grasp :: resolver(float alfa) {
    Dibujo mejorSolucion (HeuristicaConstructiva(*d).construirSolucion(alfa));
    mejorSolucion = BusquedaLocal(*d).hallarMinimoLocal(mejorSolucion);

    vector<unsigned int> indicesP1, indicesP2;
    armarIndices(mejorSolucion.nodosEnP1(), indicesP1);
	cout<<"paso esto?"<<endl;
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
//alfa fija en .75, randomPos = false, parada=maxParticion 
Dibujo Grasp :: resolver1(float alfa) {
    alfa = 0.75;
	//primero una greedy a secas
    Dibujo mejorSolucion (HeuristicaConstructiva(*d).construirSolucion());
    mejorSolucion = BusquedaLocal(*d).hallarMinimoLocal(mejorSolucion);

    vector<unsigned int> indicesP1, indicesP2;
    armarIndices(mejorSolucion.nodosEnP1(), indicesP1);
    armarIndices(mejorSolucion.nodosEnP2(), indicesP2);
    unsigned int crucesMejor = contadorDeCruces(mejorSolucion.nodosEnP1(),mejorSolucion.nodosEnP2(), d->grafo()->ejes(), indicesP1, indicesP2);
    unsigned maxIteraciones = max(mejorSolucion.nodosEnP1().size(),mejorSolucion.nodosEnP2().size());
    unsigned iteraciones = 0;
    while (iteraciones < maxIteraciones) {
        Dibujo nuevaSolucion (HeuristicaConstructiva(*d).construirSolucion(alfa));
        nuevaSolucion = BusquedaLocal(*d).hallarMinimoLocal(nuevaSolucion);
        armarIndices(nuevaSolucion.nodosEnP1(), indicesP1);
        armarIndices(nuevaSolucion.nodosEnP2(), indicesP2);
        unsigned int crucesNueva = contadorDeCruces(nuevaSolucion.nodosEnP1(),nuevaSolucion.nodosEnP2(), d->grafo()->ejes(), indicesP1, indicesP2);
        if (crucesNueva < crucesMejor) {
            mejorSolucion = nuevaSolucion;
            crucesMejor = crucesNueva;
        }
        iteraciones++;
    }

    return mejorSolucion;
}
//alfa fija en .75, randomPos = false, parada=cantNodos /2 por mejora
Dibujo Grasp :: resolver2(float alfa) {
    alfa = 0.75;
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
        Dibujo nuevaSolucion (HeuristicaConstructiva(*d).construirSolucion(alfa));
        nuevaSolucion = BusquedaLocal(*d).hallarMinimoLocal(nuevaSolucion);
        armarIndices(nuevaSolucion.nodosEnP1(), indicesP1);
        armarIndices(nuevaSolucion.nodosEnP2(), indicesP2);
        unsigned int crucesNueva = contadorDeCruces(nuevaSolucion.nodosEnP1(),nuevaSolucion.nodosEnP2(), d->grafo()->ejes(), indicesP1, indicesP2);
        if (crucesNueva < crucesMejor) {
            mejorSolucion = nuevaSolucion;
            crucesMejor = crucesNueva;
			maxIteraciones = maxIteraciones / 2;
        }
        iteraciones++;
    }

    return mejorSolucion;
}
//alfa fija en .75, randomPos = true, parada=maxParticion 
Dibujo Grasp :: resolver3(float alfa) {
    alfa = 0.75;
	//primero una greedy a secas
    Dibujo mejorSolucion (HeuristicaConstructiva(*d).construirSolucion());
    mejorSolucion = BusquedaLocal(*d).hallarMinimoLocal(mejorSolucion);

    vector<unsigned int> indicesP1, indicesP2;
    armarIndices(mejorSolucion.nodosEnP1(), indicesP1);
    armarIndices(mejorSolucion.nodosEnP2(), indicesP2);
    unsigned int crucesMejor = contadorDeCruces(mejorSolucion.nodosEnP1(),mejorSolucion.nodosEnP2(), d->grafo()->ejes(), indicesP1, indicesP2);
    unsigned maxIteraciones = max(mejorSolucion.nodosEnP1().size(),mejorSolucion.nodosEnP2().size());
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
        }
        iteraciones++;
    }

    return mejorSolucion;
}
//alfa fija en .75, randomPos = true, parada=cantNodos /2 por mejora
Dibujo Grasp :: resolver4(float alfa) {
    alfa = 0.75;
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
        iteraciones++;
    }

    return mejorSolucion;
}
//alfa movil, randomPos = false, parada=maxParticion 
Dibujo Grasp :: resolver5(float alfa) {
    alfa = 0.95; //no le pongo 1, para que no se miope
	//primero una greedy a secas
    Dibujo mejorSolucion (HeuristicaConstructiva(*d).construirSolucion());
    mejorSolucion = BusquedaLocal(*d).hallarMinimoLocal(mejorSolucion);

    vector<unsigned int> indicesP1, indicesP2;
    armarIndices(mejorSolucion.nodosEnP1(), indicesP1);
    armarIndices(mejorSolucion.nodosEnP2(), indicesP2);
    unsigned int crucesMejor = contadorDeCruces(mejorSolucion.nodosEnP1(),mejorSolucion.nodosEnP2(), d->grafo()->ejes(), indicesP1, indicesP2);
    unsigned maxIteraciones = max(mejorSolucion.nodosEnP1().size(),mejorSolucion.nodosEnP2().size());
    unsigned iteraciones = 0;
    while (iteraciones < maxIteraciones) {
        Dibujo nuevaSolucion (HeuristicaConstructiva(*d).construirSolucion(alfa,false));
        nuevaSolucion = BusquedaLocal(*d).hallarMinimoLocal(nuevaSolucion);
        armarIndices(nuevaSolucion.nodosEnP1(), indicesP1);
        armarIndices(nuevaSolucion.nodosEnP2(), indicesP2);
        unsigned int crucesNueva = contadorDeCruces(nuevaSolucion.nodosEnP1(),nuevaSolucion.nodosEnP2(), d->grafo()->ejes(), indicesP1, indicesP2);
        if (crucesNueva < crucesMejor) {
            mejorSolucion = nuevaSolucion;
            crucesMejor = crucesNueva;
        }
		else{
			alfa = min(0.0,alfa-0.25);
		}
        iteraciones++;
    }

    return mejorSolucion;
}
//alfa fija en .75, randomPos = false, parada=cantNodos /2 por mejora
Dibujo Grasp :: resolver6(float alfa) {
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
        Dibujo nuevaSolucion (HeuristicaConstructiva(*d).construirSolucion(alfa,false));
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
			alfa = min(0.0,alfa-0.25);
		}
        iteraciones++;
    }

    return mejorSolucion;
}

//alfa movil, randomPos = true, parada=maxParticion 
Dibujo Grasp :: resolver7(float alfa) {
    alfa = 0.95; //no le pongo 1, para que no se miope
	//primero una greedy a secas
    Dibujo mejorSolucion (HeuristicaConstructiva(*d).construirSolucion());
    mejorSolucion = BusquedaLocal(*d).hallarMinimoLocal(mejorSolucion);

    vector<unsigned int> indicesP1, indicesP2;
    armarIndices(mejorSolucion.nodosEnP1(), indicesP1);
    armarIndices(mejorSolucion.nodosEnP2(), indicesP2);
    unsigned int crucesMejor = contadorDeCruces(mejorSolucion.nodosEnP1(),mejorSolucion.nodosEnP2(), d->grafo()->ejes(), indicesP1, indicesP2);
    unsigned maxIteraciones = max(mejorSolucion.nodosEnP1().size(),mejorSolucion.nodosEnP2().size());
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
        }
		else{
			alfa = min(0.0,alfa-0.25);
		}
        iteraciones++;
    }

    return mejorSolucion;
}
//alfa fija en .75, randomPos = true, parada=cantNodos /2 por mejora
Dibujo Grasp :: resolver8(float alfa) {
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
			alfa = min(0.0,alfa-0.25);
		}
        iteraciones++;
    }

    return mejorSolucion;
}

Grasp :: ~Grasp() {
}

