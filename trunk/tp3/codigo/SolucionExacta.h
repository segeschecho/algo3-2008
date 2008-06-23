#ifndef _Solucion_Exacta_H
#define _Solucion_Exacta_H

#include <list>
#include <vector>

#include "GrafoBipartito.h"
#include "Dibujo.h"
#include "conteoDeCruces.h"
#include "HeuristicaConstructiva.h"

using namespace std;

unsigned cuantasCombinaciones(unsigned, unsigned);


class SolucionExacta {

public:
    SolucionExacta(Dibujo& original);
    Dibujo resolver();

private:
    Dibujo* d;
    Dibujo mejorDibujo;
    unsigned cruces;
    bool invertirLados;
    list<nodo> l1, l2;
    list<nodo> fijo1, fijo2;
    list<nodo> movil1, movil2;
    vector<unsigned> posiciones1;
    vector<unsigned> posiciones2;
    vector< vector<unsigned> > tabla1;
    vector< vector<unsigned> > tabla2;
    vector< list<nodo> > adyp1;

    void inicializar();
    void mejorar();
    void tabular1();
    void tabular2();
    unsigned minimosCrucesRestantes1();
    unsigned minimosCrucesRestantes2();
    void sacarPrincipio1();
    void sacarPrincipio2();
    void agregarAtras1();
    void agregarAtras2();
    void retrasar1(list<nodo>::iterator& i, unsigned pos);
    void retrasar2(list<nodo>::iterator& i, unsigned pos);

};

#endif
