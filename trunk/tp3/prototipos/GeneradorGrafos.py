#!/usr/bin/python
# -*- coding: utf-8 -*-

from GrafoBipartito import GrafoBipartito, Dibujo

from sets import Set
import random

def generarGrafoBipartitoAleatorio(n1=10,n2=10,m=25):
    p1 = range(n1)
    p2 = range(n1,n1+n2)
    maxEjes = n1 * n2
    if m > n1 * n2:
        raise ValueError, "Error: K_(%s,%s) tiene %s ejes (se pidieron %s)." % (n1, n2, n1*n2, m)
    
    # FIXME: esto es un poco ineficiente
    # se pueden generar pares al azar e ir insertandolos
    # hasta que el conjunto tiene el cardinal deseado
    ejesPosibles = [(a,b) for a in p1 for b in p2]
    ejes = random.sample(ejesPosibles,m)

    return GrafoBipartito(Set(p1),Set(p2),Set(ejes))

def generarDibujoAleatorio(g, n1=5, n2=5):
    assert n1 <= len(g.p1)
    assert n2 <= len(g.p2)

    p1 = list(g.p1)
    p2 = list(g.p2)
    l1 = random.sample(p1, n1)
    l2 = random.sample(p2, n2)

    return Dibujo(g, l1, l2)

g = generarGrafoBipartitoAleatorio()
d = generarDibujoAleatorio(g)
print g
print d
