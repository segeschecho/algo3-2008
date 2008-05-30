#!/usr/bin/python
# -*- coding: utf-8 -*-

from sets import Set

import svg
from GrafoBipartito import GrafoBipartito, Dibujo

class DibujadorGrafoBipartito:
    def __init__(self, dibujo, nombre="GrafoBipartito", height=600):
        self.dibujo = dibujo

        # calculo las dimensiones
        self.alto_nodos = max(len(dibujo.l1), len(dibujo.l2))
        self.alto = height
        
        # radio del nodo
        self.rn = int(self.alto * 0.90 * 0.5 / self.alto_nodos)

        self.ancho = int(height/1.3)

        self.scene = svg.Scene(nombre, height=height, width=self.ancho)
        self._dibujar()

    def _dibujar(self):
        l1 = self.dibujo.l1
        l2 = self.dibujo.l2

        c1 = 0.2 * self.ancho
        c2 = 0.8 * self.ancho
        m_sup = 0.13 * self.alto
        colorCirculo = (200,255,200)

        # filtro los ejes que me interesan
        ejes = []
        for a,b in self.dibujo.g.ejes:
            if ((a in l1 and b in l2) or (b in l1 and a in l2)):
                if a in l2:
                    a,b = b,a
                ejes.append((a,b))
        
        # dibujo los ejes
        for a,b in ejes:           
            self.scene.add(svg.Line((c1, m_sup + l1.index(a) * 2 * self.rn),
                                    (c2, m_sup + l2.index(b) * 2 * self.rn)))
        
        # dibujo los nodos
        for a,b in ejes:
            centro = (c1, m_sup + l1.index(a) * 2 * self.rn)
            self.scene.add(svg.Circle(centro,self.rn / 2,colorCirculo))
            centro = (centro[0] - self.rn / 7, centro[1] + self.rn / 6)
            self.scene.add(svg.Text(centro, a))
            centro = (c2, m_sup + l2.index(b) * 2 * self.rn)
            self.scene.add(svg.Circle(centro,self.rn / 2,colorCirculo))
            centro = (centro[0] - self.rn / 7, centro[1] + self.rn / 6)
            self.scene.add(svg.Text(centro, b))

    def grabar(self):
        self.scene.write_svg()

    def grabarYMostrar(self):
        self.scene.write_svg()
        self.scene.display(prog="display")


def test():
    g = GrafoBipartito(Set([1,2,3,4]),
                       Set([5,6,7,8,9]),
                       Set([(4,6),(4,5),(3,5),(3,7),(2,6),(1,7),(3,8),(2,9),(4,8)]))
    d = Dibujo(g,[1,2,3,4],[5,6,7,8,9])
    dib = DibujadorGrafoBipartito(d)
    dib.grabarYMostrar()

if __name__ == '__main__':
    test()
