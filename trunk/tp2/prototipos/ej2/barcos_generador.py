#!/usr/bin/python
# -*- coding: iso-8859-1 -*-

from grafocircular import GrafoCircular
from sets import Set
import random

#################################################################
# Generador de instancias de barcos y ciudades                  #
#################################################################

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
