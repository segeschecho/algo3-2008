#!/usr/bin/python
# -*- coding: iso-8859-1 -*-

from grafo import Grafo

from sets import Set
import os
import random

def ordenar(t):
    if t[0] < t[1]:
        return t
    else:
        return (t[1],t[0])

def generarInstancia(ciudades=10, acuerdos=None):
    if acuerdos is None:
        acuerdos = random.randint(1, ciudades**2/2)
    
    acs = Set()
    cds = range(ciudades)
    for i in xrange(acuerdos):
        acs.add(ordenar(tuple(random.sample(cds,2))))

    return Grafo(ciudades, list(acs))

def generarInstanciaConSolucion(ciudades=10, acuerdos=None):
    if acuerdos is None:
        acuerdos = random.randint(ciudades, ciudades**2/2)

    acs = Set()
    cds = range(ciudades)
    
    # agrego una solucion trivial
    for i in xrange(ciudades-1):
        acs.add((i, i+1))

    for i in xrange(acuerdos-ciudades+1):
        acs.add(ordenar(tuple(random.sample(cds,2))))

    return Grafo(ciudades, list(acs))

def generarInstanciaSinSolucion(ciudades=10, acuerdos=None):
    if acuerdos is None:
        acuerdos = random.randint(1, ciudades**2/2)

    acs = Set()
    cds = range(ciudades)

    # saco una ciudad al azar, asi el grafo no queda conexo
    # y fuerzo que no haya ninguna solucion valida
    random.shuffle(cds)
    cds.pop()
    cds.sort()
    
    for i in xrange(acuerdos):
        acs.add(ordenar(tuple(random.sample(cds,2))))

    return Grafo(ciudades, list(acs))


def imprimirInstancia(g):
    print "%s %s" % (g.n, g.m)
    for each in g.lista_acuerdos:
        print "%s %s" % (each[0] + 1, each[1] + 1)
    print "0 0"



if __name__ == '__main__':
   
    # Ejemplos de uso
    g1 = generarInstancia(ciudades=20, acuerdos=100)
    imprimirInstancia(g1)
    
    g2 = generarInstanciaConSolucion(ciudades=20, acuerdos=100)
    g3 = generarInstanciaSinSolucion(ciudades=20, acuerdos=100)
