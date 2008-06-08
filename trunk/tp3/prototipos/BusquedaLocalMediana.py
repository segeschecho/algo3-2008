import random
from HeuristicaInsercionEjes import *
import psyco
psyco.full()

class BusquedaLocalMediana:
    def calcularMediana(self,each,indicesi,losEjesDe):
        med = []
        for each1 in losEjesDe[each]:
            med.append(indicesi[each1])
        med.sort()
        if med == []:
            return 0
        if len(med) % 2:
            return int(round(float((med[len(med)/2] + med[(len(med)-1)/2]))/2))
        else:
            return med[len(med)/2]
    
    def corregirDesvios(self,v1Aux,v2,marcados,ejesDe):
        for fede in range(2):
            #primero hacemos swap desde arriba hacia abajo
            for i in range(len(v1Aux)-1):
                if v1Aux[i] not in marcados or v1Aux[i+1] not in marcados:
                    if contadorDeCruces([v1Aux[i],v1Aux[i+1]],v2,ejesDe) > contadorDeCruces([v1Aux[i+1],v1Aux[i]],v2,ejesDe):
                        aux = v1Aux[i]
                        v1Aux[i] = v1Aux[i+1]
                        v1Aux[i+1] = aux
            for i in range(1,len(v1Aux)):
                if v1Aux[len(v1Aux)-i] not in marcados or v1Aux[len(v1Aux)-i -1] not in marcados:
                    if contadorDeCruces([ v1Aux[len(v1Aux)-i -1],v1Aux[len(v1Aux)-i]],v2,ejesDe) > contadorDeCruces([v1Aux[len(v1Aux)-i], v1Aux[len(v1Aux)-i -1]],v2,ejesDe):

                        aux = v1Aux[len(v1Aux)-i]
                        v1Aux[len(v1Aux)-i] = v1Aux[len(v1Aux)-i -1]
                        v1Aux[len(v1Aux)-i -1] = aux
        return v1Aux
        
    def puedoInsertar(self,each,pi,marcadosi,med):
        if each not in marcadosi:
            return True
        else:
            k = marcadosi.index(each)
            anterior = -1
            siguiente = len(pi)
            if k != 0:
                anterior = pi.index(marcadosi[k-1])
            if k != len(marcadosi)-1:
                siguiente = pi.index(marcadosi[k+1])
            return anterior < med and med < siguiente
   
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
        p2 = dibujo.l2
        indices2 = {}
        for i in range(len(p2)):
            indices2[p2[i]] = i
        p1Copia = p1[:]
        crucesActual = contadorDeCruces(p1,p2,losEjesDe,None,indices2)
        for each in p1Copia:
            med = self.calcularMediana(each,indices2,losEjesDe)
            if med >= len(p1):
                med = len(p1)-1
            puedo = False
            if self.puedoInsertar(each,p1,marcados1,med):
                puedo = True
            elif med < len(p1)-1 and self.puedoInsertar(each,p1,marcados1,med+1):
                med = med + 1
                puedo = True
            elif med > 0 and self.puedoInsertar(each,p1,marcados1,med-1):
                med = med -1
                puedo = True
            if puedo:
                indiceEach = p1.index(each)
                p1.remove(each)
                p1.insert(med,each)
                nuevosCruces = contadorDeCruces(p1,p2,losEjesDe,None,indices2)
                if nuevosCruces > crucesActual:
                    p1.remove(each)
                    p1.insert(indiceEach,each)
                else:
                    crucesActual = nuevosCruces
            
        indices1 = {}
        for i in range(len(p1)):
            indices1[p1[i]] = i
        p2Copia = p2[:]            
        for each in p2Copia:
            med = self.calcularMediana(each,indices1,losEjesDe)
            if med >= len(p2):
                med = len(p2)-1
            puedo = False
            if self.puedoInsertar(each,p2,marcados2,med):
                puedo = True
            elif med < len(p2)-1 and self.puedoInsertar(each,p2,marcados2,med+1):
                med = med + 1
                puedo = True
            elif med > 0 and self.puedoInsertar(each,p2,marcados2,med-1):
                med = med -1
                puedo = True
            if puedo:
                indiceEach = p2.index(each)
                p2.remove(each)
                p2.insert(med,each)
                nuevosCruces = contadorDeCruces(p2,p1,losEjesDe,None,indices1)
                if nuevosCruces > crucesActual:
                    p2.remove(each)
                    p2.insert(indiceEach,each)
                else:
                    crucesActual = nuevosCruces
        crucesActual = contadorDeCruces(p1,p2,losEjesDe,None,indices2)
        cambio = True
        while cambio:
            cambio = False
            p1 =self.corregirDesvios(p1,p2,marcados1,losEjesDe)
            p2 =self.corregirDesvios(p2,p1,marcados2,losEjesDe)
            crucesMejor = contadorDeCruces(p1,p2,losEjesDe,None,indices2)
            if crucesMejor < crucesActual:
                crucesActual = crucesMejor
                cambio = True

if __name__ == '__main__':
    g =  generarGrafoBipartitoAleatorio(100, 100, 200)
    d = generarDibujoAleatorio(g,50, 50)
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
    blIG=BusquedaLocalMediana()
    print "antes de la busqueda",res.contarCruces()
    blIG.hallarMinimoLocal(res,marcados1,marcados2,losEjesDe)
    print "despues de la misma", contadorDeCruces(res.l1,res.l2,losEjesDe)
    DibujadorGrafoBipartito(res,marcados1=marcados1,marcados2=marcados2).grabar('localMediana.svg')        
    


