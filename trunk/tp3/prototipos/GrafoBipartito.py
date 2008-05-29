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
        assert len(p1.intersection(p2)) == 0, "Error: la particion no es valida."

        # bipartito
        for a,b in ejes:
            try:
                assert (a in p1 and b in p2) or (a in p2 and b in p1)
            except AssertionError:
                raise AssertionError, "Error: el eje %s no cruza de p1 a p2." % (a,b)


    def estaRel(self, a, b):
        return ((a,b) in self.ejes) or \
               ((b,a) in self.ejes)

class Dibujo:
    def __init__(self, g, l1, l2):
        self.g = g
        self.l1 = l1
        self.l2 = l2

        # chequeos misc
        # tipos
        assert isinstance(g, GrafoBipartito), "Error: g debe ser un objeto GrafoBipartito (es %s)" % type(g)
        
        # dibujo valido
        try:
            assert Set(l1).issubset(g.p1)
            assert Set(l2).issubset(g.p2)
        except AssertionError:
            raise AssertionError, "Error: el dibujo propuesto no es valido para este grafo."


class ResolvedorConstructivo:
    def __init__(self, dib):
        self.dibujo = dib

    def resolver(self):
        raise NotImplementedError
