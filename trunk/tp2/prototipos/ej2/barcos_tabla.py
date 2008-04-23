#!/usr/bin/python
# -*- coding: iso-8859-1 -*-

from grafocircular import GrafoCircular

#################################################################
# Versión con tabulado por demanda                              #
#################################################################

class BuscadorCaminoTPD:
    def __init__(self, grafo):
        self.g = grafo
        self.camino = None
        
        # preparo las tablas
        self.matA = []
        self.matB = []
        for i in range(grafo.n):
            self.matA.append([None] * grafo.n)
            self.matB.append([None] * grafo.n)

    def caminoQueTerminaEnA(self,a,b):
        if self.matA[a][b] != None:
            return self.matA[a][b]

        # caso base
        if b-a == 1 or (b == 0 and a == self.g.n-1):
            if self.g.estanConectados(a,b):
                self.matA[a][b] = [b,a]
                return [b,a]
            else:
                self.matA[a][b] = []
                return []
    
        # caso recursivo
        c = self.caminoQueTerminaEnA((a+1) % self.g.n, b)
        if c != [] and self.g.estanConectados(a, (a+1) % self.g.n):
            self.matA[a][b] = c + [a]
            return c + [a]
        c = self.caminoQueTerminaEnB((a+1) % self.g.n, b)
        if c != [] and self.g.estanConectados(a,b):
            self.matA[a][b] = c + [a]
            return c + [a]

        self.matA[a][b] = []
        return []

    def caminoQueTerminaEnB(self,a,b):
        if self.matB[a][b] != None:
            return self.matB[a][b]
    
        # caso base
        if b-a == 1 or (b == 0 and a == self.g.n-1):
            if self.g.estanConectados(a,b):
                self.matB[a][b] = [a,b]
                return [a,b]
            else:
                self.matB[a][b] = []
                return []

        # caso recursivo
        c = self.caminoQueTerminaEnA(a, (b-1) % self.g.n)
        if c != [] and self.g.estanConectados(a,b):
            self.matB[a][b] = c + [b]
            return c + [b]
        c = self.caminoQueTerminaEnB(a, (b-1) % self.g.n)
        if c != [] and self.g.estanConectados((b-1) % self.g.n, b):
            self.matB[a][b] = c + [b]
            return c + [b]

        self.matB[a][b] = []
        return []


    def buscarCamino(self):
        if self.camino != None:
            return self.camino

        for i in range(self.g.n):
            a = i
            b = (i-1) % self.g.n

            c = self.caminoQueTerminaEnA(a,b)
            if c != []:
                self.camino = c
                return c

            c = self.caminoQueTerminaEnB(a,b)
            if c != []:
                self.camino = c
                return c

        self.camino = []
        return []


#################################################################
# Versión con tabulado completo al inicio                       #
#################################################################

class BuscadorCaminoTCI:
    def __init__(self):
        pass

    def caminoQueTerminaEnA(self,a,b):
        pass

    def caminoQueTerminaEnB(self,a,b):
        pass

    def buscarCamino(self,):
        pass
