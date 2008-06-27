#!/usr/bin/python
# -*- coding: utf-8 -*-

from GrafoBipartito import ResolvedorConstructivo, Dibujo
from GrafoBipartito import crucesEntre, crucesPorAgregarAtras
from GeneradorGrafos import generarGrafoBipartitoAleatorio, generarDibujoAleatorio

import random

class HeuristicaInsercionNodos(ResolvedorConstructivo):

    ###########################################################
    # Funcion global de aplicación de la heurística           #
    ###########################################################

    def resolver(self, alfa=1, randomPos=False):
        assert 0 < alfa <= 1
        self.alfa = alfa

        self.randomPos = randomPos

        self._inicializar()

        # Ejecuto la heuristica constructiva greedy
        while self.movil1 != [] or self.movil2 != []:
            if self.movil1 != []:
                sig = self._tomarSiguiente1()
                self._insertarEn1(sig)
            if self.movil2 != []:
                sig = self._tomarSiguiente2()
                self._insertarEn2(sig)

        d = Dibujo(self.dibujo.g, self.fijo1, self.fijo2)
        assert self.cruces == d.contarCruces()
        return d



    ###########################################################
    # Función auxiliar de inicialización                      #
    ###########################################################

    def _inicializar(self):
        d = self.dibujo
        g = self.dibujo.g
        
        self.fijo1 = d.l1[:]
        self.fijo2 = d.l2[:]
        # FIXME: esto es O(n^2) y se puede mejorar en la version definitiva
        self.movil1 = [x for x in g.p1 if not x in d.l1]
        self.movil2 = [x for x in g.p2 if not x in d.l2]
        
        # Guardo en un diccionario quien es movil y quien no
        # (este diccionario se ira modificando a medida que voy "fijando" nodos)
        self.esMovil = {}
        for each in self.fijo1:
            self.esMovil[each] = False
        for each in self.fijo2:
            self.esMovil[each] = False
        for each in self.movil1:
            self.esMovil[each] = True
        for each in self.movil2:
            self.esMovil[each] = True

        esMovil = self.esMovil
        
        # Construyo 3 diccionarios que voy a necesitar:
        self.ady = {}           # listas de adyacencia del grafo completo
        self.adyParcial = {}    # listas de adyacencia del subgrafo ya fijado
        self.gradoParcial = {}  # grados de los nodos (moviles) contando solo los ejes 
                                # que van a los nodos ya fijados

        for each in g.p1:
            self.ady[each] = []
            self.gradoParcial[each] = 0
            if not esMovil[each]:
                self.adyParcial[each] = []

        for each in g.p2:
            self.ady[each] = []
            self.gradoParcial[each] = 0
            if not esMovil[each]:
                self.adyParcial[each] = []

        for a,b in g.ejes:
            self.ady[a].append(b)
            self.ady[b].append(a)

            if not esMovil[a] and not esMovil[b]:
                self.adyParcial[a].append(b)
                self.adyParcial[b].append(a)

            if not esMovil[a] or not esMovil[b]:
                self.gradoParcial[a] += 1
                self.gradoParcial[b] += 1
        
        # Almaceno para los nodos fijos su posicion en la particion
        # que les corresponde - esto permite agilizar los conteos de cruces.
        self.posiciones = {}
        for i in range(len(self.fijo1)):
            self.posiciones[self.fijo1[i]] = i
        for i in range(len(self.fijo2)):
            self.posiciones[self.fijo2[i]] = i


        # Guardo los cruces del dibujo fijo como punto de partida
        # para ir incrementando sobre este valor a medida que agrego nodos.
        self.cruces = d.contarCruces()



    ###########################################################
    # Funciones auxiliares de selección de nodos              #
    ###########################################################

    def _tomarSiguiente(self, moviles):
        # Ordeno los moviles por grado
        self._ordenarPorGradoParcial(moviles)
        maximoGrado = self.gradoParcial[moviles[0]]
        alfaMaximoGrado = maximoGrado * self.alfa
        
        # Elijo al azar alguno de los que superan el grado alfa-maximo
        ultimoQueSupera = 0
        while ultimoQueSupera + 1 < len(moviles) and \
              self.gradoParcial[moviles[ultimoQueSupera + 1]] >= alfaMaximoGrado:
            ultimoQueSupera += 1

        elegido = random.randint(0,ultimoQueSupera)
        e = moviles.pop(elegido)
        del self.gradoParcial[e]
        return e

    def _tomarSiguiente1(self):
        return self._tomarSiguiente(self.movil1)

    def _tomarSiguiente2(self):
        return self._tomarSiguiente(self.movil2)
    
    def _ordenarPorGradoParcial(self, moviles):
        # FIXME: ordena por grado en orden decreciente, implementado con alto orden :P
        moviles.sort(lambda x,y: -cmp(self.gradoParcial[x], self.gradoParcial[y]))



    ###########################################################
    # Funciones auxiliares de inserción de nodos              #
    ###########################################################

    def _insertar(self, nodo, fijos, otrosFijos):
        
        self.esMovil[nodo] = False

        # Actualizo la lista de adyacencias parcial para incorporar las adyacencias
        # del nodo que voy a agregar - esto es necesario puesto que las funciones de conteo
        # de cruces se usan dentro del subgrafo fijo y por tanto para que tengan en cuenta
        # al nodo a agregar, es necesario completarlas con sus ejes.
        self.adyParcial[nodo] = []
        for vecino in self.ady[nodo]:
            if not self.esMovil[vecino]:
                self.adyParcial[vecino].append(nodo)
                self.adyParcial[nodo].append(vecino)

        # Busco las mejores posiciones en la particion para insertar este nodo, comenzando
        # por el final y swapeando hacia atrás hasta obtener las mejores.
        fijos.append(nodo)
        cruces = self.cruces + crucesPorAgregarAtras(fijos, otrosFijos, self.adyParcial, indice2=self.posiciones)
        pos = len(fijos) - 1
        
        mejorCruces = cruces
        posValidas = [pos]
        
        while pos > 0:
            pos = pos - 1
            cruces = (cruces - 
                      crucesEntre(fijos[pos], fijos[pos+1], otrosFijos, self.adyParcial, indice2=self.posiciones) +
                      crucesEntre(fijos[pos+1], fijos[pos], otrosFijos, self.adyParcial, indice2=self.posiciones))
            fijos[pos], fijos[pos+1] = fijos[pos+1], fijos[pos]

            if cruces == mejorCruces:
                posValidas.append(pos)
                
            if cruces < mejorCruces:
                mejorCruces = cruces
                posValidas = [pos]

        
        # Inserto el nodo en alguna de las mejores posiciones
        if self.randomPos:
            mejorPos = random.choice(posValidas)
        else:
            mejorPos = posValidas[0]
            
        fijos.pop(0)
        fijos.insert(mejorPos, nodo)
        self.cruces = mejorCruces

        # Actualizo los grados parciales
        for a in self.ady[nodo]:
            if self.esMovil[a]:
                self.gradoParcial[a] += 1
        
        # Actualizo las posiciones 
        for i in range(len(fijos)):
            self.posiciones[fijos[i]] = i


    def _insertarEn1(self, nodo):
        return self._insertar(nodo, self.fijo1, self.fijo2)

    def _insertarEn2(self, nodo):
        return self._insertar(nodo, self.fijo2, self.fijo1)



def test_HeuristicaInsercionNodos():
    g = generarGrafoBipartitoAleatorio(n1=25,n2=25,m=500)
    d = generarDibujoAleatorio(g,n1=5,n2=5)
    h = HeuristicaInsercionNodos(d)
    s = h.resolver(alfa=1)
    print s
    s2 = h.resolver(alfa=1,randomPos=True)
    print s2
    s3 = h.resolver(alfa=0.6)
    print s3
    s4 = h.resolver(alfa=0.6, randomPos=True)
    print s4


if __name__ == '__main__':
    test_HeuristicaInsercionNodos()
