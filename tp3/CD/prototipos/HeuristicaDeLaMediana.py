from GrafoBipartito import *
from GeneradorGrafos import *
from Dibujador import *
from SolucionBasicaPoda import *
from HeuristicaInsercionEjes import *
import random
# grafo: todos los nodos y ejes, p1 p2 estaRel(v,u)
#dibujo: l1, l2 los nodos que no se pueden mover
class HeuristicaDeLaMediana (ResolvedorConstructivo):
    #no es la version del paper pero para la mediana, aca parto de los q ya estan, calculo la mediana para
    # cada uno q tengo q agregar
    def resolver(self,alfa=1):
        sinMarcar1 = [x for x in self.dibujo.g.p1 if x not in self.dibujo.l1]
        sinMarcar2 = [x for x in self.dibujo.g.p2 if x not in self.dibujo.l2]
        #nodos marcados (posicion relativa fija)
    
        marcados1 = self.dibujo.l1
        marcados2 = self.dibujo.l2
        marcadosl1=marcados1
        marcadosl2=marcados2
        print marcados1
        print marcados2
        #nodos totales
        v1 = sinMarcar1
        v2 = sinMarcar2 
        #inicializa arreglo de medianas para los nodos de v1
        p1 = marcados1[:]
        p2 = marcados2[:]
        #ejesDe: listas de adyacencias
        ejesDe = {}
        losEjesEntreLosPuestos = {}
        medianas={}
        #lo inicializo
        for each in v1 + v2+marcados1+marcados2:
            losEjesEntreLosPuestos[each] = []
        for each in v1+v2+marcados1+marcados2:
            ejesDe[each] = []
            medianas[each]=0
        #la completo
        for each in self.dibujo.g.ejes:
            ejesDe[each[0]].append(each[1])
            ejesDe[each[1]].append(each[0])
            if each[1] in p2:
                losEjesEntreLosPuestos[each[0]].append(each[1])
            if each[0] in p1:
                losEjesEntreLosPuestos[each[1]].append(each[0])
        
        while (v1 != [] or v2 != []):
            #toma uno con grado >= alfa*max (lo saca ademas)
            (x,donde)=self.tomarUnoDeMayorGrado(v1,v2,losEjesEntreLosPuestos,alfa=1)
            if donde == 1:
                    #va en p1
                    med=self.calcularMediana(x,p2,losEjesEntreLosPuestos)
                    medianas[x] = med
                    if med > len(p1):
                        med = len(p1)
                    for each in ejesDe[x]:
                        losEjesEntreLosPuestos[each].append(x)
                    medMenos1 = med - 1
                    medMas1 = med + 1
                    p1.insert(med,x)
                    crucesInicial = contadorDeCruces(p1,p2,losEjesEntreLosPuestos)
                    crucesMejor = crucesInicial
                    indiceMejor = med
                    if medMenos1 >= 0:
                        crucesPreSwap = crucesEntre(p1[med-1],p1[med],p2,losEjesEntreLosPuestos)
                        crucesPostSwap = crucesEntre(p1[med],p1[med-1],p2,losEjesEntreLosPuestos)
                        if crucesPostSwap > crucesPreSwap:
                            indiceMejor = med - 1
                            crucesMejor = crucesInicial - crucesPreSwap + crucesPostSwap
                    if medMas1 < len(p1):
                        crucesPreSwap = crucesEntre(p1[med],p1[med+1],p2,losEjesEntreLosPuestos)
                        crucesPostSwap = crucesEntre(p1[med+1],p1[med],p2,losEjesEntreLosPuestos)
                        if crucesMejor > (crucesInicial - crucesPreSwap + crucesPostSwap):
                            indiceMejor = med + 1
                    if indiceMejor == medMenos1:
                        aux = p1[med]
                        p1[med] = p1[med - 1]
                        p1[med - 1] = aux
                    if indiceMejor == medMas1:
                        aux = p1[med]
                        p1[med] = p1[med + 1]
                        p1[med + 1] = aux
                        
            else:
                    med=self.calcularMediana(x,p1,losEjesEntreLosPuestos)
                    medianas[x] = med
                    if med > len(p2):
                        med = len(p2)
                    for each in ejesDe[x]:
                        losEjesEntreLosPuestos[each].append(x)
                    medMenos1 = med - 1
                    medMas1 = med + 1
                    p2.insert(med,x)
                    crucesInicial = contadorDeCruces(p2,p1,losEjesEntreLosPuestos)
                    crucesMejor = crucesInicial
                    indiceMejor = med
                    if medMenos1 >= 0:
                        crucesPreSwap = crucesEntre(p2[med-1],p2[med],p1,losEjesEntreLosPuestos)
                        crucesPostSwap = crucesEntre(p2[med],p2[med-1],p1,losEjesEntreLosPuestos)
                        if crucesPostSwap > crucesPreSwap:
                            indiceMejor = med - 1
                            crucesMejor = crucesInicial - crucesPreSwap + crucesPostSwap
                    if medMas1 < len(p2):
                        crucesPreSwap = crucesEntre(p2[med],p2[med+1],p1,losEjesEntreLosPuestos)
                        crucesPostSwap = crucesEntre(p2[med+1],p2[med],p1,losEjesEntreLosPuestos)
                        if crucesMejor > (crucesInicial - crucesPreSwap + crucesPostSwap):
                            indiceMejor = med + 1
                    if indiceMejor == medMenos1:
                        aux = p2[med]
                        p2[med] = p2[med - 1]
                        p2[med - 1] = aux
                    if indiceMejor == medMas1:
                        aux = p2[med]
                        p2[med] = p2[med + 1]
                        p2[med + 1] = aux
        #tratamos de arreglar los corrimientos por empate, hacemos para eso unos swaps                    
        p1 = self.corregirDesvios(p1,p2,marcadosl1,ejesDe)
        p2 = self.corregirDesvios(p2,p1,marcadosl2,ejesDe)
        return Dibujo(self.dibujo.g,p1,p2)
    

                    
        
    
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
    
    def tomarUnoDeMayorGrado(self,v1,v2,losEjesDe,alfa=1):
        maxGrado = 0
        for each in v1:
            if len(losEjesDe[each]) > maxGrado:
                maxGrado=len(losEjesDe[each])
        for each in v2:
            if len(losEjesDe[each]) > maxGrado:
                maxGrado=len(losEjesDe[each])
        assert alfa <= 1
        gradoAlfa = maxGrado*alfa
        candidatos = []
        for each in v1:
            if len(losEjesDe[each]) >= gradoAlfa:
                candidatos.append(each)
        for each in v2:
            if len(losEjesDe[each]) >= gradoAlfa:
                candidatos.append(each)
        
        
        winner=random.sample(candidatos,1)
        ganador = winner[0]

        if ganador in v1:
            v1.remove(ganador)
            return (ganador,1)
        else:
            v2.remove(ganador)
            return (ganador,2)
        
    def calcularMediana(self,x,pi,losEjesDe):
        indice = {}
        for i in range(len(pi)):
            indice[pi[i]] = i
        med = []
        for each in losEjesDe[x]:
               med.append(indice[each])
        med.sort()
        if med == []:
            return 0
        if len(med) % 2 == 0:
            return int(round(float((med[len(med)/2] + med[(len(med)-1)/2]))/2))
        else:
            return med[len(med)/2]
    
        

if __name__ == '__main__':
   g = generarGrafoBipartitoAleatorio(6,6,10)
   print 'nodos =', g.p1
   print 'nodos =', g.p2
   print 'ejes =', g.ejes
   dib = generarDibujoAleatorio(g,2,2)
   resultado = HeuristicaDeLaMediana(dib).resolver()
   print "ahora dio", resultado.contarCruces()
   DibujadorGrafoBipartito(resultado).grabar('dibujo.svg')
