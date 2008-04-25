#ifndef _BuscadorCaminoTCI_H
#define _BuscadorCaminoTCI_H

#include <cstdlib>
#include <iostream>
#include <list>

#include "Grafo.h"

using namespace std;

class BuscadorCaminoTCI {
    public:
        BuscadorCaminoTCI(Grafo& grafo);
        ~BuscadorCaminoTCI();
        list<unsigned> buscarCamino();
        void imprimirCamino();
    private:
        Grafo& g;
        bool resuelto;
        list<unsigned> camino;
        bool ** matA;
        bool ** matB;

        void resolver();
        list<unsigned> caminoQueTerminaEnA(unsigned a, unsigned b);
        list<unsigned> caminoQueTerminaEnB(unsigned a, unsigned b);
};
#endif /*_BuscadorCaminoTCI_H*/
