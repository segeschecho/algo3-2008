#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
from HeuristicaInsercionEjes import *
#import psyco
#psyco.full()

from GrafoBipartito import Dibujo, ResolvedorConstructivo
from SolucionFuerzaBruta import cuantasCombinaciones

class ResolvedorSwapperConPoda(ResolvedorConstructivo):
    def resolver(self):
        g = self.dibujo.g
        d = self.dibujo

        # busco los nodos que quedan por posicionar
        q1 = [x for x in g.p1 if not x in self.dibujo.l1]
        q2 = [x for x in g.p2 if not x in self.dibujo.l2]

        # cargo un candidato inicial
        self.mejorDibujo = HeuristicaInsercionEjes(d).resolver()#Dibujo(g, d.l1 + q1, d.l2 + q2)
        
        # busco el mejor candidato
        print "Explorando conjunto de soluciones... ",
        sys.stdout.flush()
        self.podas = 0

        # estos son los buffers que usa el algoritmo recursivo
        # (todas las llamadas operan sobre los mismos para evitar copias)
        self.fijo1 = d.l1[:]
        self.fijo2 = d.l2[:]
        self.movil1 = q1
        self.movil2 = q2

        self._mejor()

        combinaciones = cuantasCombinaciones(d.l1, d.l2, q1, q2)
        porcent_podas = self.podas * 100.0 / combinaciones
        print "Listo! (cruces: %s, podas: %.1f%%)" % \
            (self.mejorDibujo.contarCruces(), porcent_podas)
        
        return self.mejorDibujo

    def _mejor(self, cruces=None):
        # valores misc
        fijo1 = self.fijo1
        fijo2 = self.fijo2
        movil1 = self.movil1
        movil2 = self.movil2
        nf1 = len(fijo1)
        nf2 = len(fijo2)
     

        if movil1 == [] and movil2 == []:
            if cruces < self.mejorDibujo.contarCruces():
                # creo un dibujo (copiando las listas!), y guardo la cantidad
                # de cruces que ya calculé en la guarda del if (evito repetir el calculo)
                self.mejorDibujo = Dibujo(self.dibujo.g, fijo1[:], fijo2[:])
                self.mejorDibujo.cruces = cruces

        elif movil1 == []:
            cab = movil2.pop(0)
            fijo2.append(cab)

            for i in range(-1, nf2):
                if i != -1:                
                    # swap 
                    a = nf2-i
                    fijo2[a], fijo2[a-1] = fijo2[a-1], fijo2[a]
                
                d = Dibujo(self.dibujo.g, fijo1, fijo2)
                if d.contarCruces() < self.mejorDibujo.contarCruces():
                    self._mejor(cruces=d.contarCruces())
                else:
                    self.podas += cuantasCombinaciones(fijo1, fijo2, movil1, movil2) - 1
            
            movil2.append(fijo2.pop(0))

        else:
            cab = movil1.pop(0)
            fijo1.append(cab)

            for i in range(-1, nf1):
                if i != -1:
                    # swap
                    a = nf1-i
                    fijo1[a], fijo1[a-1] = fijo1[a-1], fijo1[a]

                d = Dibujo(self.dibujo.g, fijo1, fijo2)
                if d.contarCruces() < self.mejorDibujo.contarCruces():
                    self._mejor(cruces=d.contarCruces())
                else:
                    self.podas += cuantasCombinaciones(fijo1, fijo2, movil1, movil2) - 1
            
            movil1.append(fijo1.pop(0))

def test_resolvedorSwapperConPoda():

    from GeneradorGrafos import generarGrafoBipartitoAleatorio, generarDibujoAleatorio
    from SolucionFuerzaBruta import ResolvedorFuerzaBruta

    g = generarGrafoBipartitoAleatorio(n1=8, n2=8, m=64)
    d = generarDibujoAleatorio(g, n1=2, n2=2)

    #r1 = ResolvedorFuerzaBruta(d)
    #s1 = r1.resolver()
    r2 = ResolvedorSwapperConPoda(d)
    s2 = r2.resolver()

    #assert s1.contarCruces() == s2.contarCruces()
    
if __name__ == '__main__':
    test_resolvedorSwapperConPoda()
