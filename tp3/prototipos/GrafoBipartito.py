#!/usr/bin/python
# -*- coding: utf-8 -*-

from sets import Set

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

        l1c = [x for x in self.l1 if not x in d.l1]
        if l1c != d.l1:
            return False

        l2c = [x for x in self.l2 if not x in d.l2]
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

        for n in self.l1:
            # buffer para los ejes que agrego con este nodo
            # (no los puedo poner directamente en ejesDesde porque
            # estoy asumiendo que no estan al hacer la cuenta de cruces)
            ejesDesdeTmp = [0 for x in self.l2]
            
            for e in ady[n]:
                # busco la posicion del nodo adyacente
                # en la segunda mitad del dibujo
                p = self.l2.index(e)
                
                # calculo los cruces que crea este eje
                if p  != len(self.l2)-1:
                    cruces += ejesDesde[p+1]

                # incremento ejesDesdeLoc desde 0 hasta p
                for i in range(p+1):
                    ejesDesdeTmp[i] += 1

            # agrego los ejes agregados con el ultimo nodo
            for i in range(len(self.l2)):
                ejesDesde[i] += ejesDesdeTmp[i]
        
        return cruces
 
    def __eq__(self, otro):
        return self.l1 == otro.l1 and \
               self.l2 == otro.l2 and \
               self.g1 == otro.g1

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


class ResolvedorConstructivo:
    def __init__(self, dib):
        self.dibujo = dib

    def resolver(self):
        raise NotImplementedError


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


if __name__ == '__main__':
    test_contarCruces()
