import random
from HeuristicaInsercionEjes import *
import psyco
from psyco import *

class BusquedaLocalReInsercion(BusquedaLocal):
    def _rango(self,x,pi,marcados):
        if x not in marcados:
           return range(len(pi)+1)
        else:
               posxMarcado = marcados.index(x)
               anterior=0
               siguiente=len(pi)+1
               if posxMarcado != 0:
                   anterior= pi.index(marcados[posxMarcado-1])+1
               if posxMarcado != len(marcados)-1:
                   siguiente = pi.index(marcados[posxMarcado+1])+1
               z=range(anterior,siguiente)
               if z == []:
                   print "error", z,pi,marcados
               assert z != []
               return z

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
        
        p1 = dibujo.l1
        p2=dibujo.l2
        indice2={}
        for i in range(len(p2)):
            indice2[p2[i]] = i
        #tomamos cada tipito de p1 y vemos si lo podemos reubicar
        for each in p1:
            
            p1.remove(each)
            #rangoi es el rango donde puedo insertar al nodo sin violar el orden parcial entre los moviles
            rangoi = self._rango(each,p1,marcados1)
            p1.insert(rangoi[0],each)
            indice1={}
            crucesInicial = contadorDeCruces(p1,p2,losEjesDe,None,indice2)
            posMinima = rangoi[0]
            crucesAhora = crucesInicial
            crucesMin = crucesInicial
            for i in rangoi:
                if i < rangoi[len(rangoi)-1]:
                    crucesPreSwap = contadorDeCruces(p2,[p1[i],p1[i+1]],losEjesDe,indice2,None)
                    crucesPostSwap = contadorDeCruces(p2,[p1[i+1],p1[i]],losEjesDe,indice2,None)
                    crucesAhora = crucesAhora - crucesPreSwap + crucesPostSwap
                    aux = p1[i]
                    p1[i] = p1[i+1]
                    p1[i+1] = aux
                    if crucesAhora < crucesMin:
                        crucesMin = crucesAhora
                        posMinima = i+1
            p1.remove(each)
            p1.insert(posMinima,each)
        indice1={}
        for i in range(len(p1)):
            indice1[p1[i]] = i
            
        for each in p2: 
            p2.remove(each)
            rangoi = self._rango(each,p2,marcados2)
            
            p2.insert(rangoi[0],each)
            indice2={}
            for i in range(len(p2)):
                indice2[p2[i]] = i
            crucesInicial = contadorDeCruces(p2,p1,losEjesDe,None,indice1)
            posMinima = rangoi[0]
            crucesAhora = crucesInicial
            crucesMin = crucesInicial
            for i in rangoi:
                if i < rangoi[len(rangoi)-1]:
                    crucesPreSwap = contadorDeCruces(p1,[p2[i],p2[i+1]],losEjesDe,indice1,None)
                    crucesPostSwap = contadorDeCruces(p1,[p2[i+1],p2[i]],losEjesDe,indice1,None)
                    crucesAhora = crucesAhora - crucesPreSwap + crucesPostSwap
                    aux = p2[i]
                    p2[i] = p2[i+1]
                    p2[i+1] = aux
                    if crucesAhora < crucesMin:
                        crucesMin = crucesAhora
                        posMinima = i+1
            p2.remove(each)
            p2.insert(posMinima,each)
        resultado = Dibujo(dibujo.g,p1,p2)
        return resultado

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
    blIG=BusquedaLocalReInsercion()
    print "antes de la busqueda",res.contarCruces()
    blIG.hallarMinimoLocal(res,marcados1,marcados2,losEjesDe)
    print "despues de la misma", contadorDeCruces(res.l1,res.l2,losEjesDe)
    DibujadorGrafoBipartito(res,marcados1=marcados1,marcados2=marcados2).grabar('localMediana.svg')        
    
