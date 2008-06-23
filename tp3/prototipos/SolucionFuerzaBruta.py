#!/usr/bin/python
# -*- coding: utf-8 -*-

from GrafoBipartito import Dibujo, ResolvedorConstructivo

import sys

#import psyco
#psyco.full()

class ResolvedorFuerzaBruta(ResolvedorConstructivo):
    def resolver(self):
        # busco los nodos que quedan por posicionar
        q1 = [x for x in self.dibujo.g.p1 if not x in self.dibujo.l1]
        q2 = [x for x in self.dibujo.g.p2 if not x in self.dibujo.l2]
        

        # genero todos los posibles dibujos
        print "Generando soluciones posibles...     ",
        sys.stdout.flush()
        combs = combinaciones(self.dibujo.l1, self.dibujo.l2, q1, q2)
        print "Listo! (total: %s)" % len(combs) 


        # elijo el mejor
        print "Eligiendo solución óptima...         ",
        sys.stdout.flush()
        l1, l2 = combs.pop()
        mejor = Dibujo(self.dibujo.g, l1, l2)
        cruces = mejor.contarCruces()

        for c in combs:
            d = Dibujo(self.dibujo.g, c[0], c[1])
            if d.contarCruces() < cruces:
                mejor = d
                cruces = d.contarCruces()
        print "Listo! (cruces: %s)" % cruces

        return mejor


def combinaciones(fijo1, fijo2, movil1, movil2):
    '''Construye todos los dibujos incrementales sobre fijo1, fijo2'''
    if movil1 == [] and movil2 == []:
        return [(fijo1, fijo2)]

    # algunos valores misc
    nf1 = len(fijo1)
    nf2 = len(fijo2)

    # posiciono los moviles 2
    if movil1 == []:
        cab = movil2[0]
        cola = movil2[1:]

        ops = []
        for i in range(nf2+1):
            nuevo_fijo2 = fijo2[:]
            nuevo_fijo2.insert(i, cab)
            ops += combinaciones(fijo1, nuevo_fijo2, movil1, cola)
        return ops

    # posiciono los moviles 1
    else:
        cab = movil1[0]
        cola = movil1[1:]

        ops = []
        for i in range(nf1+1):
            nuevo_fijo1 = fijo1[:]
            nuevo_fijo1.insert(i, cab)
            ops += combinaciones(nuevo_fijo1, fijo2, cola, movil2)
        return ops


def cuantasCombinaciones(fijo1, fijo2, movil1, movil2):
    '''Calcula el cardinal del universo de soluciones posibles de esta instancia'''
    if isinstance(fijo1, list) and \
       isinstance(fijo2, list) and \
       isinstance(movil1, list) and \
       isinstance(movil2, list):
        f1, f2, m1, m2 = map(len, [fijo1, fijo2, movil1, movil2])
    else:
        f1, f2, m1, m2 = fijo1, fijo2, movil1, movil2
    
    c = 1
    for i in range(m1):
        c *= f1 + i + 1 
    for i in range(m2):
        c *= f2 + i + 1
    return c


def tamTree(fijo1, fijo2, movil1, movil2):
    if isinstance(fijo1, list) and \
       isinstance(fijo2, list) and \
       isinstance(movil1, list) and \
       isinstance(movil2, list):
        f1, f2, m1, m2 = map(len, [fijo1, fijo2, movil1, movil2])
    else:
        f1, f2, m1, m2 = fijo1, fijo2, movil1, movil2

    if m1 == 0 and m2 == 0:
        return 1
    elif m2 != 0:
        return (f2+1)*tamTree(f1, f2+1, m1, m2-1) + 1
    elif m1 != 0:
        return (f1+1)*tamTree(f1+1, f2, m1-1, m2) + 1

def tamArbol(fijo1,fijo2,movil1,movil2):

    arbol1 = tamTree(fijo1,[],movil1,[])
    arbol2 = tamTree([],fijo2,[],movil2)
    return arbol1 + cuantasCombinaciones(fijo1, [], movil1, [])*(arbol2 -1)

def test_resolvedorFuerzaBruta():
    from GeneradorGrafos import generarGrafoBipartitoAleatorio, generarDibujoAleatorio

    g = generarGrafoBipartitoAleatorio(n1=8, n2=8, m=15)
    d = generarDibujoAleatorio(g,n1=5, n2=5)

    r = ResolvedorFuerzaBruta(d)
    s = r.resolver()

if __name__ == '__main__':
    test_resolvedorFuerzaBruta()
