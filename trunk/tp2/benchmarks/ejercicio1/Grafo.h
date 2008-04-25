#ifndef _Grafo_H
#define _Grafo_H
#include <iostream>
#include <cstdlib>
#include <list>
using namespace std;

class Grafo{
    public:
    Grafo(unsigned nodos,list<pair<unsigned,unsigned> >&relaciones);
    list<unsigned> * verticesOut;
    list<unsigned> * verticesIn;
    ~Grafo();
    unsigned nodos;
    friend std::ostream& operator<< (ostream&, const Grafo&);
};
#endif /*_Grafo_H*/
