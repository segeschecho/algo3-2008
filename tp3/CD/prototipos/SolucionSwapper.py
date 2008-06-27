#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys

#import psyco
#psyco.full()

from GrafoBipartito import Dibujo, ResolvedorConstructivo

class ResolvedorSwapper(ResolvedorConstructivo):
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

        # estos son los buffers que usa el algoritmo recursivo
        # (todas las llamadas operan sobre los mismos para evitar copias)
        self.fijo1 = d.l1[:]
        self.fijo2 = d.l2[:]
        self.movil1 = q1
        self.movil2 = q2

        self._mejor()

        print "Listo! (cruces: %s)" % self.mejorDibujo.contarCruces()
        return self.mejorDibujo

    def _mejor(self):
        # valores misc
        fijo1 = self.fijo1
        fijo2 = self.fijo2
        movil1 = self.movil1
        movil2 = self.movil2
        nf1 = len(fijo1)
        nf2 = len(fijo2)
     

        if movil1 == [] and movil2 == []:
            d = Dibujo(self.dibujo.g, fijo1, fijo2)
            if d.contarCruces() < self.mejorDibujo.contarCruces():
                # creo un dibujo (copiando las listas!), y guardo la cantidad
                # de cruces que ya calculé en la guarda del if (evito repetir el calculo)
                self.mejorDibujo = Dibujo(self.dibujo.g, fijo1[:], fijo2[:])
                self.mejorDibujo.cruces = d.contarCruces()

        elif movil1 == []:
            cab = movil2.pop(0)
            fijo2.append(cab)

            for i in range(-1, nf2):
                if i != -1:                
                    # swap 
                    a = nf2-i
                    fijo2[a], fijo2[a-1] = fijo2[a-1], fijo2[a]
                
                self._mejor()
            
            movil2.append(fijo2.pop(0))

        else:
            cab = movil1.pop(0)
            fijo1.append(cab)

            for i in range(-1, nf1):
                if i != -1:
                    # swap
                    a = nf1-i
                    fijo1[a], fijo1[a-1] = fijo1[a-1], fijo1[a]

                self._mejor()
            
            movil1.append(fijo1.pop(0))

def test_resolvedorSwapper():

    from GeneradorGrafos import generarGrafoBipartitoAleatorio, generarDibujoAleatorio
    from SolucionFuerzaBruta import ResolvedorFuerzaBruta

    g = generarGrafoBipartitoAleatorio(n1=7, n2=7, m=15)
    d = generarDibujoAleatorio(g, n1=5, n2=5)

    r1 = ResolvedorFuerzaBruta(d)
    s1 = r1.resolver()
    r2 = ResolvedorSwapper(d)
    s2 = r2.resolver()

    assert s1.contarCruces() == s2.contarCruces()
    
if __name__ == '__main__':
    test_resolvedorSwapper()
