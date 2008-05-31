from GrafoBipartito import *
from GeneradorGrafos import *
from Dibujador import *
# grafo: todos los nodos y ejes, p1 p2 estaRel(v,u)
#dibujo: l1, l2 los nodos que no se pueden mover
class heuristicaFede (ResolvedorConstructivo):
 #contador de cruces mediante radix sort y un accumulator tree  
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
            z=range(anterior,siguiente)
            if z == []:
                print "error", z,pi,marcados
            assert z != []
            return z
        
 #establece los cruces entre dos nodos x e y para un dibujo dado       
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
             p1Parcial.insert(i,x)
             for j in self._rango(y,p2Parcial,marcadosl2):
                    p2Parcial.insert(j,y)
                    #nuevop1=p1Parcial[0:i]+[x]+p1Parcial[i:]
                    #nuevop2=p2Parcial[0:j]+[y]+p2Parcial[j:]
                    # TODO:
                    # a priori pareceria importar cuantos cruces me genera insertarlos en las pos i,j
                    # hay q ver como puedo aprovechar esto para que ande mas rapido
                    actual = self.contarCrucesAcumTree(p1Parcial,p2Parcial,ejesPuestos)
                    p2Parcial.remove(y)
                    if cantCruces == None or actual < cantCruces:
                            cantCruces=actual
                            pos=(i,j)
             p1Parcial.remove(x)


        p1Parcial.insert(pos[0],x)
        p2Parcial.insert(pos[1],y)
    cruces=self.contarCruces(p1Parcial,p2Parcial,losEjesDe)
    for i in range(len(p1Parcial)-1):
        if p1Parcial[i] not in marcadosl1 or p1Parcial[i+1] not in marcadosl1:
            comoEsta=self.crucesEntre(p1Parcial[i],p1Parcial[i+1],p1Parcial,p2Parcial,losEjesDe)
            swapeado=self.crucesEntre(p1Parcial[i+1],p1Parcial[i],p1Parcial,p2Parcial,losEjesDe)
            if swapeado < comoEsta:
                aux=p1Parcial[i]
                p1Parcial[i]=p1Parcial[i+1]
                p1Parcial[i+1]=aux
    for i in range(len(p2Parcial)-1):
        if p2Parcial[i] not in marcadosl2 or p2Parcial[i+1] not in marcadosl2:
            comoEsta=self.crucesEntre(p2Parcial[i],p2Parcial[i+1],p2Parcial,p1Parcial,losEjesDe)
            swapeado=self.crucesEntre(p2Parcial[i+1],p2Parcial[i],p2Parcial,p1Parcial,losEjesDe)
            if swapeado < comoEsta:
                aux=p2Parcial[i]
                p2Parcial[i]=p2Parcial[i+1]
                p2Parcial[i+1]=aux
    listita = range(1,len(p1Parcial))
    listita.reverse()
    for i in listita:
        if p1Parcial[i] not in marcadosl1 or p1Parcial[i-1] not in marcadosl1:
            comoEsta=self.crucesEntre(p1Parcial[i-1],p1Parcial[i],p1Parcial,p2Parcial,losEjesDe)
            swapeado=self.crucesEntre(p1Parcial[i],p1Parcial[i-1],p1Parcial,p2Parcial,losEjesDe)
            if swapeado < comoEsta:
                aux=p1Parcial[i]
                p1Parcial[i]=p1Parcial[i-1]
                p1Parcial[i-1]=aux
    listita = range(1,len(p2Parcial))
    listita.reverse()
    for i in listita:
        if p2Parcial[i] not in marcadosl2 or p2Parcial[i-1] not in marcadosl2:
            comoEsta=self.crucesEntre(p2Parcial[i-1],p2Parcial[i],p2Parcial,p1Parcial,losEjesDe)
            swapeado=self.crucesEntre(p2Parcial[i],p2Parcial[i-1],p2Parcial,p1Parcial,losEjesDe)
            if swapeado < comoEsta:
                aux=p2Parcial[i]
                p2Parcial[i]=p2Parcial[i-1]
                p2Parcial[i-1]=aux
    print cruces
    print self.contarCrucesAcumTree(p1Parcial,p2Parcial,ejes)
    print self.contarCruces(p1Parcial,p2Parcial,losEjesDe)
    print "metodo loquino", self.contarCrucesAcumTree(p1Parcial,p2Parcial,ejes)
    return Dibujo(grafo,p1Parcial,p2Parcial)

 def grafoDenso(self):
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
    ejes = list(grafo.ejes)
    #genero todos los ejes del mundo :D
    todosLosEjes=[]
    for each in p1Parcial:
        for each1 in p2Parcial:
            todosLosEjes.append((each,each1))
    ejesASacar=[x for x in todosLosEjes if x not in ejes]
    cruces=self.contarCrucesAcumTree(p1Parcial,p2Parcial,todosLosEjes)
    print "al incicio " ,cruces
    for each in ejesASacar:
        (x,y) = each
        cantCruces = None
        Pos = (None, None)
        p1Parcial.remove(x)
        p2Parcial.remove(y)
        todosLosEjes.remove((x,y))
        for i in self._rango(x,p1Parcial,marcadosl1):
             p1Parcial.insert(i,x)
             for j in self._rango(y,p2Parcial,marcadosl2):
                    #nuevop1=p1Parcial[0:i]+[x]+p1Parcial[i:]
                    #nuevop2=p2Parcial[0:j]+[y]+p2Parcial[j:]
                    p2Parcial.insert(j,y)
                    actual = self.contarCrucesAcumTree(p1Parcial,p2Parcial,todosLosEjes)
                    p2Parcial.remove(y)
                    if cantCruces == None or actual < cantCruces:
                            cantCruces=actual
                            pos=(i,j)
             p1Parcial.remove(x)

        p1Parcial.insert(pos[0],x)
        p2Parcial.insert(pos[1],y)
    cruces=self.contarCrucesAcumTree(p1Parcial,p2Parcial,todosLosEjes)
    print "el denso logro",cruces
    losEjesDe={}
    for each in p1Parcial:
        losEjesDe[each]=[]
    for each in p2Parcial:
        losEjesDe[each]=[]
    for each in ejes:
        losEjesDe[each[0]].append(each[1])
        losEjesDe[each[1]].append(each[0])

    for i in range(len(p1Parcial)-1):
        if p1Parcial[i] not in marcadosl1 or p1Parcial[i+1] not in marcadosl1:
            comoEsta=self.crucesEntre(p1Parcial[i],p1Parcial[i+1],p1Parcial,p2Parcial,losEjesDe)
            swapeado=self.crucesEntre(p1Parcial[i+1],p1Parcial[i],p1Parcial,p2Parcial,losEjesDe)
            if swapeado < comoEsta:
                aux=p1Parcial[i]
                p1Parcial[i]=p1Parcial[i+1]
                p1Parcial[i+1]=aux
    for i in range(len(p2Parcial)-1):
        if p2Parcial[i] not in marcadosl2 or p2Parcial[i+1] not in marcadosl2:
            comoEsta=self.crucesEntre(p2Parcial[i],p2Parcial[i+1],p2Parcial,p1Parcial,losEjesDe)
            swapeado=self.crucesEntre(p2Parcial[i+1],p2Parcial[i],p2Parcial,p1Parcial,losEjesDe)
            if swapeado < comoEsta:
                aux=p2Parcial[i]
                p2Parcial[i]=p2Parcial[i+1]
                p2Parcial[i+1]=aux
    listita = range(1,len(p1Parcial))
    listita.reverse()
    for i in listita:
        if p1Parcial[i] not in marcadosl1 or p1Parcial[i-1] not in marcadosl1:
            comoEsta=self.crucesEntre(p1Parcial[i-1],p1Parcial[i],p1Parcial,p2Parcial,losEjesDe)
            swapeado=self.crucesEntre(p1Parcial[i],p1Parcial[i-1],p1Parcial,p2Parcial,losEjesDe)
            if swapeado < comoEsta:
                aux=p1Parcial[i]
                p1Parcial[i]=p1Parcial[i-1]
                p1Parcial[i-1]=aux
    listita = range(1,len(p2Parcial))
    listita.reverse()
    for i in listita:
        if p2Parcial[i] not in marcadosl2 or p2Parcial[i-1] not in marcadosl2:
            comoEsta=self.crucesEntre(p2Parcial[i-1],p2Parcial[i],p2Parcial,p1Parcial,losEjesDe)
            swapeado=self.crucesEntre(p2Parcial[i],p2Parcial[i-1],p2Parcial,p1Parcial,losEjesDe)
            if swapeado < comoEsta:
                aux=p2Parcial[i]
                p2Parcial[i]=p2Parcial[i-1]
                p2Parcial[i-1]=aux
    print "se mejoro a :", self.contarCrucesAcumTree(p1Parcial,p2Parcial,todosLosEjes)
    return Dibujo(grafo,p1Parcial,p2Parcial)

a = GrafoBipartito(Set([1,2,3,4,5]),Set([6,7,8]),Set([(1,8),(2,6),(3,7),(4,7),(4,6),(5,8)]))
dib=Dibujo(a,[1,2,3],[6])
f = heuristicaFede(dib)
dibujo = f.resolver()
print "cruces gonza",dibujo.contarCruces()
print(dibujo.l1)
print(dibujo.l2)
g = generarGrafoBipartitoAleatorio(60,6,22)
d = generarDibujoAleatorio(g,3,2)
f = heuristicaFede(d)
dibujo=f.resolver()
dibujo=f.grafoDenso()
#f.heuristica2()
print(dibujo.l1)
print(dibujo.l2)
print  "cruces gonza", dibujo.contarCruces()
dibu = DibujadorGrafoBipartito( dibujo)
dibu.grabarYMostrar()

              
