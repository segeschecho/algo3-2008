from GrafoBipartito import *
from GeneradorGrafos import *
from Dibujador import *
from heuristicaFede import *
import random
import psyco
psyco.full()
# grafo: todos los nodos y ejes, p1 p2 estaRel(v,u)
#dibujo: l1, l2 los nodos que no se pueden mover
class heuristicaSplitting (ResolvedorConstructivo):
    def contarCrucesAcumTree(self,p1,p2,ejes):
        if len(p1) < len(p2):
            return self.contarCrucesAcumTree(p2,p1,[(y,x) for (x,y) in ejes])
        lista=[]
        indice1={}
        indice2={}
        for i in range(len(p1)):
            indice1[p1[i]]=i
        for i in range(len(p2)):
            indice2[p2[i]]=i
            
        for each in ejes:
            lista.append((indice1[each[0]],indice2[each[1]]))
        b1=[[] for each in range(len(p2))]
        b2=[[] for each in range(len(p1))]
        for each in lista:
            b1[each[1]].append(each)
        lista2=[]
        for i in range(len(b1)):
            lista2.extend(b1[i])
        for each in lista2:
            b2[each[0]].append(each)
        lista2=[]
        for i in range(len(b2)):
            lista2.extend(b2[i])
        #print lista2

        sur=[]
        for each in lista2:
            sur.append(each[1])
        primerIndice=1
        while primerIndice <= len(p2):
            primerIndice *= 2
        arbol = [0]*(2*primerIndice - 1)
        primerIndice -=1

        cruces=0
        for i in range(len(sur)):
            indice=sur[i]+primerIndice
            try:
                arbol[indice]+=1
            except:
                print "arbol",arbol
                print "indice",indice
                print "sur",sur
                print "i",i
                print "p1", p1
                print "p2",p2
                #print "lista2",lista2
                print "b1", b1
                print "b2", b2
            while(indice > 0):
                if (indice % 2 == 1):
                    cruces += arbol[indice+1]
                indice=(indice -1)/2
                arbol[indice]+=1
        return cruces

    def crucesEntre(self,x,y,p1,p2,losEjesDe):
         indiceX = p1.index(x)
         indiceY = p1.index(y)
    ##     if indiceX < indiceY:
    ##         aux=indiceX
    ##         indiceX=indiceY
    ##         indiceY=indiceX
         acum=0
         for each in losEjesDe[x]:
             indiceEach = p2.index(each)
             for each2 in losEjesDe[y]:
                 #if indiceEach >= indiceY and indiceEach > p2.index(each2):
                  if indiceEach > p2.index(each2):
                     acum += 1
                 #if indiceEach < indiceY and indiceEach > p2.index(each2):
                 #    acum += 1
         return acum

    def compararNodos(self,x,y,p1,p2,marcados,losEjesDe):
        if x in marcados and y in marcados:
            return marcados.index(y) < marcados.index(x)
        elif y in marcados:
            k = marcados.index(y)
            if k != 0:
                caca=None
                if self.crucesEntre(marcados[k-1],x,p1,p2,losEjesDe) < self.crucesEntre(x,marcados[k-1],p1,p2,losEjesDe):
                    return self.crucesEntre(y,x,p1,p2,losEjesDe) < self.crucesEntre(x,y,p1,p2,losEjesDe)
                else:
                    return True
            else:
                 return self.crucesEntre(y,x,p1,p2,losEjesDe) < self.crucesEntre(x,y,p1,p2,losEjesDe)
        else:
            return self.crucesEntre(y,x,p1,p2,losEjesDe) < self.crucesEntre(x,y,p1,p2,losEjesDe)
    
    def qsort(self,p1,p2,marcados,losEjesDe,gradosNoNulos,grados):
        if len(p1) < 2:
            return p1
        indPivot = random.randint(0,len(p1)-1)
        pivot = p1[indPivot]
        if pivot not in gradosNoNulos:
            i = 0
            pivot=None
            while i < len(gradosNoNulos):
                if gradosNoNulos[i] in p1 :
                    pivot = gradosNoNulos[i]
                    break
                i+=1
            if pivot == None:
                return p1
            
        izq=[x for x in p1 if self.compararNodos(pivot,x,p1,p2,marcados,losEjesDe)]
        der=[y for y in p1 if y != pivot and not (self.compararNodos(pivot,y,p1,p2,marcados,losEjesDe))]
        return self.qsort(izq,p2,marcados,losEjesDe, gradosNoNulos,grados) + [pivot] + self.qsort(der,p2,marcados,losEjesDe, gradosNoNulos,grados)
    
        
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
        gradosNoNulosP1=[]
        gradosNoNulosP2=[]
        grados=[0]*(len(p1)+len(p2))
        for each in p1:
            if losEjesDe[each] != []:
                gradosNoNulosP1+=[each]
            grados[each] =len(losEjesDe[each])
        for each in p2:
            if losEjesDe[each] != []:
                gradosNoNulosP2+=[each]
            grados[each] =len(losEjesDe[each])
            
        if gradosNoNulosP1==[]:
            return dibujo
        cruces = self.contarCrucesAcumTree(p1,p2,ejes)
        p1=marcadosl1+v1
        p2=marcadosl2+v2
        print cruces
        for i in range(len(p1)*len(p2)-2*abs(len(p1)*len(p2)/2 - len(ejes))):
            p1Aux=self.qsort(p1,p2,marcadosl1,losEjesDe,gradosNoNulosP1,grados)
            crucesAux=self.contarCrucesAcumTree(p1Aux,p2,ejes)
            if crucesAux < cruces:
                p1=p1Aux
                cruces=crucesAux
            p2Aux=self.qsort(p2,p1,marcadosl2,losEjesDe,gradosNoNulosP2,grados)
            crucesAux = self.contarCrucesAcumTree(p1,p2Aux,ejes)
            if crucesAux < cruces:
                p2=p2Aux
                cruces=crucesAux
            
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
        print self.contarCrucesAcumTree(p1,p2,ejes)
        return Dibujo(grafo,p1,p2)

##a = GrafoBipartito(Set([1,2,3,4,5]),Set([6,7,8]),Set([(1,6),(2,6),(2,7),(3,7),(4,8),(1,8)]))
##dib=Dibujo(a,[1,2,3],[6])
##f = heuristicaSplitting(dib)
##dibujo = f.resolver()
g = generarGrafoBipartitoAleatorio(5,5,14)
d = generarDibujoAleatorio(g,3,2)
f = heuristicaSplitting(d)
f1 = heuristicaFede(d)
dibujo=f.resolver()
print "terminooooooooooooooo split"
dibujo2=f1.grafoDenso()
dibujo1=f1.resolver()
print  "cruces heursplit", dibujo.contarCruces()
print "cruces heurfed", dibujo1.contarCruces()
print "cruces grafoDenso", dibujo2.contarCruces()
dibu = DibujadorGrafoBipartito( dibujo)
dibu.grabarYMostrar()
        
        
