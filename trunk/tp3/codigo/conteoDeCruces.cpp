#include "Dibujo.h"
#include <math.h>

#define BETA(a) a ? 1 : 0
#define print(a) cout<<a<<endl;

nodo maxElem(const vector<nodo>& p) {
  nodo maximo = p[0];
  for(unsigned int i = 1; i < p.size(); i++) {
    if ( p[i] > maximo) {
      maximo = p[i];
    }
  }
  return maximo;
}

void radixSort(list<eje>& listaEjes, unsigned int size1, unsigned int size2) {
    // bucket1 y bucket2 son los buckets donde voy a guardar los ejes
    vector< list<eje> > bucket1 (size1);
    vector< list<eje> > bucket2 (size2);

    //ordeno por segunda componente
    list<eje>::const_iterator it (listaEjes.begin());
    while (it != listaEjes.end()) {
        bucket2[it->segundo].push_back(*it);
        it++;
    }

    listaEjes.clear();
    for(unsigned int i = 0; i < size2; i++) {
        listaEjes.splice(listaEjes.end(), bucket2[i]);
    }

    //ordeno por primera componente
    it = listaEjes.begin();
    while (it != listaEjes.end()) {
        bucket1[it->primero].push_back(*it);
        it++;
    }

    listaEjes.clear();
    for(unsigned int i = 0; i < size1; i++) {
        listaEjes.splice(listaEjes.end(), bucket1[i]);
    }
}

unsigned int acumTree (const list<eje>& l, unsigned int cantHojas) {
    // Saco donde estara guardado el primer indice
    int primerIndice = (int)pow(2, ceil(log((float)cantHojas)/log((float)2)));
    // Creo el arbol acumulador inicializado en 0
    unsigned int* arbol = new unsigned int [2*primerIndice - 1];
    for (int i = 0; i < 2*primerIndice - 1; i++) {
        arbol[i] = 0;
    }
    // Me paro en la hoja izquierda
    primerIndice -= 1;

    unsigned int cruces = 0;
    // Inserto los ejes
    list<eje>::const_iterator it(l.begin());
    while (it != l.end()) {
        // Indice es la hoja a la que pertenece el eje
        unsigned int indice = it->segundo + primerIndice;
        // Hay un eje mas en esta hoja
        arbol[indice] += 1;

        // Recorro hacia arriba
        while(indice > 0) {
            // Si estoy parado en un nodo izquierdo, miro al hermano
            // Para saber cuantos cruces agrego
            if (indice % 2 == 1) {
                cruces += arbol[indice + 1];
            }
            // Subo un nivel
            indice = (indice - 1)/2;
            // Aumento el acumulador del nodo
            arbol[indice] += 1;
        }
        it++;
    }
    delete [] arbol;
    return cruces;
}

unsigned int contadorDeCruces (const vector<nodo>& p1, const vector<nodo>& p2, const vector< list<nodo> >& ejes, vector<nodo>* indicesP1, vector<nodo>* indicesP2) {
	// Quiero tener a la de menor tama�o como segundo parametro para lograr O(m*log(min(p1,p2))
    if(p2.size() < 2){
        return 0;
    }
    if (p1.size() < p2.size()) {
        return contadorDeCruces(p2, p1, ejes, indicesP2, indicesP1);
    }

    bool existiaIndicesP1 = true;
    bool existiaIndicesP2 = true;
    // Si no me dieron los arreglos de indices, me los hago
    if (indicesP1 == NULL) {
        existiaIndicesP1 = false;
        indicesP1 = new vector<nodo> (maxElem(p1) + 1);
        for (unsigned int i = 0; i < p1.size(); i++) {
            (*indicesP1)[p1[i]] = i;
        }
    }
    if (indicesP2 == NULL){
        existiaIndicesP2 = false;
        indicesP2 = new vector<nodo> (maxElem(p2) + 1);
        for (unsigned int i = 0; i < p2.size(); i++) {
            (*indicesP2)[p2[i]] = i;
        }
    }

    // Listo, ya arme los arreglos de indices
    // Con estos arreglos de indices voy a hacer Radix Sort
    // Primero me preparo la lista donde el Radix me va a devolver el resultado

    list<eje> listaAux;
    vector<nodo>::const_iterator itNodosP2(p2.begin());
    while (itNodosP2 != p2.end()) {
        list<nodo>::const_iterator it(ejes[*itNodosP2].begin());
        while (it != ejes[*itNodosP2].end()) {
            eje e;
            e.primero = (*indicesP1)[*it];
            e.segundo = (*indicesP2)[*itNodosP2];
            listaAux.push_back(e);
            it++;
        }
        //print(*itNodosP2);
        itNodosP2++;
    }

    if (!existiaIndicesP1) {
        delete indicesP1;
    }
    if (!existiaIndicesP2) {
        delete indicesP2;
    }
    radixSort(listaAux, p1.size(), p2.size());

    return acumTree(listaAux, p2.size());
}

