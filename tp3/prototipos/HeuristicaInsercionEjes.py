from GrafoBipartito import *
from GeneradorGrafos import *
from Dibujador import *
# grafo: todos los nodos y ejes, p1 p2 estaRel(v,u)
#dibujo: l1, l2 los nodos que no se pueden mover
class HeuristicaInsercionEjes (ResolvedorConstructivo):
    
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
                abort
            while(indice > 0):
                if (indice % 2 == 1):
                    cruces += arbol[indice+1]
                indice=(indice -1)/2
                arbol[indice]+=1
        return cruces

    #contador de cruces mediante radix sort y un accumulator tree
    #magia
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
        #radixsort de los ejes
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
                abort
            while(indice > 0):
                if (indice % 2 == 1):
                    cruces += arbol[indice+1]
                indice=(indice -1)/2
                arbol[indice]+=1
        return cruces


    def contarCruces(self,p1,p2,losEjesDe):
        cruces=0
        for each in p1:
            indice=p1.index(each)
            for i in range(indice):
                for nodo in losEjesDe[each]:
                    indice2=p2.index(nodo)
                    for tipito in losEjesDe[p1[i]]:
                            if p2.index(tipito) > indice2:
                                cruces+=1
        return cruces
        
    # establece el rango en el cual se puede insertar un nodo
    # basicamente me fijo que si el tipo esta marcado, no lo trate de poner
    # antes de su anterior y despues de su posterior
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
        acum=0
        for each in losEjesDe[x]:
            indiceEach = p2.index(each)
            for each2 in losEjesDe[y]:
                 if indiceEach > p2.index(each2):
                    acum += 1
   
        return acum
   
   
    #heuristica de inserccion de nodos   
    def resolver(self,marcados1=None,marcados2=None,nodosAponer1 = None, nodosAponer2=None, p1Entrada=None,p2Entrada=None):
       #renombres
       p1 = list(self.dibujo.g.p1)
       p2 = list(self.dibujo.g.p2)
       grafo = self.dibujo.g
       dibujo=self.dibujo
       if marcados1 == None:
       #separo a los q ya estan en el dibujo (son los q tengo q mantener ordenados)
           marcadosl1 = list(self.dibujo.l1)
       else:
           marcadosl1 = marcados1
       if marcados2 == None:
           marcadosl2 = list(self.dibujo.l2)
       else:
           marcadosl2 = marcados2
       #obtengo los que tengo que poner (los q me dieron para agregar)
       if nodosAponer1 == None:
          v1 = [x for x in p1 if x not in marcadosl1]
       else:
           v1 = nodosAponer1
       if nodosAponer2 == None: 
           v2 = [y for y in p2 if y not in marcadosl2]
       else:
           v2 = nodosAponer2
       #meto a todos los nodos en un "dibujo"
       if p1Entrada == None:
           p1Parcial = marcadosl1 + v1
       else:
           p1Parcial = p1Entrada
       if p2Entrada == None:
           p2Parcial = marcadosl2 + v2
       else:
           p2Parcial = p2Entrada    

       #agarro los ejes del grafo
       ejes = list(grafo.ejes)
       #separo los q todavia no puse (Porq tienen algun nodo q no meti)
       ejesSinPoner = [ (x,y) for (x,y) in ejes if (x in v1 or y in v2) ]
       #estos son los q ya meti y q tengo q considerar para armar el grafo
       ejesPuestos = [ (x,y) for (x,y) in ejes if (x in marcadosl1 and y in marcadosl2) ]
       #cruces=self.contarCruces(p1Parcial,p2Parcial,ejesPuestos)
       losEjesDe ={}
       #lista de adyacencia del grafo (solo los ejes puestos)
       for each in (p1Parcial+p2Parcial):
           losEjesDe[each]=[]
       for (x,y) in ejesPuestos:
           losEjesDe[x]+=[y]
           losEjesDe[y]+=[x]
       #voy poniendo de a uno los ejes

       for each in ejesSinPoner:
           (x,y) = each
           cantCruces = None
           Pos = (None, None)
           # voy a actualizar la posicion de los nodos del ejes
           p1Parcial.remove(x)
           p2Parcial.remove(y)
           #cruces = self.contarCrucesAcumTree(p1Parcial,p2Parcial,ejesPuestos)
           ejesPuestos.append((x,y))
           losEjesDe[x]+=[y]
           losEjesDe[y]+=[x]
           rangoi = self._rango(x,p1Parcial,marcadosl1)
           rangoj = self._rango(y,p2Parcial,marcadosl2)
           i1 = rangoi[0]
           j1 = rangoj[0]
           #lo meto en el lugar i
           
           p1Parcial.insert(i1,x)
           pos = (i1,j1)
           p2Parcial.insert(j1,y)
           crucesFede = self.contarCrucesAcumTree(p1Parcial,p2Parcial,ejesPuestos)
           cruces=crucesFede
           iteracionesi = 0
           #recorro todas las posiciones de p1
           for i in rangoi:
                iteracionesj = 0
                # lo dejo en la pos i y miro todas las posiciones de p1
                for j in rangoj:
                       actual = cruces
                       if iteracionesj != len(rangoj) -1:
                           crucesj = self.contarCrucesAcumTree2(p1Parcial,[y,p2Parcial[j+1]],losEjesDe)
                           crucesj1 = self.contarCrucesAcumTree2(p1Parcial,[p2Parcial[j+1],y],losEjesDe)
                           cruces = cruces - crucesj + crucesj1
                           auxj=p2Parcial[j]
                           p2Parcial[j] = p2Parcial[j+1]
                           p2Parcial[j+1] = auxj
                       # si ponerlos en i,j me baja los cruces, actualizo
                       if cantCruces == None or actual < cantCruces:
                               cantCruces=actual
                               pos=(i,j)
                       iteracionesj += 1
                aux = p1Parcial[i]
                p2Parcial.remove(y)
                if iteracionesi != len(rangoi) - 1:
                    p2Parcial.insert(j1,y)
                    crucesi = self.contarCrucesAcumTree2([x,p1Parcial[i+1]],p2Parcial,losEjesDe)
                    crucesi1 = self.contarCrucesAcumTree2([p1Parcial[i+1],x],p2Parcial,losEjesDe)
                    cruces = crucesFede - crucesi + crucesi1
                    crucesFede = cruces
                    p1Parcial[i] = p1Parcial[i+1]
                    p1Parcial[i+1] = aux
                iteracionesi += 1
           p1Parcial.remove(x)
           p1Parcial.insert(pos[0],x)
           p2Parcial.insert(pos[1],y)
           
       #aplico una mejora a la solucion dada: si crucesEntre(x,y) >= crucesEntre(y,x), es mejor intercambiarlo (solo vale para posicioes adyacentes)
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
       return Dibujo(grafo,p1Parcial,p2Parcial)

if __name__ == '__main__':
   g = generarGrafoBipartitoAleatorio(10,10,57)
   print 'nodos =', g.p1
   print 'nodos =', g.p2
   print 'ejes =', g.ejes
   dib = generarDibujoAleatorio(g,2,4)
   resultado = HeuristicaInsercionEjes(dib).resolver()
   DibujadorGrafoBipartito(resultado).grabar('dibujo.svg')


