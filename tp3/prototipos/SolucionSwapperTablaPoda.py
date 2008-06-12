#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys

#import psyco
#psyco.full()

from GrafoBipartito import Dibujo, ResolvedorConstructivo
from GrafoBipartito import crucesEntre, crucesPorAgregarAdelante, crucesPorAgregarAtras
from SolucionFuerzaBruta import cuantasCombinaciones


class ResolvedorSwapperTablaConPoda(ResolvedorConstructivo):

    ###########################################################
    # Funcion global de resolución exacta                     #
    ###########################################################
    
    def resolver(self):
        g = self.dibujo.g
        d = self.dibujo

        self._inicializar()

        # cargo un candidato inicial
        self.mejorDibujo = Dibujo(g, d.l1 + self.q1, d.l2 + self.q2)
        
        # busco el mejor candidato
        print "Explorando conjunto de soluciones... ",
        sys.stdout.flush()
        self.podas = 0

        self._mejor()
        
        combinaciones = cuantasCombinaciones(self.fijo1, self.fijo2, self.movil1, self.movil2)
        porcent_podas = self.podas * 100.0 / combinaciones
        print "Listo! (cruces: %s, podas: %.1f%%)" % \
            (self.mejorDibujo.contarCruces(), porcent_podas)

        return self.mejorDibujo


    ###########################################################
    # Función auxiliar de inicialización                      #
    ###########################################################
    
    def _inicializar(self):
        g = self.dibujo.g
        d = self.dibujo

        # armo las listas de adyacencia del grafo completo
        ady = {}
        for n in g.p1:
            ady[n] = []
        for n in g.p2:
            ady[n] = []
        for a,b in g.ejes:
            ady[a].append(b)
            ady[b].append(a)        
        self.ady = ady

        # busco los nodos que quedan por posicionar
        self.q1 = [x for x in g.p1 if not x in self.dibujo.l1]
        self.q2 = [x for x in g.p2 if not x in self.dibujo.l2]

        # elijo cual de las 2 mitades tiene menos permutaciones
        # para llenarla primero en el arbol de combinaciones
        # (esto puede mejorar el rendimiento del algoritmo)
        combs1 = cuantasCombinaciones(len(d.l1),0,len(self.q1),0)
        combs2 = cuantasCombinaciones(len(d.l2),0,len(self.q2),0)
        if combs1 > combs2:
            invertirLados = True
        else:
            invertirLados = False
        self.invertirLados = invertirLados

        # estos son los buffers que usa el algoritmo recursivo
        # (todas las llamadas operan sobre los mismos para evitar copias)
        if invertirLados:
            self.fijo1 = d.l2[:]
            self.fijo2 = d.l1[:]
            self.movil1 = self.q2
            self.movil2 = self.q1
            self.l1 = list(g.p2)
            self.l2 = list(g.p1)
        else:
            self.fijo1 = d.l1[:]
            self.fijo2 = d.l2[:]
            self.movil1 = self.q1
            self.movil2 = self.q2
            self.l1 = list(g.p1)
            self.l2 = list(g.p2)
 
        # armo las listas de adyacencia de p1 con los de d.l1
        # (esto me permite calcular de forma eficiente los cruces
        # de una cierta permutacion de p1)
        adyp1 = {}      
        
        if invertirLados:
            p1 = g.p2
        else:
            p1 = g.p1

        for n in p1:
            adyp1[n] = []
        for a,b in g.ejes:
            if a in adyp1 and b in self.fijo2:
                adyp1[a].append(b)
            elif b in adyp1 and a in self.fijo2:
                adyp1[b].append(a)
        
        self.adyp1 = adyp1
        
        # cache de posiciones para evitar busquedas
        self.posiciones1 = {}
        for i in range(len(self.fijo1)):
            self.posiciones1[self.fijo1[i]] = i 
        self.posiciones2 = {}
        for i in range(len(self.fijo2)):
            self.posiciones2[self.fijo2[i]] = i 
        
        # Cache de cruces para reutilizar calculos
        # tablaN[(i,j)] es la cantidad de cruces que hay entre
        # los nodos i,j si son contiguos en el candidato actual de pN
        self._tabular1()
        if self.movil1 == []:
            self._tabular2()

        # cargo los cruces del dibujo original
        self.cruces = d.contarCruces()

    def _tabular1(self):
        # Inicializa la tabla de valores precalculados para p1 (vs. fijo2)
        # FIXME: hay calculos innecesarios
        self.tabla1 = {}
        for i in self.l1:
            for j in self.l1:
                if i < j:
                    c = crucesEntre(i, j, self.fijo2, 
                                    self.adyp1,indice2=self.posiciones2)
                    self.tabla1[(i,j)] = c
                    c = crucesEntre(j, i, self.fijo2, 
                                    self.adyp1,indice2=self.posiciones2)
                    self.tabla1[(j,i)] = c

    def _tabular2(self):
        # Reinicia la tabla de valores precalculados para p2 cuando cambia p1
        # FIXME: hay calculos innecesarios
        self.tabla2 = {}
        for i in self.l2:
            for j in self.l2:
                if i < j:
                    c = crucesEntre(i,j, self.fijo1, 
                                    self.ady,indice2=self.posiciones1)
                    self.tabla2[(i,j)] = c
                    c = crucesEntre(j,i, self.fijo1, 
                                    self.ady,indice2=self.posiciones1)
                    self.tabla2[(j,i)] = c

    def _minimosCrucesRestantes(self):
        c = 0
        for i in self.movil2:
            for j in self.movil2:
                if i < j:
                    c += min(self.tabla2[(i,j)], self.tabla2[(j,i)])

            for j in self.fijo2:
                c += min(self.tabla2[(i,j)], self.tabla2[(j,i)])

        return c
                    
                


    ###########################################################
    # Funciones auxiliares para modificacion de candidatos    #
    ###########################################################
    
    # mueve movil1[0] a fijo1[n]
    def _agregarAtras1(self):
        cab = self.movil1.pop(0)
        self.fijo1.append(cab)
        self.posiciones1[cab] = len(self.fijo1) - 1
        self.cruces += crucesPorAgregarAtras(self.fijo1, 
                                             self.dibujo.l2,
                                             self.adyp1,
                                             indice2=self.posiciones2)
    
    # analogo para p1
    def _agregarAtras2(self):
        cab = self.movil2.pop(0)
        self.fijo2.append(cab)
        self.cruces += crucesPorAgregarAtras(self.fijo2,
                                             self.fijo1,
                                             self.ady,
                                             indice2=self.posiciones1)

    # mueve fijo1[0] a movil1[n]
    def _sacarPrincipio1(self):
        self.cruces -= crucesPorAgregarAdelante(self.fijo1,
                                                self.dibujo.l2,
                                                self.adyp1,
                                                indice2=self.posiciones2)

        self.movil1.append(self.fijo1.pop(0))
        # FIXME: esta operacion se puede ahorrar con un
        # offset entero que se resta a todas las posiciones
        for i in range(len(self.fijo1)):
            self.posiciones1[self.fijo1[i]] = i

    # analogo para p2
    def _sacarPrincipio2(self):
        self.cruces -= crucesPorAgregarAdelante(self.fijo2,
                                                self.fijo1,
                                                self.ady,
                                                indice2=self.posiciones1)
        self.movil2.append(self.fijo2.pop(0))

    # swapea fijo1[i] con fijo1[i-1]
    def _retrasar1(self, i):
        fijo1 = self.fijo1
        a = len(fijo1) - 1 - i
        
        cAntes = self.tabla1[(fijo1[a-1],fijo1[a])]
        
        # swapeo y actualizo
        fijo1[a], fijo1[a-1] = fijo1[a-1], fijo1[a]
        self.posiciones1[fijo1[a]] = a
        self.posiciones1[fijo1[a-1]] = a-1
        
        # actualizo la cuenta de cruces
        cDespues = self.tabla1[(fijo1[a-1],fijo1[a])]
        self.cruces = self.cruces - cAntes + cDespues

    
    # analogo para p2
    def _retrasar2(self, i):
        fijo2 = self.fijo2
        a = len(fijo2) - 1 - i

        cAntes = self.tabla2[(fijo2[a-1],fijo2[a])]

        # swapeo (no hay nada que actualizar)
        fijo2[a], fijo2[a-1] = fijo2[a-1], fijo2[a]

        # actualizo la cuenta de cruces
        cDespues = self.tabla2[(fijo2[a-1],fijo2[a])]
        self.cruces = self.cruces - cAntes + cDespues


    ###########################################################
    # Funcion auxiliar de busqueda del mejor candidato        #
    ###########################################################

    def _mejor(self):
        # valores misc
        fijo1 = self.fijo1
        fijo2 = self.fijo2
        movil1 = self.movil1
        movil2 = self.movil2
        nf1 = len(fijo1)
        nf2 = len(fijo2)
        
        # esto corresponde al caso base, donde chequeo si obtuve una
        # solución mejor a la previamente máxima, y de ser así la 
        # actualizo con el nuevo valor
        if movil1 == [] and movil2 == []:
            
            if self.cruces < self.mejorDibujo.contarCruces():
                # creo un dibujo (copiando las listas!), y guardo la cantidad
                # de cruces que ya tengo calculada en el atributo cruces (para
                # evitar que se recalcule)
                if self.invertirLados:
                    self.mejorDibujo = Dibujo(self.dibujo.g, fijo2[:], fijo1[:])
                else:
                    self.mejorDibujo = Dibujo(self.dibujo.g, fijo1[:], fijo2[:])
                
                self.mejorDibujo.cruces = self.cruces

        # entro en este caso cuando ya complete una permutacion
        # de fijo1, y ahora tengo que elegir la mejor permutacion
        # para la particion 2
        elif movil1 == []:
            self._agregarAtras2()

            for i in range(-1, nf2):
                if i != -1:
                    self._retrasar2(i)

                if self._minimosCrucesRestantes() + self.cruces < self.mejorDibujo.contarCruces():
                    self._mejor()
                else:
                    self.podas += cuantasCombinaciones(fijo1, fijo2, movil1, movil2) - 1
            
            self._sacarPrincipio2()

        # entro en este caso cuando lleno la permutacion de fijo1 
        # (siempre se hace esto antes de verificar la otra particion, 
        # ya que elegimos fijo1 para que tenga menos permutaciones)
        else:
            self._agregarAtras1()

            for i in range(-1, nf1):
                if i != -1:
                    self._retrasar1(i)
                if movil1 == []:
                    self._tabular2()
                self._mejor()
            
            self._sacarPrincipio1()


def test_resolvedorSwapperTablaConPoda():

    from GeneradorGrafos import generarGrafoBipartitoAleatorio, generarDibujoAleatorio
    from SolucionFuerzaBruta import ResolvedorFuerzaBruta

    g = generarGrafoBipartitoAleatorio(n1=7, n2=7, m=15)
    d = generarDibujoAleatorio(g, n1=5, n2=5)

    r1 = ResolvedorFuerzaBruta(d)
    s1 = r1.resolver()
    r2 = ResolvedorSwapperTablaConPoda(d)
    s2 = r2.resolver()

    assert s1.contarCruces() == s2.contarCruces()
    
if __name__ == '__main__':
    test_resolvedorSwapperTablaConPoda()
