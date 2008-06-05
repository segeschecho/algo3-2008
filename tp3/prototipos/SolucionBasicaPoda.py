#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys

#import psyco
#psyco.full()

from GrafoBipartito import Dibujo, ResolvedorConstructivo
from SolucionFuerzaBruta import cuantasCombinaciones

class ResolvedorBasicoConPoda(ResolvedorConstructivo):
    def __init__(self, dib):
        self.dibujo = dib

    def resolver(self):
        g = self.dibujo.g
        d = self.dibujo

        # busco los nodos que quedan por posicionar
        q1 = [x for x in g.p1 if not x in self.dibujo.l1]
        q2 = [x for x in g.p2 if not x in self.dibujo.l2]
        

        # cargo un candidato inicial
        self.mejorDibujo = Dibujo(g, d.l1 + q1, d.l2 + q2)

        # busco el mejor candidato
        print "Explorando conjunto de soluciones... ",
        sys.stdout.flush()
        self.podas = 0
        self._mejor(d.l1, d.l2, q1, q2)

        combinaciones = cuantasCombinaciones(d.l1, d.l2, q1, q2)
        porcent_podas = self.podas * 100.0 / combinaciones
        print "Listo! (cruces: %s, podas: %.1f%%)" % \
            (self.mejorDibujo.contarCruces(), porcent_podas)

        return self.mejorDibujo

    def _mejor(self, fijo1, fijo2, movil1, movil2, cruces=None):
        if movil1 == [] and movil2 == []:
            if cruces < self.mejorDibujo.contarCruces():
                d = Dibujo(self.dibujo.g, fijo1, fijo2)
                self.mejorDibujo = d
            return

        # valores misc
        nf1 = len(fijo1)
        nf2 = len(fijo2)

        if movil1 == []:
            cab = movil2[0]
            cola = movil2[1:]

            for i in range(nf2+1):
                nuevo_fijo2 = fijo2[:]
                nuevo_fijo2.insert(i, cab)
                d = Dibujo(self.dibujo.g, fijo1, nuevo_fijo2)
                if d.contarCruces() < self.mejorDibujo.contarCruces():
                    self._mejor(fijo1, nuevo_fijo2, movil1, cola, cruces=d.contarCruces())
                else:
                    self.podas += cuantasCombinaciones(fijo1, nuevo_fijo2, movil1, cola) - 1
            return

        else:
            cab = movil1[0]
            cola = movil1[1:]

            for i in range(nf1+1):
                nuevo_fijo1 = fijo1[:]
                nuevo_fijo1.insert(i, cab)
                d = Dibujo(self.dibujo.g, nuevo_fijo1, fijo2)
                if d.contarCruces() < self.mejorDibujo.contarCruces():
                    self._mejor(nuevo_fijo1, fijo2, cola, movil2, cruces=d.contarCruces())
                else:
                    self.podas += cuantasCombinaciones(nuevo_fijo1, fijo2, cola, movil2) - 1
            return

def test_resolvedorBasicoConPoda():
    from GeneradorGrafos import generarGrafoBipartitoAleatorio, generarDibujoAleatorio
    from SolucionFuerzaBruta import ResolvedorFuerzaBruta

    g = generarGrafoBipartitoAleatorio(n1=7, n2=7, m=15)
    d = generarDibujoAleatorio(g, n1=5, n2=5)

    r1 = ResolvedorFuerzaBruta(d)
    s1 = r1.resolver()
    r2 = ResolvedorBasicoConPoda(d)
    s2 = r2.resolver()

    assert s1.contarCruces() == s2.contarCruces()

if __name__ == '__main__':
    test_resolvedorBasicoConPoda()
