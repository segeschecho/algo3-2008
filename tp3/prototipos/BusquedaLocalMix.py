from BusquedaLocalIntercambio import *
from BusquedaLocalReInsercion import *
from HeuristicaInsercionEjes import *

class BusquedaLocalMix:
    def mejorar(self,dibujo,marcados1,marcados2,losEjesDe):
      bli = busquedaLocalIntercambioGreedy()
      blr = busquedaLocalReInsercion()
      res = blr.mejorar(dibujo,marcados1,marcados2,losEjesDe)
      res1 = (bli.mejorar(res,marcados1,marcados2,losEjesDe))[0]
      return res1

