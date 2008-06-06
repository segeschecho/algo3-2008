from GrafoBipartito import *
from GeneradorGrafos import *
from Dibujador import *
import random
# grafo: todos los nodos y ejes, p1 p2 estaRel(v,u)
#dibujo: l1, l2 los nodos que no se pueden mover
class HeuristicaSplitting (ResolvedorConstructivo):
    #calcula cuantos cruces hay entre x e y
    def crucesEntre(self,x,y,p1,p2,losEjesDe):
        return contadorDeCruces(p2,[x,y],losEjesDe)

    #compara 2 nodos
    #devuelve True si x < y (menos cruces entre x e y q entre y y x)
    def compararNodos(self,x,y,p2,losEjesDe):
            return contadorDeCruces(p2,[x,y],losEjesDe) > contadorDeCruces(p2,[y,x],losEjesDe)
    
    #toma un v de grado maximo de v1
    def vMayorGrado(self,v1,losEjesDe):
        mejorVi = v1[0]
        mayorGrado = len(losEjesDe[mejorVi])
        for each in v1:
            grado = len(losEjesDe[each])
            if mayorGrado < grado:
                mayorGrado = grado
                mejorVi = each
        return mejorVi
    
    #ordena segun los cruces entre        
    def qsort(self,v1,p2,marcados,losEjesDe):
        #caso lista vacia
        if v1 == []:
            return marcados
        #caso con solo un elemento movil
        if len(v1) < 2:
            pivote = v1[0]
            marcadosAux = [pivote]+marcados
            minCruces = contadorDeCruces(p2,marcadosAux,losEjesDe)
            crucesActual = minCruces
            mejorIndice = 0
            #pruebo todas las formas de meter al movil entre los no moviles
            #y me quedo con la q genera menos cruces
            for i in range(len(marcadosAux)-1):
                
                crucesPreSwap = contadorDeCruces(p2,[marcadosAux[i],marcadosAux[i+1]],losEjesDe)
                aux = marcadosAux[i+1]
                marcadosAux[i+1]=marcadosAux[i]
                marcadosAux[i]=aux
                crucesPostSwap =  contadorDeCruces(p2,[marcadosAux[i],marcadosAux[i+1]],losEjesDe)
                crucesActual =  crucesActual - crucesPreSwap + crucesPostSwap
                if crucesActual < minCruces:
                    minCruces = crucesActual
                    mejorIndice = i + 1

            marcadosAux.remove(pivote)
            marcadosAux.insert(mejorIndice,pivote)
            return marcadosAux
        #caso normal
        pivote = self.vMayorGrado(v1,losEjesDe)
        #primero qsorteo los moviles
        izq = [x for x in v1 if self.compararNodos(pivote,x,p2,losEjesDe)]
        der = [y for y in v1 if y != pivote and y not in izq]
        marcadosAux = [pivote]+marcados[:]
        minCruces = contadorDeCruces(p2,marcadosAux,losEjesDe)
        crucesActual = minCruces
        mejorIndice = 0
        #ahora miro q me conviene hacer con los no moviles
        for i in range(len(marcadosAux)-1):

            crucesPreSwap = contadorDeCruces(p2,[marcadosAux[i],marcadosAux[i+1]],losEjesDe)
            aux = marcadosAux[i+1]
            marcadosAux[i+1]=marcadosAux[i]
            marcadosAux[i]=aux
            crucesPostSwap =  contadorDeCruces(p2,[marcadosAux[i],marcadosAux[i+1]],losEjesDe)

            crucesActual =  crucesActual - crucesPreSwap + crucesPostSwap
            if crucesActual < minCruces:
                minCruces = crucesActual
                mejorIndice = i+1
        marcadosIzq = [marcados[k] for k in range(mejorIndice)]
        marcadosDer = [marcados[k] for k in range(mejorIndice,len(marcados))]
        return  self.qsort(izq,p2,marcadosIzq,losEjesDe) + [pivote] + self.qsort(der,p2,marcadosDer,losEjesDe)
            
    def resolver(self):
        p1 = list(self.dibujo.g.p1)
        p2 = list(self.dibujo.g.p2)
        print p1
        print p2
        grafo = self.dibujo.g
        dibujo=self.dibujo
        #separo a los q ya estan en el dibujo (son los q tengo q manteer ordenados)
        marcadosl1 = list(self.dibujo.l1)
        print "marcados",marcadosl1
        marcadosl2 = list(self.dibujo.l2)
        print "marcados2",marcadosl2
        #obtengo los que tengo que poner (los q me dieron para agregar)
        v1 = [x for x in p1 if x not in marcadosl1]
        v2 = [y for y in p2 if y not in marcadosl2]
        losEjesDe={}
        ejes = list(grafo.ejes)
        for each in (p1+p2):
            losEjesDe[each]=[]
        for (x,y) in ejes:
            losEjesDe[x]+=[y]
            losEjesDe[y]+=[x]
        p1 = v1+marcadosl1
        p2 = v2+marcadosl2
        cruces = contadorDeCruces(p1,p2,losEjesDe)
        print cruces
        
        #hago qsort 2 veces para cada pi
        for i in range(2):
            p1Aux=self.qsort(v1,p2,marcadosl1,losEjesDe)
            crucesAux=contadorDeCruces(p1Aux,p2,losEjesDe)
            if crucesAux < cruces:
                cruces=crucesAux
                p1=p1Aux
            
            p2Aux=self.qsort(v2,p1,marcadosl2,losEjesDe)
            crucesAux = contadorDeCruces(p1,p2Aux,losEjesDe)
            if crucesAux < cruces:
               p2=p2Aux
               cruces=crucesAux

        print contadorDeCruces(p1,p2,losEjesDe)
        for i in range(len(p1)-1):
            if p1[i] not in marcadosl1 or p1[i+1] not in marcadosl1:
                comoEsta=self.crucesEntre(p1[i],p1[i+1],p1,p2,losEjesDe)
                swapeado=self.crucesEntre(p1[i+1],p1[i],p1,p2,losEjesDe)
                if swapeado < comoEsta:
                    aux=p1[i]
                    p1[i]=p1[i+1]
                    p1[i+1]=aux
 
        for i in range(len(p2)-1):
            if p2[i] not in marcadosl2 or p2[i+1] not in marcadosl2:
                comoEsta=self.crucesEntre(p2[i],p2[i+1],p2,p1,losEjesDe)
                swapeado=self.crucesEntre(p2[i+1],p2[i],p2,p1,losEjesDe)
                if swapeado < comoEsta:
                    aux=p2[i]
                    p2[i]=p2[i+1]
                    p2[i+1]=aux

        listita = range(1,len(p1))
        listita.reverse()
        for i in listita:
            if p1[i] not in marcadosl1 or p1[i-1] not in marcadosl1:
                comoEsta=self.crucesEntre(p1[i-1],p1[i],p1,p2,losEjesDe)
                swapeado=self.crucesEntre(p1[i],p1[i-1],p1,p2,losEjesDe)
                if swapeado < comoEsta:
                    aux=p1[i]
                    p1[i]=p1[i-1]
                    p1[i-1]=aux
        listita = range(1,len(p2))
        listita.reverse()
        for i in listita:
            if p2[i] not in marcadosl2 or p2[i-1] not in marcadosl2:
                comoEsta=self.crucesEntre(p2[i-1],p2[i],p2,p1,losEjesDe)
                swapeado=self.crucesEntre(p2[i],p2[i-1],p2,p1,losEjesDe)
                if swapeado < comoEsta:
                    aux=p2[i]
                    p2[i]=p2[i-1]
                    p2[i-1]=aux
        print contadorDeCruces(p1,p2,losEjesDe)
        return Dibujo(grafo,p1,p2)

        
if __name__ == '__main__':
   g = generarGrafoBipartitoAleatorio(10,10,70)
   print 'nodos =', g.p1
   print 'nodos =', g.p2
   print 'ejes =', g.ejes
   dib = generarDibujoAleatorio(g,6,7)
   resultado = HeuristicaSplitting(dib).resolver()
   DibujadorGrafoBipartito(resultado).grabar('dibujo.svg')
