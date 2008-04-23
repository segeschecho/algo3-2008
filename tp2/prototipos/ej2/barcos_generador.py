#!/usr/bin/python
# -*- coding: iso-8859-1 -*-

from grafocircular import GrafoCircular
import random

#################################################################
# Generador de instancias de barcos y ciudades                  #
#################################################################

def generarInstancia(ciudades=10, acuerdos=None):
    if acuerdos is None:
        acuerdos = random.randint(1, ciudades**2)
    
    acs = []
    cds = range(ciudades)
    for i in range(acuerdos):
        acs.append(tuple(random.sample(cds,2)))

    return GrafoCircular(ciudades, acs)
