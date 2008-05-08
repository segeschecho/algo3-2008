#ifndef _BuscadorCaminoTCI_H
#define _BuscadorCaminoTCI_H

#include <cstdlib>
#include <iostream>
#include <list>

#include "Grafo.h"

using namespace std;
//TCI: tabulado completo al inicio
class BuscadorCaminoTCI {
    public:
        BuscadorCaminoTCI(Grafo& grafo);
        ~BuscadorCaminoTCI();
        list<unsigned> buscarCamino();
        void imprimirCamino();
        void guardarCamino(ostream& o);
    private:
        Grafo& g;
        bool resuelto;
        bool ** matA;
        bool ** matB;

        void resolver();
        list<unsigned>* caminoQueTerminaEnA(unsigned a, unsigned b);
        list<unsigned>* caminoQueTerminaEnB(unsigned a, unsigned b);
};
#endif /*_BuscadorCaminoTCI_H*/
