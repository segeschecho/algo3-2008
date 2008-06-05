from GrafoBipartito import *
from GeneradorGrafos import *
from Dibujador import *

# grafo: todos los nodos y ejes, p1 p2 estaRel(v,u)
#dibujo: l1, l2 los nodos que no se pueden mover
class HeuristicaMediana (ResolvedorConstructivo):
    
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
        grafo = self.dibujo.g
        dibujo=self.dibujo
        #separo a los q ya estan en el dibujo (son los q tengo q manteer ordenados)
        marcadosl1 = list(self.dibujo.l1)
        print marcadosl1
        marcadosl2 = list(self.dibujo.l2)
        print marcadosl2
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
        cruces =  contarCrucesAcumTree(p1,p2,ejes)
        
        movilesV1 = [x for x in self.dibujo.g.p1 if not x in self.dibujo.l1] # los moviles de V1
        movilesV2 = [x for x in self.dibujo.g.p2 if not x in self.dibujo.l2] # los moviles de V2
        for each in range(5):
            for each in p1:
                medianasp1[each]=self.calcularMediana(each,losEjesDe,indice,p2)
            for i in range(len(p2Parcial)):
                indice[p2[i]]=i
            for i in range(len(p1Parcial)):
                indice[p1[i]]=i
            p1Aux=self.qsort2(p1,p2,movilesV1, marcadosl1,losEjesDe,medianasp1)
            crucesAux=contarCrucesAcumTree(p1Aux,p2,ejes)
            p1=p1Aux
            cruces=crucesAux
            for each in p2:
                medianasp2[each]=self.calcularMediana(each,losEjesDe,indice,p1)
            print p2
            print medianasp2
            p2Aux=self.qsort2(p2,p1,movilesV2, marcadosl2,losEjesDe,medianasp2)
            crucesAux = contarCrucesAcumTree(p1,p2Aux,ejes)
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
                    cambio=True
        for i in range(len(p2)-1):
            if p2[i] not in marcadosl2 or p2[i+1] not in marcadosl2:
                comoEsta=self.crucesEntre(p2[i],p2[i+1],p2,p1,losEjesDe)
                swapeado=self.crucesEntre(p2[i+1],p2[i],p2,p1,losEjesDe)
                if swapeado < comoEsta:
                    aux=p2[i]
                    p2[i]=p2[i+1]
                    p2[i+1]=aux
                    cambio=True
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
                    cambio=True
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
                    cambio=True
        return Dibujo(self.dibujo.g,p1,p2)

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

    def compararNodos(self,x,y,marcados,mediana):
        if x in marcados and y in marcados:
            return marcados.index(y) < marcados.index(x)
        else:
            return mediana[y] < mediana[x]

    def qsort2(self, p1, p2, moviles, noMoviles, losEjesDe, mediana):
        if len(moviles) == 0:           # caso base
            return noMoviles

        # elijo el PIVOT
        pivot = moviles[0]
        for v in moviles :
            if len(losEjesDe[pivot]) > len(losEjesDe[v]):
               pivot = v

        # divido los moviles para llamar recursivamente
        izq=[x for x in moviles if mediana[x] < mediana[pivot]]
        der=[x for x in moviles if x != pivot and mediana[x] >= mediana[pivot]]

        # ubico el PIVOT entre los no moviles
        indPivNoMov = 0
        crucesActual = contarCrucesAcumTree2(moviles,p2,losEjesDe)
        crucesMejor = crucesActual
        for i in range(len(noMoviles)) :
            crucesActual = crucesActual + contarCrucesAcumTree2(p2, [noMoviles[i], pivot],losEjesDe) -  contarCrucesAcumTree2(p2, [pivot,noMoviles[i]],losEjesDe)
            if crucesActual < crucesMejor :
                crucesMejor = crucesActual
                indPivNoMov = i + 1

        return self.qsort2(p1,p2, izq, noMoviles[0:indPivNoMov],losEjesDe,mediana) + [pivot] + self.qsort2(p1,p2,der, noMoviles[indPivNoMov:],losEjesDe, mediana)

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

if __name__ == '__main__':
    g = generarGrafoBipartitoAleatorio(6,6,10)
    print 'nodos =', g.p1
    print 'nodos =', g.p2
    print 'ejes =', g.ejes
    dib = generarDibujoAleatorio(g,2,4)
    resultado = HeuristicaMediana(dib).resolver()
    print 'cruces', resultado.contarCruces()
    print resultado.l1
    print resultado.l2
    DibujadorGrafoBipartito(resultado).grabar('dibujo.svg')        

    #g = generarGrafoBipartitoAleatorio(6,6,10)
    #print 'nodos =', g.p1
    #print 'nodos =', g.p2
    #print 'ejes =', g.ejes
    #dib = generarDibujoAleatorio(g,2,4)

    #movilesV1 = [x for x in g.p1 if not x in dib.l1] # los moviles de V1
    #movilesV2 = [x for x in g.p2 if not x in dib.l2] # los moviles de V2

    #p1Permutado = HeuristicaMediana(dib).qsort2(g.p1, g.p2, movilesV1, dib.l1[:],
    #print 'cruces', resultado.contarCruces()
    #DibujadorGrafoBipartito(resultado).grabar('dibujo.svg')