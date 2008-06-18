#ifndef _Heuristica_Constructiva_H
#define _Heuristica_Constructiva_H

#include <vector>
#include <list>
#include <time.h>

#include "GrafoBipartito.h"
#include "Dibujo.h"
#include "conteoDeCruces.h"

using namespace std;

class HeuristicaConstructiva {

public:
    HeuristicaConstructiva(Dibujo& original);
    Dibujo construirSolucion(float alfa=1.0, bool randomPos=false);

private:
    Dibujo* d;
    list<nodo> fijo1, fijo2, movil1, movil2;
    float alfa;
    unsigned cruces;
    bool randomPos;
    vector< list<nodo> > adyParcial;
    vector< unsigned > gradoParcial;
    vector< unsigned > posiciones;
    vector< bool > esMovil;


    void inicializar();

    nodo tomarSiguiente(list<nodo>& moviles);
    nodo tomarSiguiente1();
    nodo tomarSiguiente2();
    
    void ordenarPorGradoParcial(list<nodo>& moviles);

    void insertar(nodo, list<nodo>& fijos, list<nodo>& otrosFijos);
    void insertarEn1(nodo);
    void insertarEn2(nodo);

};

#endif
