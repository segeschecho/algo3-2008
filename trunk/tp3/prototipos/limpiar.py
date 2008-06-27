import random
from HeuristicaInsercionEjes import *
from HeuristicaInsercionNodos import *
from HeuristicaDeLaMediana import *
from SolucionSwapperTablaPoda import *
import psyco
from psyco import *

class Tp3:
    def limpiarDibujo(self,d,losEjesDe):
        g = d.g
        marcados1 = d.l1
        marcados2 = d.l2
        print "marcados1",marcados1
        print "marcados2",marcados2
        marcadosNoNulos1 = [x for x in marcados1 if not len(losEjesDe[x]) == 0]
        marcadosNoNulos2 = [x for x in marcados2 if not len(losEjesDe[x]) == 0]
        nulos1=[]
        noNulos1=[]
        noNulos2=[]
        nulos2=[]
        for each in g.p1:
            if each not in marcados1:
                if len(losEjesDe[each]) == 0:
                    nulos1.append(each)
                else:
                    noNulos1.append(each)
        for each in g.p2:
            if each not in marcados2:
                if len(losEjesDe[each]) == 0:
                    nulos2.append(each)
                else:
                    noNulos2.append(each)
                
        self.traduccion = [0 for x in range(len(noNulos1)+ len(noNulos2)+len(marcadosNoNulos1)+ len(marcadosNoNulos2))]
        i = 0
        losEjesNuevos ={}
        indice = [ 0 for x in range(len(g.p1)+len(g.p2))]
        nuevoP1=[]
        nuevoP2=[]
        
        for each in marcadosNoNulos1:
            losEjesNuevos[i]=[]
            self.traduccion[i] = each
            indice[each] = i
            i = i +1
            

        for each in marcadosNoNulos2:
            losEjesNuevos[i]=[]
            self.traduccion[i] = each
            indice[each] = i
            i = i +1
            
        for each in noNulos1:
            losEjesNuevos[i]=[]
            self.traduccion[i] = each
            indice[each] = i
            i+=1

        for each in noNulos2:
            losEjesNuevos[i]=[]
            self.traduccion[i] = each
            indice[each] = i
            i+=1
                
        ejesNuevos = []
        ejes = [] #esto es solo por el generador de python
        for each in noNulos1+marcadosNoNulos1:
            for y in losEjesDe[each]:
                x=each
                losEjesNuevos[indice[x]].append(indice[y])
                ejes.append((indice[x],indice[y]))
                losEjesNuevos[indice[y]].append(indice[x])
                ejesNuevos.append((x,y))

        cantV1 = len(marcadosNoNulos1)
        cantIV1 = len(noNulos1)
        cantV2 = len(marcadosNoNulos2)
        cantIV2 = len(noNulos2)
        grafo = GrafoBipartito(Set(range(cantV1)+range(cantV1+cantV2,cantV1+cantV2+cantIV1)),Set(range(cantV1,cantV1+cantV2)+range(cantV1+cantV2+cantIV1,cantV1+cantV2+cantIV1+cantIV2)),Set(ejes))

        Dib = Dibujo(grafo,range(cantV1),range(cantV1,cantV1+cantV2))
        self.indice=indice
        self.marcados1 = marcados1
        self.marcados2 = marcados2
        self.noNulos1 = noNulos1
        self.noNulos2 = noNulos2
        self.g = g
        self.nulos1 = nulos1
        self.nulos2 = nulos2
        self.marcadosNoNulos1 = marcadosNoNulos1
        self.marcadosNoNulos2 = marcadosNoNulos2
        
        return Dib

    def reconstruirDibujo(self,d):
        i = 0
        marcados1=self.marcados1
        traduccion = self.traduccion
        marcados2=self.marcados2
        p1Posta = []
        for each in d.l1:

            if traduccion[each] not in marcados1:
                p1Posta.append(self.traduccion[each])
            else:
                while(i < len(marcados1) and marcados1[i] != traduccion[each]):
                    p1Posta.append(marcados1[i])
                    i+=1
                i+=1
                p1Posta.append(self.traduccion[each])
        p1Posta.extend(self.nulos1)
        p1Posta.extend(self.marcados1[i:])
        p2Posta = []
        i=0
        for each in d.l2:

            if traduccion[each] not in marcados2:
                p2Posta.append(self.traduccion[each])
            else:
                while(i < len(marcados2) and marcados2[i] != traduccion[each]):
                    p2Posta.append(marcados2[i])
                    i+=1
                i+=1
                p2Posta.append(self.traduccion[each])
        p2Posta.extend(self.nulos2)
        p2Posta.extend(self.marcados2[i:])

        return Dibujo(self.g,p1Posta,p2Posta)

g =  generarGrafoBipartitoAleatorio(10, 7, 8)
d = generarDibujoAleatorio(g,5,4)
losEjesDe = {}
for each in g.p1 :
    losEjesDe[each] = []
for each in g.p2 :
    losEjesDe[each] = []
for each in g.ejes:
    losEjesDe[each[0]].append(each[1])
    losEjesDe[each[1]].append(each[0])
tp3 = Tp3()
dibu = tp3.limpiarDibujo(d,losEjesDe)
print dibu.l1
res = HeuristicaInsercionNodos(tp3.limpiarDibujo(d,losEjesDe)).resolver()
print "ahhh",len(dibu.l2),len(dibu.g.p2)
print tp3.reconstruirDibujo(res)
