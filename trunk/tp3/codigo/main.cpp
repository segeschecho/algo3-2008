#include <iostream>
#include "Dibujo.h"
#include "GrafoBipartito.h"
#include <math.h>

using namespace std;

void radixSort(list<eje>& listaEjes, unsigned int p1Size, unsigned int p2Size) {
    // bucket1 y bucket2 son los buckets donde voy a guardar los ejes
    list<eje>* bucket1 = new list<eje> [p1Size];
    list<eje>* bucket2 = new list<eje> [p2Size];

    //ordeno por segunda componente
    list<eje>::const_iterator it (listaEjes.begin());
    while (it != listaEjes.end()) {
        bucket2[it->segundo].push_back(*it);
        it++;
    }

    listaEjes.clear();
    for(unsigned int i = 0; i < p2Size; i++) {
        listaEjes.splice(listaEjes.end(), bucket2[i]);
    }

    //ordeno por primera componente
    it = listaEjes.begin();
    while (it != listaEjes.end()) {
        bucket1[it->primero].push_back(*it);
        it++;
    }

    listaEjes.clear();
    for(unsigned int i = 0; i < p1Size; i++) {
        listaEjes.splice(listaEjes.end(), bucket1[i]);
    }
}

unsigned int acumTree (const list<eje>& l, unsigned int cantHojas) {
    // Ahora que tengo las segundas componentes, puedo aplicar el metodo del arbol acumulador
    // para finalmente contar los cruces
    vector<nodo> segComp (l.size());

    list<eje>::const_iterator it2(l.begin());
    for(unsigned int i = 0; i < l.size(); i++) {
        segComp[i] = it2->segundo;
        it2++;
    }

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
    for(unsigned int i = 0; i < segComp.size(); i++) {
        // Indice es la hoja a la que pertenece el eje
        unsigned int indice = segComp[i] + primerIndice;
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
    }
    delete arbol;
    return cruces;
}

nodo maxElem(const vector<nodo>& p) {
    nodo maximo = p[0];
    for(unsigned int i = 1; i < p.size(); i++) {
        if (maximo < p[i]) {
            maximo = p[i];
        }
    }
    return maximo;
}

unsigned int contadorDeCruces (const vector<nodo>& p1, const vector<nodo>& p2, const vector< vector<nodo> >& ejes, vector<nodo>* indicesP1 = NULL, vector<nodo>* indicesP2 = NULL) {
	// Quiero tener a la de menor tamaño como segundo parametro para lograr O(m*log(min(p1,p2))
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
        vector<nodo>::const_iterator it(ejes[*itNodosP2].begin());
        while (it != ejes[*itNodosP2].end()) {
            eje e;
            e.primero = (*indicesP1)[*it];
            e.segundo = (*indicesP2)[*itNodosP2];
            listaAux.push_back(e);
            it++;
        }
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
unsigned int crucesEntre(nodo x, nodo y, const vector<nodo>& p2, const vector< vector<nodo> >& ejes, vector<nodo>* indicesP2 = NULL) {
    if ((ejes[x].size() * ejes[y].size() < p2.size()) && indicesP2 != NULL) {
        unsigned int cruces = 0;
        vector<nodo>::const_iterator itAdyacentesX(ejes[x].begin());
        while (itAdyacentesX != ejes[x].end()) {
            vector<nodo>::const_iterator itAdyacentesY(ejes[y].begin());
            while (itAdyacentesY != ejes[y].end()) {
                if (indicesP2[*itAdyacentesX] > indicesP2[*itAdyacentesY]) {
                    cruces += 1;
                }
                itAdyacentesY++;
            }
            itAdyacentesX++;
        }
        return cruces;
    }
    else {
        bool existiaIndicesP2 = true;
        list<eje> listaAux;
        if (indicesP2 == NULL) {
            existiaIndicesP2 = false;
            indicesP2 = new vector<nodo>;
            for (unsigned int i = 0; i < p2.size(); i++) {
                (*indicesP2)[p2[i]] = i;
            }
        }
        // Me preparo la lista de ejes para hacer Radix Sort

        vector<nodo>::const_iterator it (ejes[x].begin());
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

        radixSort(listaAux, 2, p2.size());

        return acumTree(listaAux, 2);
    }
}

// Esta funcion calcula los cruces que genera agregar un elemento
// adelante o atras de la particion p1. Si x es NULL, se asume que el elemento
// a contabilizar ya fue agregado en p1 (en su posicion correspondiente: adelante o atras)
// en caso contrario se agrega el elemento x a p1.
unsigned int crucesPorAgregarEnLosBordes(bool agregoAdelante, const vector<nodo>& p1, const vector<nodo>& p2, const vector< vector<nodo> > ejes, nodo* x = NULL, vector<nodo>* indicesP2 = NULL) {
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
        indicesP2 = new vector<nodo>;
        for (unsigned int i = 0; i < p2.size(); i++) {
            (*indicesP2)[p2[i]] = i;
        }
    }
    // Me preparo la lista de ejes para hacer RadixSort
    vector<nodo>::const_iterator itNodosP1(p1.begin());
    while (itNodosP1 != p1.end()) {
        vector<nodo>::const_iterator itEjes(ejes[*itNodosP1].begin());
        while (itEjes != ejes[*itNodosP1].end()) {
            eje e;
            e.primero = (*indicesP2)[*itEjes];
            if (*itNodosP1 == candidato) {
                e.segundo = 0;
                listaAux.push_back(e);
            }
            else {
                e.segundo = 1;
                listaAux.push_back(e);
            }
            itEjes++;
        }
        itNodosP1++;
    }
    // Hago una iteracion mas si existia x
    if (x != NULL) {
        vector<nodo>::const_iterator itEjes(ejes[*x].begin());
        while (itEjes != ejes[*x].end()) {
            eje e;
            e.primero = (*indicesP2)[*itEjes];
            if (*x == candidato) {
                e.segundo = 0;
                listaAux.push_back(e);
            }
            else {
                e.segundo = 1;
                listaAux.push_back(e);
            }
            itEjes++;
        }
    }

    radixSort(listaAux, p1.size(), p2.size());

    return acumTree(listaAux, 2);
}

int main(int argc, char* argv[]) {
    list<eje> ejes;
    eje e1, e2, e3, e4;
    list<nodo> nodosV1, nodosV2;

    e1.primero = 0;
    e1.segundo = 2;
    e2.primero = 0;
    e2.segundo = 3;
    e3.primero = 1;
    e3.segundo = 2;
    e4.primero = 1;
    e4.segundo = 3;

    nodosV1.push_back(0);
    nodosV1.push_back(1);
    nodosV2.push_back(2);
    nodosV2.push_back(3);

    ejes.push_back(e1);
    ejes.push_back(e2);
    ejes.push_back(e3);
    ejes.push_back(e4);

    GrafoBipartito g(nodosV1, nodosV2, ejes);

    Dibujo d(&g, nodosV1, nodosV2);

    cout << contadorDeCruces(d.nodosL1, d.nodosL2, g.diccEjes) << endl;

    system("PAUSE");
    return 0;
}
