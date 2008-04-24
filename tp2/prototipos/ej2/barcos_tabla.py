#!/usr/bin/python
# -*- coding: iso-8859-1 -*-

from grafocircular import GrafoCircular

#################################################################
# Versión con tabulado por demanda                              #
#################################################################

# Nota: Esta versión guarda en la tabla los subcaminos encontrados
#       hasta el momento, con lo cual su complejidad espacial es 
#       O(n^3), lo cual es fulero. La idea es reimplementar usando
#       matriz de bool y generar el camino recorriendo dicha matriz
#       cuando se lo requiera.

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

# Nota: esta implementacion resuelve sobre 2 matrices de bool en
#       O(n^2) y despues construye un camino cuando se le pide.

class BuscadorCaminoTCI:

    def __init__(self, grafo):
        self.g = grafo
        self.camino = None
        self.resuelto = False        
    
    # este metodo arma la matriz de bools asociada a la solucion
    # para un grafo dado (esta matriz permite despues encontrar los
    # caminos existentes)
    def _resolver(self):
        if self.resuelto:
            return

        # preparo las tablas
        self.matA = []
        self.matB = []
        for i in range(self.g.n):
            self.matA.append([False] * self.g.n)
            self.matB.append([False] * self.g.n)


        # caso base (hay camino entre nodos adyacentes?)
        for i in range(self.g.n):
            a = i
            b = (i+1) % self.g.n
            if self.g.estanConectados(a,b):
                self.matA[a][b] = True
                self.matB[a][b] = True
        
        # caso general (hay camino entre nodos separados por $i ciudades?)
        for i in range(2,self.g.n):
            for j in range(self.g.n):
                a = j
                amas1 = (a+1) % self.g.n
                b = (j+i) % self.g.n
                bmenos1 = (b-1) % self.g.n

                self.matA[a][b] = (self.matA[a][amas1] and self.matA[amas1][b]) or \
                                  (self.matA[a][b] and self.matB[amas1][b])
                self.matB[a][b] = (self.matA[b][bmenos1] and self.matB[a][bmenos1]) or \
                                  (self.matA[a][b] and self.matA[a][bmenos1])

        self.resuelto = True

    # Funcion recursiva auxiliar para construir los caminos
    # requiere que el camino exista!
    def _caminoQueTerminaEnA(self,a,b):
        if b-a == 1 or (b == 0 and a == self.g.n-1):
            return [b,a]

        amas1 = (a+1) % self.g.n
        
        if self.matA[a][amas1] and self.matA[amas1][b]:
            return self._caminoQueTerminaEnA(amas1,b) + [a]
        if self.matA[a][b] and self.matB[amas1][b]:
            return self._caminoQueTerminaEnB(amas1,b) + [a]

        raise ValueError, "No existe el camino que se intento generar! (de %s a %s)" % (a,b)

    # Funcion recursiva auxiliar para construir los caminos
    # requiere que el camino exista!
    def _caminoQueTerminaEnB(self,a,b):
        if b-a == 1 or (b == 0 and a == self.g.n-1):
            return [a,b]

        bmenos1 = (b-1) % self.g.n

        if self.matA[b][bmenos1] and self.matB[a][bmenos1]:
            return self._caminoQueTerminaEnB(a,bmenos1) + [b]
        if self.matA[a][b] and self.matA[a][bmenos1]:
            return self._caminoQueTerminaEnA(a,bmenos1) + [b]

        raise ValueError, "No existe el camino que se intento generar! (de %s a %s)" % (a,b)

    # Devuelve el camino hallado o [] si no fue posible hallar uno.
    def buscarCamino(self):

        if not self.resuelto:
            self._resolver()

        # me fijo si hay algun camino posible, si lo encuentro
        # lo construyo y devuelvo, sino devuelvo []
        for i in range(self.g.n):
            a = i
            b = (i-1) % self.g.n
            
            if self.matA[a][b]:
                return self._caminoQueTerminaEnA(a,b)
            if self.matB[a][b]:
                return self._caminoQueTerminaEnB(a,b)

        return []
