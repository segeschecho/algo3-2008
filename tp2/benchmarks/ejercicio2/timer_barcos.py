#!/usr/bin/python
# -*- coding: iso-8859-1 -*-

from grafocircular import GrafoCircular

from sets import Set
import os
import random

import psyco
psyco.full()


infile = 'generador_test.in'
outfile = 'generador_test.out'

# dado un grafo, mide el tiempo que le insume al resolvedor
# en C++ computar su solucion en milisegundos.
def medirTiempo(grafo):
    def limpiar():
        try:
            os.remove(outfile)
        except:
            pass
        try:
            os.remove(infile)
        except:
            pass

    limpiar()
    f = open(infile,'w')
    f.write('%s %s\n' % (grafo.n, grafo.m))
    for each in grafo.lista_acuerdos:
        f.write('%s %s\n' % (each[0]+1, each[1]+1))
    f.write('0 0\n')
    f.close()
    c = os.popen('./barcos %s %s' % (infile, outfile))
    t = c.read()
    return int(t)


def ordenar(t):
    if t[0] < t[1]:
        return t
    else:
        return (t[1],t[0])

def generarInstancia(ciudades=10, acuerdos=None):
    if acuerdos is None:
        acuerdos = random.randint(1, ciudades**2)
    
    acs = Set()
    cds = range(ciudades)
    for i in range(acuerdos):
        acs.add(ordenar(tuple(random.sample(cds,2))))

    return GrafoCircular(ciudades, list(acs))

def imprimirInstancia(ciudades=10, acuerdos=None):
    g = generarInstancia(ciudades, acuerdos)
    print "%s %s" % (g.n, g.m)
    for each in g.lista_acuerdos:
        print "%s %s" % each

if __name__ == '__main__':

    # genera los datos para el grafico en funcion de N
    max_n = 1000

    print "Generando datos para el grafico en funcion de N..."
    print
    fn = open('datos_n.m','w')
    fn.write('m = [')
    for i in xrange(10, max_n):
        print "%s/%s" % (i, max_n)
        fn.write('%s %s;' % (i, medirTiempo(generarInstancia(ciudades=i))))
    fn.write('];')
    fn.close()
    print

    # genera los datos para el grafico en funcion de M
    max_m = 10000
    print "Generando datos para el grafico en funcion de M (N constante)..."
    print
    fm = open('datos_m.m','w')
    fm.write('m = [')
    for i in xrange(10, max_m):
        print "%s/%s" % (i, max_m)
        fm.write('%s %s;' % (i, medirTiempo(generarInstancia(ciudades=200, acuerdos=i))))
    fm.write('];')
    fm.close()
    print


