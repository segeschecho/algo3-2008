from GrafoBipartito import *
from GeneradorGrafos import *
from Dibujador import *
from HeuristicaSplitting import *
# grafo: todos los nodos y ejes, p1 p2 estaRel(v,u)
#dibujo: l1, l2 los nodos que no se pueden mover
class HeuristicaMediana (ResolvedorConstructivo):
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

    
    def resolver(self):
    # Mariconadas
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
        #meto a todos los nodos en un "dibujo"
        p1Parcial = marcadosl1 + v1
        p2Parcial = marcadosl2 + v2
        #agarro los ejes del grafo
        ejes = list(grafo.ejes)
        losEjesDe ={}
        for each in (p1Parcial+p2Parcial):
            losEjesDe[each]=[]
        for (x,y) in ejes:
            losEjesDe[x]+=[y]
            losEjesDe[y]+=[x]
        indice={}
        for i in range(len(p2Parcial)):
            indice[p2Parcial[i]]=i
        for i in range(len(p1Parcial)):
            indice[p1Parcial[i]]=i
        medianasp1={}
        medianasp2={}
        p1=p1Parcial
        p2=p2Parcial
        cruces =  self.contarCrucesAcumTree(p1,p2,ejes)
        print "cruces antes", cruces
        
            
        for i in range(len(p1)*len(p2)-2*abs(len(p1)*len(p2)/2 - len(ejes))):
            for i in range(len(p2Parcial)):
                indice[p2[i]]=i
            for i in range(len(p1Parcial)):
                indice[p1[i]]=i
            for each in p1:
                medianasp1[each]=self.calcularMediana(each,losEjesDe,indice,p2)
            for each in p2:
                medianasp2[each]=self.calcularMediana(each,losEjesDe,indice,p1)
            p1Aux=self.qsort(p1,p2,marcadosl1,losEjesDe,medianasp1)
            crucesAux=self.contarCrucesAcumTree(p1Aux,p2,ejes)
            if crucesAux < cruces:
                p1=p1Aux
                cruces=crucesAux
            p2Aux=self.qsort(p2,p1,marcadosl2,losEjesDe,medianasp2)
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
        print "cruces ahora", self.contarCrucesAcumTree(p1,p2,ejes)
        return Dibujo(self.dibujo.g,p1,p2)
    
    def compararNodos(self,x,y,p1,p2,marcados,losEjesDe,mediana):
        if x in marcados and y in marcados:
            return marcados.index(y) < marcados.index(x)
        else:
            return mediana[y] < mediana[x]
    
    def qsort(self,p1,p2,marcados,losEjesDe,mediana):
        if len(p1) < 2:
            return p1
        marcadosEnP1=[x for x in p1 if x in marcados]
        if marcadosEnP1 == []:
           indPivot = random.randint(0,len(p1)-1)
           pivot = p1[indPivot]
        else:
           pivot = marcadosEnP1[random.randint(0,len(marcadosEnP1)-1)] 
        izq=[x for x in p1 if self.compararNodos(pivot,x,p1,p2,marcados,losEjesDe,mediana)]
        der=[y for y in p1 if y != pivot and not (self.compararNodos(pivot,y,p1,p2,marcados,losEjesDe,mediana))]
        return self.qsort(izq,p2,marcados,losEjesDe,mediana) + [pivot] + self.qsort(der,p2,marcados,losEjesDe, mediana)
    


    def calcularMediana(self,x,losEjesDe,indice,otros):
        lista=[0]*len(otros)
        for each in losEjesDe[x]:
            #print indice[each]
            lista[indice[each]]=1
        ordenado=[]
        for i in range(len(lista)):
            if lista[i]==1:
                ordenado.append(i)
        if ordenado == []:
            return 0
        if len(ordenado) % 2 ==1:
            return ordenado[len(ordenado)/2]
        else:
            #print ordenado
            return (ordenado[len(ordenado)/2] + ordenado[(len(ordenado)-1)/2]) / 2
                
        

