#!/usr/bin/python
# -*- coding: utf-8 -*-

from time import time

from GrafoBipartito import Dibujo, ResolvedorConstructivo
from GeneradorGrafos import generarGrafoBipartitoAleatorio, generarDibujoAleatorio

from SolucionFuerzaBruta import ResolvedorFuerzaBruta
from SolucionBasica import ResolvedorBasico
from SolucionBasicaPoda import ResolvedorBasicoConPoda

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
    g = generarGrafoBipartitoAleatorio(n1=8, n2=7, m=15)
    d = generarDibujoAleatorio(g, n1=5, n2=5)

    r1 = ResolvedorFuerzaBruta(d)
    print "Fuerza Bruta:"
    t.empezar()
    s1 = r1.resolver()
    t.terminar()
    assert s1.esIncrementalDe(d)
    print

    r2 = ResolvedorBasico(d)
    print "Básico:"
    t.empezar()
    s2 = r2.resolver()
    t.terminar()
    assert s2.esIncrementalDe(d)
    print

    r3 = ResolvedorBasicoConPoda(d)
    print "Básico con poda:"
    t.empezar()
    s3 = r3.resolver()
    t.terminar()
    assert s3.esIncrementalDe(d)
    print

    assert s3.contarCruces() == s2.contarCruces() == s1.contarCruces()

if __name__ == '__main__':
    comparar()
