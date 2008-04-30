#ifndef _Grafo_H
#define _Grafo_H
#include <cstdlib>
#include <list>

using namespace std;

class Grafo {
    public:
        unsigned n;
        unsigned m;
        Grafo(unsigned nodos, list<pair<unsigned,unsigned> >& relaciones);
        ~Grafo();
        bool estanConectados(unsigned a, unsigned b);
    private:
        bool ** ejes;
};
#endif /*_Grafo_H*/

