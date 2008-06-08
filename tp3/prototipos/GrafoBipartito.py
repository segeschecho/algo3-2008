#!/usr/bin/python
# -*- coding: utf-8 -*-

from sets import Set


###########################################
# Clase GrafoBipartito                    #
###########################################

class GrafoBipartito:
    def __init__(self, p1, p2, ejes):
        self.ejes = ejes
        self.p1 = p1
        self.p2 = p2

        self.n = len(p1) + len(p2)
        self.m = len(ejes)

        # chequeos misc
        # tipos
        try:
            assert isinstance(p1, Set)
            assert isinstance(p2, Set)
            assert isinstance(ejes, Set)
        except AssertionError:
            raise AssertionError, "Error: p1, p2 y ejes deben ser conjuntos."
        
        # particion valida
        assert len(p1) > 0, "Error: p1 no puede ser vacío."
        assert len(p2) > 0, "Error: p2 no puede ser vacío."
        assert len(p1.intersection(p2)) == 0, "Error: la particion no es valida."

        # bipartito
        for a,b in ejes:
            try:
                assert (a in p1 and b in p2) or (a in p2 and b in p1)
            except AssertionError:
                raise AssertionError, "Error: el eje (%s,%s) no cruza de p1 a p2." % (a,b)



    def estaRel(self, a, b):
        return ((a,b) in self.ejes) or \
               ((b,a) in self.ejes)

    def __eq__(self, otro):
        return self.ejes == otro.ejes and \
               self.p1 == otro.p1 and \
               self.p2 == otro.p2

    def __ne__(self, otro):
        return not (self == otro)

    def __repr__(self):
        return "<GrafoBipartito #p1=%s #p2=%s m=%s>" % (len(p1),len(p2),m)

    def __str__(self):
        buf = []
        buf.append("------------------------")
        buf.append("GrafoBipartito")
        buf.append("------------------------")
        buf.append("P1 = %s" % list(self.p1))
        buf.append("P2 = %s" % list(self.p2))
        buf.append("Ejes = %s" % list(self.ejes))
        buf.append("------------------------")
        return '\n'.join(buf)



###########################################
# Clase Dibujo                            #
###########################################

class Dibujo:
    def __init__(self, g, l1, l2):
        self.g = g
        self.l1 = l1
        self.l2 = l2
        self.cruces = None

        # chequeos misc
        # tipos
        assert isinstance(g, GrafoBipartito), "Error: g debe ser un objeto GrafoBipartito (es %s)" % type(g)
        
        # dibujo valido
        try:
            s1 = Set(l1)
            s2 = Set(l2)
            
            # no hay repetidos
            assert len(s1) == len(l1)
            assert len(s2) == len(l2)
            
            # estan incluidos en la particion del grafo
            assert s1.issubset(g.p1)
            assert s2.issubset(g.p2)

        except AssertionError:
            raise AssertionError, "Error: el dibujo propuesto no es valido para este grafo."

    def esIncrementalDe(self,d):
        if self.g != d.g:
            return False

        l1c = [x for x in self.l1 if x in d.l1]
        if l1c != d.l1:
            return False
        
        l2c = [x for x in self.l2 if x in d.l2]
        if l2c != d.l2:
            return False
        
        return True


    def contarCruces(self):
        if not self.cruces is None:
            return self.cruces
        
        self.cruces = self._contarCruces()
        return self.cruces

    def _contarCruces(self):

        # Armo las listas de adyacencia del grafo
        ady = {}
        for n in self.g.p1:
            ady[n] = []
        for n in self.g.p2:
            ady[n] = []
        for a,b in self.g.ejes:
            ady[a].append(b)
            ady[b].append(a)        
        
        # Para contar los ejes hago el siguiente algoritmo:
        # Supongo que tengo ya dispuestos los nodos de l2, y voy
        # agregando de 1 a len(l1) los nodos que estan en l1.

        # Para cada uno de ellos, agrego sus ejes uno por uno,
        # contando la cantidad de cruces que se crean al agregarlos
        # e incrementando asi el valor del contador cruces. 
        cruces = 0

        # Esta variable auxiliar almacena la cantidad
        # de ejes (ya elegidos) que inciden en la lista l2
        # desde el indice i en adelante.
        ejesDesde = [0 for x in self.l2]

        # Buffer para los ejes que agrego con este nodo
        # (no los puedo poner directamente en ejesDesde porque
        # estoy asumiendo que no estan al hacer la cuenta de cruces)
        ejesDesdeTmp = [0 for x in self.l2]

        # Precalculo en un diccionario las posiciones de los
        # elementos de l2 en la lista l2 (para evitar buscarlos 
        # siempre cuando necesite saber su posicion)
        pos = {}
        for each in range(len(self.l2)):
            pos[self.l2[each]] = each

        for n in self.l1:
            for e in ady[n]:
                # tomo la posicion del nodo adyacente en l2
                try:
                    p = pos[e]
                except KeyError:
                    continue
                
                # calculo los cruces que crea este eje
                # (el calculo no tiene sentido en caso de que p
                # sea la ultima posicion de l2, pero en este caso
                # tampoco agrego cruces ya que no puede haberlos)
                if p  != len(self.l2)-1:
                    cruces += ejesDesde[p+1]

                # incremento ejesDesdeLoc desde 0 hasta p
                for i in range(p+1):
                    ejesDesdeTmp[i] += 1

            # agrego los ejes agregados con el ultimo nodo y reseteo
            for i in range(len(self.l2)):
                ejesDesde[i] += ejesDesdeTmp[i]
                ejesDesdeTmp[i] = 0
        
        return cruces
 
    
    def __eq__(self, otro):
        return self.l1 == otro.l1 and \
               self.l2 == otro.l2 and \
               self.g == otro.g

    def __ne__(self, otro):
        return not (self == otro)

    def __repr__(self):
        return "<Dibujo de GrafoBipartito (#l1=%s, #l2=%s)>" % (len(self.l1),len(self.l2))

    def __str__(self):
        buf = []
        buf.append("------------------------")
        buf.append("Dibujo de GrafoBipartito")
        buf.append("------------------------")
        buf.append("L1: %s" % self.l1)
        buf.append("L2: %s" % self.l2)
        buf.append("Cruces: %s" % self.contarCruces())
        buf.append("------------------------")
        return '\n'.join(buf)

