#!/usr/bin/python
# -*- coding: iso-8859-1 -*-

from grafocircular import GrafoCircular

#################################################################
# Versión de decisión                                           #
#################################################################

def hayCaminoTerminaEnA(a,b,g):
    n = g.n
    if b-a == 1 or (b == 0 and a == n-1):
        return g.estanConectados(a,b)
   
    return (hayCaminoTerminaEnA((a+1) % n, b, g) and g.estanConectados(a, (a+1) % n)) or \
           (hayCaminoTerminaEnB((a+1) % n, b, g) and g.estanConectados(a,b))

def hayCaminoTerminaEnB(a,b,g):
    n = g.n
    if b-a == 1 or (b == 0 and a == n-1):
        return g.estanConectados(a,b)

    return (hayCaminoTerminaEnA(a, (b-1) % n, g) and g.estanConectados(a,b)) or \
           (hayCaminoTerminaEnB(a, (b-1) % n, g) and g.estanConectados((b-1) % n,b))

def hayCamino(g):
    for i in range(g.n):
        a = i
        b = (i-1) % g.n
        if hayCaminoTerminaEnA(a,b,g) or hayCaminoTerminaEnB(a,b,g):
            return True

        return False

# version "verbose" que tira mas informacion
def hayCamino2(g):
    print "Buscando caminos (%s nodos, %s acuerdos)" % (g.n, g.a)
    for i in range(g.n):
        a = i
        b = (i-1) % g.n
        print "  Camino de %s a %s:" % (a,b)
        p = 0
        if hayCaminoTerminaEnA(a,b,g): 
            print "    Hay un camino que empieza en %s" % a
            p = 1
        if hayCaminoTerminaEnB(a,b,g):
            print "    Hay un camino que empieza en %s" % b
            p = 1
        if p != 1:
            print "    Ninguno"


#################################################################
# Versiones de construcción de caminos (recursión sin tablas)   #
#################################################################


def caminoQueTerminaEnA(a,b,g):
    # caso base
    if b-a == 1 or (b == 0 and a == g.n-1):
        if g.estanConectados(a,b):
            return [b,a]
        else:
            return []

    # caso recursivo
    c = caminoQueTerminaEnA((a+1) % g.n, b, g)
    if c != [] and g.estanConectados(a, (a+1) % g.n):
        return c + [a]
    c = caminoQueTerminaEnB((a+1) % g.n, b, g)
    if c != [] and g.estanConectados(a,b):
        return c + [a]

    return []

def caminoQueTerminaEnB(a,b,g): 
    # caso base
    if b-a == 1 or (b == 0 and a == g.n-1):
        if g.estanConectados(a,b):
            return [a,b]
        else:
            return []
    
    # caso recursivo
    c = caminoQueTerminaEnA(a, (b-1) % g.n, g)
    if c != [] and g.estanConectados(a,b):
        return c + [b]
    c = caminoQueTerminaEnB(a, (b-1) % g.n, g)
    if c != [] and g.estanConectados((b-1) % g.n, b):
        return c + [b]

    return []


# algoritmo de busqueda
def generarCamino(g):
    for i in range(g.n):
        a = i
        b = (i-1) % g.n
        
        c = caminoQueTerminaEnA(a,b,g)
        if c != []:
            return c

        c = caminoQueTerminaEnB(a,b,g)
        if c != []:
            return c

    return []


def grafoDesdeArchivo(fname):
    f = open(fname)
    l = f.readline()
    n,m = [int(x) for x in l.split()]
    
    acuerdos = []
    for i in range(m):
        l = f.readline()
        a,b = [int(x) for x in l.split()]
        
        if l == '' or (a,b) == (0,0):
            raise ValueError, "El archivo no tenia el formato esperado!"

        acuerdos.append((a-1,b-1))

    return GrafoCircular(n,acuerdos)


#################################################################
# Prueba simple                                                 #
#################################################################


if __name__ == '__main__':
    
    # Ejemplo del enunciado
    #acuerdos = [(1,2),(2,3),(2,4),(2,5),(3,0),(4,0),(4,5)]
    #n = 6
    #g = GrafoCircular(n, acuerdos)

    # Instancia al azar
    from barcos_generador import generarInstancia
    g = generarInstancia(ciudades=20)

    # Instancia desde archivo
    #g = grafoDesdeArchivo('Tp2Ej2.in')
    
    print g
    
    
    # Metodo recursivo convencional
    #c = generarCamino(g)

    # Metodo con tabulado por demanda
    from barcos_tabla import BuscadorCaminoTPD
    b = BuscadorCaminoTPD(g)
    c = b.buscarCamino()
    print c

    # Metodo con tabulado al inicio
    from barcos_tabla import BuscadorCaminoTCI
    b2 = BuscadorCaminoTCI(g)
    c2 = b2.buscarCaminoLoco()
    print c2

    if c == [] and hayCamino(g):
        print "No se pudo encontrar el camino y sin embargo parecía haberlo!"
    
    if c2 == [] and hayCamino(g):
        print "No se pudo encontrar el camino y sin embargo parecía haberlo!"
    
    if c != []:
        from barcos_tester import chequearCaminoValido
        chequearCaminoValido(g, c)

    if c2 != []:
        from barcos_tester import chequearCaminoValido
        chequearCaminoValido(g, c2)
