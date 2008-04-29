#!/usr/bin/python
# -*- coding: iso-8859-1 -*-

from grafocircular import GrafoCircular

#################################################################
# Verificador de que un camino es valido                        #
#################################################################

class CaminoNoValido(Exception):
    pass

def noHayRepetidos(l):
    v = l[:]
    v.sort()
    for i in range(len(v)-1):
        if v[i] == v[i+1]:
            return False
    return True


# lanza una excepcion medianamente descriptiva si el camino no es valido
def chequearCaminoValido(grafo, camino):
    
    # se pasa por todos?
    try:
        assert(len(camino)) == grafo.n
        assert(noHayRepetidos(camino))
    except AssertionError:
        raise CaminoNoValido, "El camino propuesto no pasa por todos los nodos del grafo."

    
    # se pasa usando un camino valido?
    for i in range(len(camino)-1):
        if not grafo.estanConectados(camino[i], camino[i+1]):
            raise CaminoNoValido, "El camino propuesto une dos ciudades sin acuerdo (%s y %s)." % (camino[i],camino[i+1])

    
    # el camino no se cruza con si mismo?
    tachados = [camino[0]]
    def siguientes(n):    
        i = (n+1) % grafo.n
        while i in tachados:
            i = (i+1) % grafo.n
        j = (n-1) % grafo.n
        while j in tachados:
            j = (j-1) % grafo.n
        return (i,j)

    for i in range(len(camino)-1):
        actual = camino[i]
        next = camino[i+1]
        if not next in siguientes(actual):
            raise CaminoNoValido, "El camino se cruza con si mismo."
        else:
            tachados.append(next)



# devuelve bool indicando si el camino es valido o no
def esCaminoValido(grafo, camino):
    try:
        chequearCaminoValido(grafo, camino)
    except:
        return False

    return True

