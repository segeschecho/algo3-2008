from GrafoBipartito import *
from GeneradorGrafos import *
from Dibujador import *
import random
import psyco
psyco.full()
# grafo: todos los nodos y ejes, p1 p2 estaRel(v,u)
#dibujo: l1, l2 los nodos que no se pueden mover
class HeuristicaSplitting (ResolvedorConstructivo):
    def contarCrucesAcumTree2(self,p1,p2,losEjes):
        if len(p1) < len(p2):
            return self.contarCrucesAcumTree2(p2,p1,losEjes)
        lista=[]
        indice1={}
        indice2={}
        for i in range(len(p1)):
            indice1[p1[i]]=i
        for i in range(len(p2)):
            indice2[p2[i]]=i
        #radixsort de los ejes
        for each in p2:
            for each2 in losEjes[each]:
                lista.append((indice1[each2],indice2[each]))
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
                print "b1", b1
                print "b2", b2
            while(indice > 0):
                if (indice % 2 == 1):
                    cruces += arbol[indice+1]
                indice=(indice -1)/2
                arbol[indice]+=1
        return cruces

    
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
        else:
            return self.contarCrucesAcumTree2(p2,[x,y],losEjesDe) > self.contarCrucesAcumTree2(p2,[y,x],losEjesDe)

    def qsort(self,p1,p2,marcados,losEjesDe):
        if len(p1) < 2:
            return p1
        marcadosEnP1=[x for x in p1 if x in marcados]
        if marcadosEnP1 == []:
           indPivot = random.randint(0,len(p1)-1)
           pivot = p1[indPivot]
        else:
           pivot = marcadosEnP1[random.randint(0,len(marcadosEnP1)-1)] 
        izq=[x for x in p1 if self.compararNodos(pivot,x,p1,p2,marcados,losEjesDe)]
        der=[y for y in p1 if y != pivot and not (self.compararNodos(pivot,y,p1,p2,marcados,losEjesDe))]
        return self.qsort(izq,p2,marcados,losEjesDe) + [pivot] + self.qsort(der,p2,marcados,losEjesDe)
            
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
        cambio=True
        for i in xrange(len(p1)*len(p2)-2*abs(len(p1)*len(p2)/2 - len(ejes))):
            p1Aux=self.qsort(p1,p2,marcadosl1,losEjesDe)
            crucesAux=self.contarCrucesAcumTree(p1Aux,p2,ejes)
            if crucesAux < cruces:
                p1=p1Aux
                cruces=crucesAux
            p2Aux=self.qsort(p2,p1,marcadosl2,losEjesDe)
            crucesAux = self.contarCrucesAcumTree(p1,p2Aux,ejes)
            if crucesAux < cruces:
                p2=p2Aux
                cruces=crucesAux
        cambio = True
        while cambio:
            cambio=False
            for i in range(len(p1)-1):
                if p1[i] not in marcadosl1 or p1[i+1] not in marcadosl1:
                    comoEsta=self.crucesEntre(p1[i],p1[i+1],p1,p2,losEjesDe)
                    swapeado=self.crucesEntre(p1[i+1],p1[i],p1,p2,losEjesDe)
                    if swapeado < comoEsta:
                        aux=p1[i]
                        p1[i]=p1[i+1]
                        p1[i+1]=aux
                        cambio = True
            for i in range(len(p2)-1):
                if p2[i] not in marcadosl2 or p2[i+1] not in marcadosl2:
                    comoEsta=self.crucesEntre(p2[i],p2[i+1],p2,p1,losEjesDe)
                    swapeado=self.crucesEntre(p2[i+1],p2[i],p2,p1,losEjesDe)
                    if swapeado < comoEsta:
                        aux=p2[i]
                        p2[i]=p2[i+1]
                        p2[i+1]=aux
                        cambio = True
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
                        cambio = True
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
                        cambio = True
            for i in range(len(p1)-1):
                if p1[i] not in marcadosl1 or p1[i+1] not in marcadosl1:
                    comoEsta=self.crucesEntre(p1[i],p1[i+1],p1,p2,losEjesDe)
                    swapeado=self.crucesEntre(p1[i+1],p1[i],p1,p2,losEjesDe)
                    if swapeado < comoEsta:
                        aux=p1[i]
                        p1[i]=p1[i+1]
                        p1[i+1]=aux
                        cambio = True
            for i in range(len(p2)-1):
                if p2[i] not in marcadosl2 or p2[i+1] not in marcadosl2:
                    comoEsta=self.crucesEntre(p2[i],p2[i+1],p2,p1,losEjesDe)
                    swapeado=self.crucesEntre(p2[i+1],p2[i],p2,p1,losEjesDe)
                    if swapeado < comoEsta:
                        aux=p2[i]
                        p2[i]=p2[i+1]
                        cambio = True
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
                        cambio = True
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
                        cambio = True
        print self.contarCrucesAcumTree(p1,p2,ejes)
        return Dibujo(grafo,p1,p2)

        
if __name__ == '__main__':
   g = generarGrafoBipartitoAleatorio(10,10,70)
   print 'nodos =', g.p1
   print 'nodos =', g.p2
   print 'ejes =', g.ejes
   dib = generarDibujoAleatorio(g,6,7)
   resultado = HeuristicaSplitting(dib).resolver()
   DibujadorGrafoBipartito(resultado).grabar('dibujo.svg')