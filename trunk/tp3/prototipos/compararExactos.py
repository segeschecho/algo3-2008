#!/usr/bin/python
# -*- coding: utf-8 -*-

#import psyco
#psyco.full()

from time import time

from GrafoBipartito import Dibujo, ResolvedorConstructivo
from GeneradorGrafos import generarGrafoBipartitoAleatorio, generarDibujoAleatorio

from SolucionFuerzaBruta import ResolvedorFuerzaBruta, cuantasCombinaciones
from SolucionBasica import ResolvedorBasico
from SolucionBasicaPoda import ResolvedorBasicoConPoda
from SolucionSwapper import ResolvedorSwapper
from SolucionSwapperPoda import ResolvedorSwapperConPoda
from SolucionSwapperTabla import ResolvedorSwapperTabla
from SolucionSwapperTablaPoda import ResolvedorSwapperTablaConPoda

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
    n1 = 8
    n2 = 8
    d1 = 5
    d2 = 5
    f1 = n1 - d1
    f2 = n2 - d2
    m = n1*n2/2
    print "Resolviendo un caso de prueba... (%E combinaciones)" % cuantasCombinaciones(f1,d1,f2,d2)
    print

    t = Timer()
    g = generarGrafoBipartitoAleatorio(n1=n1, n2=n2, m=m)
    d = generarDibujoAleatorio(g, n1=d1, n2=d2)

    sols = ResolvedorFuerzaBruta, \
           ResolvedorBasico, \
           ResolvedorBasicoConPoda, \
           ResolvedorSwapper, \
           ResolvedorSwapperConPoda, \
           ResolvedorSwapperTabla,  \
           ResolvedorSwapperTablaConPoda

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