###########################################
# Funciones para el conteo de cruces      #
###########################################
#utiliza un acum tree para contar los cruces entre los nodos de
#la lista p1 y la lista p2, tomando las listas de adyacencia losEjes
#indice1 e indice 2 son parametros opcionales, si se conocen los indices de los
#elementos se puede apurar el calculo no re armando los indices cada vez
def contadorDeCruces(p1,p2,losEjes,indice1 = None, indice2 = None):
	
        if len(p1) < len(p2):
            return contadorDeCruces(p2,p1,losEjes,indice2,indice1)
        lista=[]
        if indice1 == None:
            indice1={}
            for i in range(len(p1)):
                indice1[p1[i]]=i
        if indice2 == None:
            indice2={}
            for i in range(len(p2)):
                indice2[p2[i]]=i
        #radixsort de los ejes
        for each in p2:
            for each2 in losEjes[each]:
                lista.append((indice1[each2],indice2[each]))
        b1=[[] for each in range(len(p2))]
        b2=[[] for each in range(len(p1))]
        for each in lista:
            b1[each[1]].append(each)
        lista2=[]
        for i in range(len(b1)):
            lista2.extend(b1[i])
        for each in lista2:
            b2[each[0]].append(each)
        lista2=[]
        for i in range(len(b2)):
            lista2.extend(b2[i])
        sur=[]
        for each in lista2:
            sur.append(each[1])
        primerIndice=1
        while primerIndice < len(p2):
            primerIndice *= 2
        arbol = [0]*(2*primerIndice - 1)
        primerIndice -=1
        cruces=0
        for i in range(len(sur)):
            indice=sur[i]+primerIndice
            arbol[indice]+=1

            while(indice > 0):
                if (indice % 2 == 1):
                    cruces += arbol[indice+1]
                indice=(indice -1)/2
                arbol[indice]+=1
        return cruces
###########################################
# Clases base para resolvedores           #
###########################################

class ResolvedorConstructivo:
    def __init__(self, dib):
        self.dibujo = dib

    def resolver(self):
        raise NotImplementedError


class ResolvedorMejora:
    def __init__(self, dib):
        self.dibujo = dib

    def resolver(self, dibujoCandidato):
        raise NotImplementedError

class Grasp:
 
    def resolver(dib):
        raise NotImplementedError

###########################################
# Tests                                   #
###########################################

def test_contarCruces():
    g = GrafoBipartito(Set([1,2,3]),
                       Set([4,5,6]),
                       Set([(1,4),(2,5),(2,6),(1,5),(3,4),(3,5),(1,6)]))
    d = Dibujo(g, [1,2,3],[4,5,6])
    assert d.contarCruces() == 7

    g = GrafoBipartito(Set([1,2,3,4]),
                       Set([5,6,7,8,9]),
                       Set([(4,6),(4,5),(3,5),(3,7),(2,6),(1,7),(3,8),(2,9),(4,8)]))
    d = Dibujo(g,[1,2,3,4],[5,6,7,8,9])
    assert d.contarCruces() == 16

    g = GrafoBipartito(Set([1,3]),
                       Set([2,4]),
                       Set([(3,2)]))
    d = Dibujo(g,[1,3],[2,4])
    assert d.contarCruces() == 0


def test_esIncrementalDe():
    g = GrafoBipartito(Set([1,2,3]),
                       Set([4,5,6]),
                       Set([(1,4),(2,5),(2,6),(1,5),(3,4),(3,5),(1,6)]))
    d1 = Dibujo(g,[1,3],[4,5])
    d2 = Dibujo(g,[1,2,3],[4,5,6])
    d3 = Dibujo(g,[3,1],[4,5])
    d4 = Dibujo(g,[1],[4,5])
    assert d2.esIncrementalDe(d1)
    assert not d3.esIncrementalDe(d1)
    assert not d4.esIncrementalDe(d1)


if __name__ == '__main__':
    test_contarCruces()
    test_esIncrementalDe()
