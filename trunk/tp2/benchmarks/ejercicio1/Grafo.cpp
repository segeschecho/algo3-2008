#include "Grafo.h"

Grafo:: Grafo(unsigned cantNodos, list<pair<unsigned,unsigned> >& relaciones){
    nodos = cantNodos;
    verticesIn = new list<unsigned >[nodos];
    verticesOut = new list<unsigned>[nodos];
    for(list<pair<unsigned,unsigned> >::iterator each = relaciones.begin(); each != relaciones.end(); each++){
        verticesIn[each->second].push_front(each->first);
        verticesOut[each->first].push_front(each->second);
    }
}

std::ostream& operator<< (std::ostream& o, const Grafo& g){
    o<<"grafo con: "<<g.nodos<<" nodos"<< endl;
    for(unsigned i = 0; i < g.nodos; i++){
        for(list<unsigned >::iterator each = g.verticesIn[i].begin(); each != g.verticesIn[i].end(); each++){

        o<<"("<<*each<<", "<<i<<") ";
        }
    }
    return o;
}

Grafo :: ~Grafo(){
    delete[] verticesIn;
    delete[] verticesOut;
}


