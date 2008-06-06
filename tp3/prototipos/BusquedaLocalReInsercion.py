import random
from HeuristicaInsercionEjes import *
from SolucionBasicaPoda import *
from BusquedaLocalIntercambioAzar import *
from medianaReloadad import *
import psyco
from psyco import *

class busquedaLocalReInsercion:
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
   g = generarGrafoBipartitoAleatorio(8,7,26)
   print 'nodos =', g.p1
   print 'nodos =', g.p2
   print 'ejes =', g.ejes
   ejes = g.ejes
   dib = generarDibujoAleatorio(g,3,3)
   marcadosl1 = dib.l1[:]
   marcadosl2 = dib.l2[:]
   print "marcadosl1",marcadosl1
   print "marcadosl2",marcadosl2
   resultado = HeuristicaMediana2(dib).resolver()
   
   #posta = ResolvedorBasicoConPoda(dib).resolver()
   DibujadorGrafoBipartito(resultado).grabar('sinLocal.svg')
   losEjesDe = {}
   for each in resultado.l1+resultado.l2:
       losEjesDe[each] = []
   for each in ejes:
        losEjesDe[each[0]].append(each[1])
        losEjesDe[each[1]].append(each[0])
   bl = busquedaLocalReInsercion()
   cruces = resultado.contarCruces()
   print cruces
   while(True):
       resultado = bl.mejorar(resultado,marcadosl1,marcadosl2,losEjesDe)
       print "ahora", contadorDeCruces(resultado.l1,resultado.l2,losEjesDe)
       if contadorDeCruces(resultado.l1,resultado.l2,losEjesDe) == cruces:
            break
       if contadorDeCruces(resultado.l1,resultado.l2,losEjesDe) > cruces:
            raise Exception("no mejora una goma")
       cruces = contadorDeCruces(resultado.l1,resultado.l2,losEjesDe)
   print "logre",contadorDeCruces(resultado.l1,resultado.l2,losEjesDe)
   
   resultado = HeuristicaMediana2(dib).resolver()
   DibujadorGrafoBipartito(resultado).grabar('PostLocal.svg')
   cruces = resultado.contarCruces()
   print cruces
   caca = busquedaLocalIntercambio().mejorar(resultado,marcadosl1,marcadosl2,losEjesDe)
   i=0
   while(caca[1]):
       print "mejora",contadorDeCruces(resultado.l1,resultado.l2,losEjesDe)
       resultado = caca[0]
       caca = busquedaLocalIntercambio().mejorar(resultado,marcadosl1,marcadosl2,losEjesDe)
       if caca[1]:
           i=0
       else:
           i+=1
   resultado=caca[0]
   print contadorDeCruces(resultado.l1,resultado.l2,losEjesDe)
   DibujadorGrafoBipartito(resultado).grabar('Local.svg')
   #print "la posta", posta.contarCruces()
           
        
    