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
        acuerdos = random.randint(1, ciudades**2/2)
    
    acs = Set()
    cds = range(ciudades)
    for i in xrange(acuerdos):
        acs.add(ordenar(tuple(random.sample(cds,2))))

    return GrafoCircular(ciudades, list(acs))

def generarInstanciaConSolucion(ciudades=10, acuerdos=None):
    if acuerdos is None:
        acuerdos = random.randint(ciudades, ciudades**2/2)

    acs = Set()
    cds = range(ciudades)
    
    # agrego una solucion trivial
    for i in xrange(ciudades-1):
        acs.add((i, i+1))

    for i in xrange(acuerdos-ciudades+1):
        acs.add(ordenar(tuple(random.sample(cds,2))))

    return GrafoCircular(ciudades, list(acs))

def generarInstanciaSinSolucion(ciudades=10, acuerdos=None):
    if acuerdos is None:
        acuerdos = random.randint(1, ciudades**2/2)

    acs = Set()
    cds = range(ciudades)

    # saco una ciudad al azar, asi el grafo no queda conexo
    # y fuerzo que no haya ninguna solucion valida
    random.shuffle(cds)
    cds.pop()
    cds.sort()
    
    for i in xrange(acuerdos):
        acs.add(ordenar(tuple(random.sample(cds,2))))

    return GrafoCircular(ciudades, list(acs))


def imprimirInstancia(ciudades=10, acuerdos=None):
    g = generarInstancia(ciudades, acuerdos)
    print "%s %s" % (g.n, g.m)
    for each in g.lista_acuerdos:
        print "%s %s" % each


# generadores de archivos de tiempos
def datos_n(max_n=1000):
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

def datos_m(max_m=10000):
    print "Generando datos para el grafico en funcion de M (N constante)..."
    print
    fm = open('datos_m.m','w')
    fm.write('m = [')
    for i in xrange(10, max_m):
        if i % 100 == 0:
            print "%s/%s" % (i, max_m)
        fm.write('%s %s;' % (i, medirTiempo(generarInstancia(ciudades=200, acuerdos=i))))
    fm.write('];')
    fm.close()
    print

def datos_conosinsolucion(n=200,puntos=1000):
    print "Generando datos para el grafico que compara casos con o sin solución..."
    print
    consol = []
    sinsol = []
    for i in xrange(puntos):
        if i % 10 == 0:
            print "%s/%s" % (i, puntos)

        g = generarInstanciaConSolucion(ciudades=n)
        t = medirTiempo(g)
        consol.append((g.m,t))
        g = generarInstanciaSinSolucion(ciudades=n)
        t = medirTiempo(g)
        sinsol.append((g.m,t))

    fd = open('datos_conosinsol.m','w')
    fd.write('m_consol = [')
    for each in consol:
        fd.write('%s %s;' % each)
    fd.write('];\n')

    fd.write('m_sinsol = [')
    for each in sinsol:
        fd.write('%s %s;' % each)
    fd.write('];\n')

    fd.close()
    print


if __name__ == '__main__':
    datos_n()
    datos_m()
    datos_conosinsolucion()

