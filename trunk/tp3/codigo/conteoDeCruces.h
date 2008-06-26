#ifndef _conteo_De_Cruces_H
#define _conteo_De_Cruces_H

#include <math.h>

#include "GrafoBipartito.h"

// ACLARACION: indicesPi[k] da la posicion del nodo k en la particion Pi
// Funcion que calcula los cruces entre todos los nodos
unsigned int contadorDeCruces (const vector<nodo>& p1,
                               const vector<nodo>& p2,
                               const vector< list<nodo> >& ejes,
                               const vector<nodo>& indicesP1,
                               const vector<nodo>& indicesP2);
unsigned int contadorDeCruces (const list<nodo>& p1,
                               const list<nodo>& p2,
                               const vector< list<nodo> >& ejes,
                               const vector<nodo>& indicesP1,
                               const vector<nodo>& indicesP2);

// Funcion que calcula los cruces entre los ejes del nodo 'x' y los del nodo 'y'
unsigned int crucesEntre(nodo x,
                         nodo y,
                         const vector<nodo>& p2,
                         const vector< list<nodo> >& ejes,
                         const vector<nodo>& indicesP2);
unsigned int crucesEntre(nodo x,
                         nodo y,
                         const list<nodo>& p2,
                         const vector< list<nodo> >& ejes,
                         const vector<nodo>& indicesP2);

// Funcion que calcula los cruces que genera agregar un elemento adelante
// o atras de la particion p1 (parametro)
unsigned int crucesPorAgregarEnLosBordes(bool agregoAdelante,
        const vector<nodo>& p1,
        const vector<nodo>& p2,
        const vector< list<nodo> >& ejes,
        const vector<nodo>& indicesP2);
unsigned int crucesPorAgregarEnLosBordes(bool agregoAdelante,
        const list<nodo>& p1,
        const list<nodo>& p2,
        const vector< list<nodo> >& ejes,
        const vector<nodo>& indicesP2);

// Funcion que calcula los cruces que genera agregar un elemento adelante de
// la particion p1 (parametro)
unsigned int crucesPorAgregarAdelante(const vector<nodo>& p1,
                                      const vector<nodo>& p2,
                                      const vector< list<nodo> >& ejes,
                                      const vector<nodo>& indicesP2);
unsigned int crucesPorAgregarAdelante(const list<nodo>& p1,
                                      const list<nodo>& p2,
                                      const vector< list<nodo> >& ejes,
                                      const vector<nodo>& indicesP2);

// Funcion que calcula los cruces que genera agregar un elemento atras de la
// particion p1 (parametro)
unsigned int crucesPorAgregarAtras(const vector<nodo>& p1,
                                   const vector<nodo>& p2,
                                   const vector< list<nodo> >& ejes,
                                   const vector<nodo>& indicesP2);
unsigned int crucesPorAgregarAtras(const list<nodo>& p1,
                                   const list<nodo>& p2,
                                   const vector< list<nodo> >& ejes,
                                   const vector<nodo>& indicesP2);

// Funciones auxiliares
nodo maxElem(const vector<nodo>& p);
void radixSort(list<eje>& listaEjes, unsigned int size1, unsigned int size2);
unsigned int acumTree (const list<eje>& l, unsigned int cantHojas);
void armarIndices(const vector<nodo>& nodos, vector<unsigned int>& indicesPi, unsigned int tamanio);

#endif
