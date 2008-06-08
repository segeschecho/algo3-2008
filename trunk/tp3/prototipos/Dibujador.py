#!/usr/bin/python
# -*- coding: utf-8 -*-

from sets import Set

import svg
from GrafoBipartito import GrafoBipartito, Dibujo

class DibujadorGrafoBipartito:
    def __init__(self, dibujo, nombre="GrafoBipartito", height=800,marcados1=None,marcados2=None):
        self.dibujo = dibujo

        # calculo las dimensiones
        self.alto_nodos = max(len(dibujo.l1), len(dibujo.l2))
        self.alto = height
        
        # radio del nodo
        self.rn = int(self.alto * 0.90 * 0.5 / self.alto_nodos)

        self.ancho = int(height/1.3)

        self.scene = svg.Scene(nombre, height=height, width=self.ancho)
        if marcados1 == None:
            self._dibujar()
        else:
            self._dibujarConMarcados(marcados1,marcados2)

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
        for n in l1:
            centro = (c1, m_sup + l1.index(n) * 2 * self.rn)
            self.scene.add(svg.Circle(centro,self.rn / 2,colorCirculo))
            centro = (centro[0] - self.rn / 7, centro[1] + self.rn / 6)
            self.scene.add(svg.Text(centro, n))
        for n in l2:
            centro = (c2, m_sup + l2.index(n) * 2 * self.rn)
            self.scene.add(svg.Circle(centro,self.rn / 2,colorCirculo))
            centro = (centro[0] - self.rn / 7, centro[1] + self.rn / 6)
            self.scene.add(svg.Text(centro, n))
    
    def _dibujarConMarcados(self,marcados1,marcados2):
        l1 = self.dibujo.l1
        l2 = self.dibujo.l2

        c1 = 0.2 * self.ancho
        c2 = 0.8 * self.ancho
        m_sup = 0.13 * self.alto
        colorCirculo = (200,255,200)
        colorCirculoMarcado = (255,200,200)

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
        for n in l1:
            if n in marcados1:
                centro = (c1, m_sup + l1.index(n) * 2 * self.rn)
                self.scene.add(svg.Circle(centro,self.rn / 2,colorCirculoMarcado))
                centro = (centro[0] - self.rn / 7, centro[1] + self.rn / 6)
                self.scene.add(svg.Text(centro, n))
            else:
                centro = (c1, m_sup + l1.index(n) * 2 * self.rn)
                self.scene.add(svg.Circle(centro,self.rn / 2,colorCirculo))
                centro = (centro[0] - self.rn / 7, centro[1] + self.rn / 6)
                self.scene.add(svg.Text(centro, n))
        for n in l2:
            if n in marcados2:
                centro = (c2, m_sup + l2.index(n) * 2 * self.rn)
                self.scene.add(svg.Circle(centro,self.rn / 2,colorCirculoMarcado))
                centro = (centro[0] - self.rn / 7, centro[1] + self.rn / 6)
                self.scene.add(svg.Text(centro, n))
            else:
                centro = (c2, m_sup + l2.index(n) * 2 * self.rn)
                self.scene.add(svg.Circle(centro,self.rn / 2,colorCirculo))
                centro = (centro[0] - self.rn / 7, centro[1] + self.rn / 6)
                self.scene.add(svg.Text(centro, n))
    
    def grabar(self, filename=None):
        self.scene.write_svg(filename=filename)

    def grabarYMostrar(self):
        self.scene.write_svg()
        self.scene.display(prog="display")


def test_Dibujador():
    g = GrafoBipartito(Set([1,2,3,4]),
                       Set([5,6,7,8,9]),
                       Set([(4,6),(4,5),(3,5),(3,7),(2,6),(1,7),(3,8),(2,9),(4,8)]))
    d = Dibujo(g,[1,2,3,4],[5,6,7,8,9])
    dib = DibujadorGrafoBipartito(d)
    dib.grabarYMostrar()
    dib.grabar('test.svg')

if __name__ == '__main__':
    test_Dibujador()
