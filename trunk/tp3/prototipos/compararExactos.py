#!/usr/bin/python
# -*- coding: utf-8 -*-

#import psyco
#psyco.full()

from time import time

from GrafoBipartito import Dibujo, ResolvedorConstructivo
from GeneradorGrafos import generarGrafoBipartitoAleatorio, generarDibujoAleatorio

from SolucionFuerzaBruta import ResolvedorFuerzaBruta
from SolucionBasica import ResolvedorBasico
from SolucionBasicaPoda import ResolvedorBasicoConPoda
from SolucionSwapper import ResolvedorSwapper
from SolucionSwapperPoda import ResolvedorSwapperConPoda
from SolucionSwapperTabla import ResolvedorSwapperTabla

class Timer:
    def __init__(self):
        self.empezo = False

    def empezar(self):
        if self.empezo:
            raise Exception, "La cuenta ya estaba empezada!"

        self.comienzo = time()
        self.empezo = True

    def terminar(self):
        if not self.empezo:
            raise Exception, "La cuenta no habia empezado!"

        print "Tiempo: %.2f segundos" % (time() - self.comienzo)
        self.empezo = False

def comparar(): 
    t = Timer()
    g = generarGrafoBipartitoAleatorio(n1=8, n2=8, m=25)
    d = generarDibujoAleatorio(g, n1=5, n2=5)

    sols = ResolvedorFuerzaBruta, \
           ResolvedorBasico, \
           ResolvedorBasicoConPoda, \
           ResolvedorSwapper, \
           ResolvedorSwapperConPoda, \
           ResolvedorSwapperTabla

    cruces = []

    for s in sols:
        r = s(d)
        print "%s:" % s.__name__
        t.empezar()
        res = r.resolver()
        t.terminar()
        assert(res.esIncrementalDe(d))
        cruces.append(res.contarCruces())
        print

    for i in range(1,len(cruces)):
        assert cruces[0] == cruces[i]

if __name__ == '__main__':
    comparar()