// Funcion que calcula los cruces entre los ejes del nodo x y los del nodo y
// indicesP2 es un parametro opcional para no tener que recalcular los indices
// de la otra particion
unsigned int crucesEntre(nodo x, nodo y, const vector<nodo>& p2, const vector< list<nodo> >& ejes, vector<nodo>* indicesP2) {
//    print(x);
//    print(y)
//    int i = 0;
//    while(i < p2.size()){
//        cout<<"p2[i]";
//        print(p2[i]);
//        print((*indicesP2)[p2[i]]);
//        i++;
//    }
//    i = 0;
//    while(i < ejes.size()){
//        int j = 0;
//        cout<<"los ejes de "<<i<<" ";
//        while(j<ejes[i].size()){
//            cout<<ejes[i][j]<<" ";
//            j++;
//        }
//        cout<<endl;
//        i++;
//    }
//    i=0;
    if(p2.size() < 2){
        return 0;
    }
    if ((ejes[x].size() * ejes[y].size() < p2.size()) && indicesP2 != NULL) {
        unsigned int cruces = 0;
        list<nodo>::const_iterator itAdyacentesX(ejes[x].begin());
        while (itAdyacentesX != ejes[x].end()) {
            //cout<<*itAdyacentesX<<endl;
            list<nodo>::const_iterator itAdyacentesY(ejes[y].begin());
            while (itAdyacentesY != ejes[y].end()) {
                //cout<<*itAdyacentesY<<endl;
                if ((*indicesP2)[*itAdyacentesX] > (*indicesP2)[*itAdyacentesY]) {
                    cruces += 1;
                }
                itAdyacentesY++;
            }
            itAdyacentesX++;
        }
        //cout<<"aaaa"<<endl;
        return cruces;
    }
    else {
        bool existiaIndicesP2 = true;
        list<eje> listaAux;
        if (indicesP2 == NULL) {
            existiaIndicesP2 = false;
            indicesP2 = new vector<nodo> (maxElem(p2) + 1);
            for (unsigned int i = 0; i < p2.size(); i++) {
                (*indicesP2)[p2[i]] = i;
            }
        }
        // Me preparo la lista de ejes para hacer Radix Sort

        list<nodo>::const_iterator it (ejes[x].begin());
        while(it != ejes[x].end()) {
            eje e;
            e.primero = (*indicesP2)[*it];
            e.segundo = 0;
            listaAux.push_back(e);
            it++;
        }

        it = (ejes[y].begin());
        while(it != ejes[y].end()) {
            eje e;
            e.primero = (*indicesP2)[*it];
            e.segundo = 1;
            listaAux.push_back(e);
            it++;
        }

        radixSort(listaAux, p2.size(), 2);

        return acumTree(listaAux, 2);
    }
}

// Esta funcion calcula los cruces que genera agregar un elemento
// adelante o atras de la particion p1. Si x es NULL, se asume que el elemento
// a contabilizar ya fue agregado en p1 (en su posicion correspondiente: adelante o atras)
// en caso contrario se agrega el elemento x a p1.
unsigned int crucesPorAgregarEnLosBordes(bool agregoAdelante, const vector<nodo>& p1, const vector<nodo>& p2, const vector< list<nodo> > ejes, nodo* x, vector<nodo>* indicesP2) {
    if(p2.size() < 2 || p1.empty() || (p1.size() == 1 && x == NULL) ){
        return 0;
    }
    nodo candidato;
    if (x == NULL) {
        if (agregoAdelante) {
            candidato = p1[0];
        }
        else {
            candidato = p1[p1.size() - 1];
        }
    }
    else {
        candidato = *x;
    }

    list<eje> listaAux;
    bool existiaIndicesP2 = true;
    if (indicesP2 == NULL) {
        existiaIndicesP2 = false;
        indicesP2 = new vector<nodo> (maxElem(p2) + 1);
        for (unsigned int i = 0; i < p2.size(); i++) {
            (*indicesP2)[p2[i]] = i;
        }
    }
    // Me preparo la lista de ejes para hacer RadixSort
    vector<nodo>::const_iterator itNodosP1(p1.begin());
    while (itNodosP1 != p1.end()) {
        list<nodo>::const_iterator itEjes(ejes[*itNodosP1].begin());
        while (itEjes != ejes[*itNodosP1].end()) {
            eje e;
            e.primero = (*indicesP2)[*itEjes];
            if (*itNodosP1 == candidato) {
                e.segundo = BETA(!agregoAdelante);
            }
            else {
                e.segundo = BETA(agregoAdelante);
            }
            listaAux.push_back(e);
            itEjes++;
        }
        itNodosP1++;
    }
    // Hago una iteracion mas si existia x
    if (x != NULL) {
        list<nodo>::const_iterator itEjes(ejes[*x].begin());
        while (itEjes != ejes[*x].end()) {
            eje e;
            e.primero = (*indicesP2)[*itEjes];
            e.segundo = BETA(!agregoAdelante);;
            listaAux.push_back(e);
            itEjes++;
        }
    }

    radixSort(listaAux, p2.size(), 2);

    return acumTree(listaAux, 2);
}

unsigned int crucesPorAgregarAdelante(const vector<nodo>& p1, const vector<nodo>& p2, const vector< list<nodo> > ejes, nodo* x, vector<nodo>* indicesP2) {
    return crucesPorAgregarEnLosBordes(true, p1, p2, ejes, x, indicesP2);
}

unsigned int crucesPorAgregarAtras(const vector<nodo>& p1, const vector<nodo>& p2, const vector< list<nodo> > ejes, nodo* x, vector<nodo>* indicesP2) {
    return crucesPorAgregarEnLosBordes(false, p1, p2, ejes, x, indicesP2);
}

