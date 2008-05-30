from GrafoBipartito import *
from GeneradorGrafos import *
from Dibujador import *
# grafo: todos los nodos y ejes, p1 p2 estaRel(v,u)
#dibujo: l1, l2 los nodos que no se pueden mover
class heuristicaFede (ResolvedorConstructivo):
 #contador de cruces mediante radix sort y un accumulator tree  
 def contarCrucesAcumTree(self,p1,p2,ejes):
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
    while primerIndice < len(b2):
        primerIndice *= 2
    arbol = [0]*(2*primerIndice - 1)
    primerIndice -=1

    cruces=0
    for i in range(len(sur)):
        indice=sur[i]+primerIndice
        arbol[indice]+=1
        while(indice > 0):
            if (indice % 2 == 1):
                cruces += arbol[indice+1]
            indice=(indice -1)/2
            arbol[indice]+=1
    #print "crucess",cruces
    return cruces

 #contador deprecado de cruces
 #todavia no lo saque del todo por eso no lo borro
 def contarCruces(self,p1,p2,losEjesDe):
     cruces=0
     for each in p1:
         indice=p1.index(each)
         for i in range(indice):
             for nodo in losEjesDe[each]:
                 indice2=p2.index(nodo)
                 #if( indice2 <= indice):
                 for tipito in losEjesDe[p1[i]]:
                         if p2.index(tipito) > indice2:
                             cruces+=1
     return cruces
     
 #establece el rango en el cual se puede insertar un nodo
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
            x=range(anterior,siguiente)
            assert x != []
            return x
        
 #establece los cruces entre dos nodos x e y para un dibujo dado       
 def crucesEntre(self,x,y,p1,p2,losEjesDe):
     indiceX = p1.index(x)
     indiceY = p1.index(y)
     if indiceX < indiceY:
         aux=indiceX
         indiceX=indiceY
         indiceY=indiceX
     acum=0
     for each in losEjesDe[x]:
         indiceEach = p2.index(each)
         for each2 in losEjesDe[y]:
             if indiceEach >= indiceY and indiceEach < p2.index(each2):
                 acum += 1
             if indiceEach < indiceY and indiceEach > p2.index(each2):
                 acum += 1
     return acum

 #heuristica berreta
 #todavia no anda del todo
 def heuristica2(self):
    p1 = list(self.dibujo.g.p1)
    p2 = list(self.dibujo.g.p2)
    grafo = self.dibujo.g
    dibujo=self.dibujo
    #separo a los q ya estan en el dibujo (son los q tengo q manteer ordenados)
    marcadosl1 = list(self.dibujo.l1)
    print "marcados",marcadosl1
    marcadosl2 = list(self.dibujo.l2)
    losEjesDe ={}
    ejes = list(grafo.ejes)
    for each in p1+p2:
        losEjesDe[each]=[]
    for each in ejes:
        losEjesDe[each[0]]+=[each[1]]
        losEjesDe[each[1]]+=[each[0]]
    p1=self.qsort(p1,p2,losEjesDe,marcadosl1)
    p2=self.qsort(p2,p1,losEjesDe,marcadosl2)
    p2Parcial=p2
    p1Parcial=p1
    cruces=self.contarCruces(p1Parcial,p2Parcial,losEjesDe)
    print cruces
    for i in range(len(p2)-1):
        if p2Parcial[i] not in marcadosl2 or p2Parcial[i+1] not in marcadosl2:
            p2Loco = p2Parcial[:]
            p2Loco[i] = p2Parcial[i+1]
            p2Loco[i+1]=p2Parcial[i]
            crucesActual = self.contarCruces(p2Loco,p1Parcial,losEjesDe)
            if crucesActual < cruces:
                cruces=crucesActual
                p2Parcial=p2Loco
    for i in range(len(p1Parcial)-1):
        if p1Parcial[i] not in marcadosl1 or p1Parcial[i+1] not in marcadosl1:
            p1Loco = p1Parcial[:]
            p1Loco[i] = p1Parcial[i+1]
            p1Loco[i+1]=p1Parcial[i]
            crucesActual = self.contarCruces(p1Loco,p2Parcial,losEjesDe)
            if crucesActual < cruces:
                cruces=crucesActual
                p1Parcial=p1Loco
    for i in range(len(p2)-1):
        if p2Parcial[i] not in marcadosl2 or p2Parcial[i+1] not in marcadosl2:
            p2Loco = p2Parcial[:]
            p2Loco[i] = p2Parcial[i+1]
            p2Loco[i+1]=p2Parcial[i]
            crucesActual = self.contarCruces(p2Loco,p1Parcial,losEjesDe)
            if crucesActual < cruces:
                cruces=crucesActual
                p2Parcial=p2Loco
    for i in range(len(p1Parcial)-1):
        if p1Parcial[i] not in marcadosl1 or p1Parcial[i+1] not in marcadosl1:
            p1Loco = p1Parcial[:]
            p1Loco[i] = p1Parcial[i+1]
            p1Loco[i+1]=p1Parcial[i]
            crucesActual = self.contarCruces(p1Loco,p2Parcial,losEjesDe)
            if crucesActual < cruces:
                cruces=crucesActual
                p1Parcial=p1Loco
    print "cosa loca", self.contarCruces(p1Parcial,p2Parcial,losEjesDe)
    
 def qsort(self,p1,p2,losEjesDe,marcadosl1):
     if len(p1)==0 or len(p1) == 1:
         return p1[:]
     x=[k for k in p1 if self.crucesEntre(p1[len(p1)/2],k,p1,p2,losEjesDe) < self.crucesEntre(k,p1[len(p1)/2],p1,p2,losEjesDe)]
     y=[k for k in p1 if k != p1[len(p1)/2] and self.crucesEntre(p1[len(p1)/2],k,p1,p2,losEjesDe) >= self.crucesEntre(k,p1[len(p1)/2],p1,p2,losEjesDe)]
     if p1[len(p1)/2] in marcadosl1:
         indice=marcadosl1.index(p1[len(p1)/2])
         for i in range(indice):
             if marcadosl1[i] in y:
                 y.remove(marcadosl1[i])
                 x.append(marcadosl1[i])
         for i in range(indice+1,len(marcadosl1)):
             if marcadosl1[i] in x:
                 x.remove(marcadosl1[i])
                 y.append(marcadosl1[i])
     return self.qsort(x,p2,losEjesDe,marcadosl1)+[p1[len(p1)/2]]+self.qsort(y,p2,losEjesDe,marcadosl1)

 #heuristica de inserccion de nodos   
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
    #separo los q todavia no puse (Porq tienen algun nodo q no meti)
    ejesSinPoner = [ (x,y) for (x,y) in ejes if (x in v1 or y in v2) ]
    #estos son los q ya meti y q tengo q considerar para armar el grafo
    ejesPuestos = [ (x,y) for (x,y) in ejes if (x in marcadosl1 and y in marcadosl2) ]
    #cruces=self.contarCruces(p1Parcial,p2Parcial,ejesPuestos)
    print "incialmente: ",self.contarCrucesAcumTree(p1,p2,ejes)
    losEjesDe ={}
    for each in (p1Parcial+p2Parcial):
        losEjesDe[each]=[]
    for (x,y) in ejesPuestos:
        losEjesDe[x]+=[y]
        losEjesDe[y]+=[x]
    for each in ejesSinPoner:
        (x,y) = each
        cantCruces = None
        Pos = (None, None)
        p1Parcial.remove(x)
        p2Parcial.remove(y)
        ejesPuestos.append((x,y))
        losEjesDe[x]+=[y]
        losEjesDe[y]+=[x]
        for i in self._rango(x,p1Parcial,marcadosl1):
             for j in self._rango(y,p2Parcial,marcadosl2):
                    nuevop1=p1Parcial[0:i]+[x]+p1Parcial[i:]
                    nuevop2=p2Parcial[0:j]+[y]+p2Parcial[j:]
                    actual = self.contarCrucesAcumTree(nuevop1,nuevop2,ejesPuestos)
                    if cantCruces == None or actual < cantCruces:
                            cantCruces=actual
                            pos=(i,j)


        p1Parcial.insert(pos[0],x)
        p2Parcial.insert(pos[1],y)
    cruces=self.contarCruces(p1Parcial,p2Parcial,losEjesDe)
    print cruces
    #Aca hacemos un par de pasadas para ver si podemos mejorar un poco la cosa
    for i in range(len(p2Parcial)-1):
        if p2Parcial[i] not in marcadosl2 or p2Parcial[i+1] not in marcadosl2:
            p2Loco = p2Parcial[:]
            p2Loco[i] = p2Parcial[i+1]
            p2Loco[i+1]=p2Parcial[i]
            crucesActual = self.contarCruces(p2Loco,p1Parcial,losEjesDe)
            if crucesActual < cruces:
                cruces=crucesActual
                p2Parcial=p2Loco
    for i in range(len(p1Parcial)-1):
        if p1Parcial[i] not in marcadosl1 or p1Parcial[i+1] not in marcadosl1:
            p1Loco = p1Parcial[:]
            p1Loco[i] = p1Parcial[i+1]
            p1Loco[i+1]=p1Parcial[i]
            crucesActual = self.contarCrucesAcumTree(p1Loco,p2Parcial,ejes)
            if crucesActual < cruces:
                cruces=crucesActual
                p1Parcial=p1Loco
    print self.contarCrucesAcumTree(p1Parcial,p2Parcial,ejes)
    for i in range(len(p2Parcial)-1):
        if p2Parcial[i] not in marcadosl2 or p2Parcial[i+1] not in marcadosl2:
            p2Loco = p2Parcial[:]
            p2Loco[i] = p2Parcial[i+1]
            p2Loco[i+1]=p2Parcial[i]
            crucesActual = self.contarCruces(p2Loco,p1Parcial,losEjesDe)
            if crucesActual < cruces:
                cruces=crucesActual
                p2Parcial=p2Loco
    for i in range(len(p1Parcial)-1):
        if p1Parcial[i] not in marcadosl1 or p1Parcial[i+1] not in marcadosl1:
            p1Loco = p1Parcial[:]
            p1Loco[i] = p1Parcial[i+1]
            p1Loco[i+1]=p1Parcial[i]
            crucesActual = self.contarCrucesAcumTree(p1Loco,p2Parcial,ejes)
            if crucesActual < cruces:
                cruces=crucesActual
                p1Parcial=p1Loco
    print self.contarCrucesAcumTree(p1Parcial,p2Parcial,ejes)
    print self.contarCruces(p1Parcial,p2Parcial,losEjesDe)
    print "metodo loquino", self.contarCrucesAcumTree(p1Parcial,p2Parcial,ejes)
    return Dibujo(grafo,p1Parcial,p2Parcial)
        
         
a = GrafoBipartito(Set([1,2,3,4,5]),Set([6,7,8]),Set([(1,8),(2,6),(3,7),(4,7),(4,6),(5,8)]))
dib=Dibujo(a,[1,2,3],[6])
f = heuristicaFede(dib)
dibujo = f.resolver()
print "cruces gonza",dibujo.contarCruces()
print(dibujo.l1)
print(dibujo.l2)
g = generarGrafoBipartitoAleatorio()
d = generarDibujoAleatorio(g)
f = heuristicaFede(d)
dibujo=f.resolver()
#f.heuristica2()
print(dibujo.l1)
print(dibujo.l2)
print  "cruces gonza", dibujo.contarCruces()
dibu = DibujadorGrafoBipartito( dibujo)
dibu.grabarYMostrar()

              
