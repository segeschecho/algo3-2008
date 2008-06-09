from BusquedaLocalIntercambioGreedy import *
from BusquedaLocalReInsercion import *
from HeuristicaInsercionEjes import *

class BusquedaLocalMix(BusquedaLocal):
    def hallarMinimoLocal(self,dibujo,marcados1,marcados2,losEjesDe):
        crucesInicial = contadorDeCruces(dibujo.l1,dibujo.l2,losEjesDe)
        cambio = True
        while cambio:
            cambio = False
            self.mejorar(dibujo,marcados1,marcados2,losEjesDe)
            crucesActual = contadorDeCruces(dibujo.l1,dibujo.l2,losEjesDe)
            if crucesActual < crucesInicial:
                crucesInicial = crucesActual
                cambio = True
    
    def mejorar(self,dibujo,marcados1,marcados2,losEjesDe):
      bli = BusquedaLocalIntercambioGreedy()
      blr = BusquedaLocalReInsercion()
      blr.mejorar(dibujo,marcados1,marcados2,losEjesDe)
      bli.mejorar(dibujo,marcados1,marcados2,losEjesDe)

if __name__ == '__main__':
    g =  generarGrafoBipartitoAleatorio(12, 12, 60)
    d = generarDibujoAleatorio(g,3, 3)
    marcados1 = d.l1[:]
    print marcados1
    marcados2 = d.l2[:]
    print marcados2
    losEjesDe = {}
    for each in g.p1 :
        losEjesDe[each] = []
    for each in g.p2 :
        losEjesDe[each] = []
    for each in g.ejes:
        losEjesDe[each[0]].append(each[1])
        losEjesDe[each[1]].append(each[0])
        
    res=HeuristicaInsercionEjes(d).resolver()
    blIG=BusquedaLocalMix()
    print "antes de la busqueda",res.contarCruces()
    blIG.hallarMinimoLocal(res,marcados1,marcados2,losEjesDe)
    print "despues de la misma", contadorDeCruces(res.l1,res.l2,losEjesDe)
    DibujadorGrafoBipartito(res,marcados1=marcados1,marcados2=marcados2).grabar('localMediana.svg')        
    
