from GrafoBipartito import *
from GeneradorGrafos import *
from Dibujador import *
# grafo: todos los nodos y ejes, p1 p2 estaRel(v,u)
#dibujo: l1, l2 los nodos que no se pueden mover
class HeuristicaInsercionEjes (ResolvedorConstructivo):
            
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
   
   
    # heuristica de inserccion de nodos
    # alfa = 1 se escojen los ejes de manera de poner los q tienen un extremo adentro
    # alfa != 1 se eligen al azar
    def resolver(self,marcados1=None,marcados2=None,nodosAponer1 = None, nodosAponer2=None, p1Entrada=None,p2Entrada=None,alfa=1):
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
       #print marcadosl1
       #print marcadosl2
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
           p1Parcial = marcadosl1[:]
       else:
           p1Parcial = p1Entrada
       if p2Entrada == None:
           p2Parcial = marcadosl2[:]
       else:
           p2Parcial = p2Entrada    

       #agarro los ejes del grafo
       ejes = list(grafo.ejes)
       #estos son los q ya meti y q tengo q considerar para armar el grafo
       ejesPuestos = [ (x,y) for (x,y) in ejes if (x in marcadosl1 and y in marcadosl2) ]
       #separo los q todavia no puse (Porq tienen algun nodo q no meti)
       ejesSinPoner = [(x,y) for (x,y) in ejes if (x in p1Parcial or y in p2Parcial) and (x,y) not in ejesPuestos]
       ejesSinPoner += [(x,y) for (x,y) in ejes if (x in v1 and y in v2)]
       #cruces=self.contarCruces(p1Parcial,p2Parcial,ejesPuestos)
       losEjesDe ={}
       #lista de adyacencia del grafo
       for each in (p1Parcial+p2Parcial+v1+v2):
           losEjesDe[each]=[]
       #solo pongo los ejes de los nodos fijos
       for (x,y) in ejesPuestos:
           losEjesDe[x]+=[y]
           losEjesDe[y]+=[x]
       #puesto me va a permitir saber si el nodo ya lo puse
       #por lo cual tengo q sacarlo y reinsertar
       #o es la primera vez que lo pongo
       puesto = {}
       for each in v1+v2:
           puesto[each] = False
       for each in p2Parcial + p1Parcial:
           puesto[each] = True
       #indices de los nodos en su pi correspondiente
       indice1 = {}
       indice2 = {}
       for par in range(len(ejesSinPoner)):
           #caso en el que no hay q elegir al azar
           if alfa == 1:
               each = ejesSinPoner[par]
           else:
                each = random.choice(ejesSinPoner)
                ejesSinPoner.remove(each)
           (x,y) = each
           cantCruces = None
           Pos = (None, None)
           #si estaba puesto lo saco, sino lo marco como q apartir de ahora
           #ya esta puesto
           if puesto[x]:
               p1Parcial.remove(x)
           else:
               puesto[x] = True
           if puesto[y]:
               p2Parcial.remove(y)
           else:
               puesto[y] = True
           #pongo el nuevo eje   
           ejesPuestos.append((x,y))
           losEjesDe[x].append(y)
           losEjesDe[y].append(x)
           #obtengo entre que nodos puedo meter a x y a y
           rangoi = self._rango(x,p1Parcial,marcadosl1)
           rangoj = self._rango(y,p2Parcial,marcadosl2)
           i1 = rangoi[0]
           j1 = rangoj[0]
           #lo meto en el primer lugar posible
           p1Parcial.insert(i1,x)
           pos = (i1,j1)
           p2Parcial.insert(j1,y)
           
           for i in range(len(p1Parcial)):
               indice1[p1Parcial[i]] = i
           for i in range(len(p2Parcial)):
               indice2[p2Parcial[i]] = i
           crucesInicial = contadorDeCruces(p1Parcial,p2Parcial,losEjesDe,indice1=indice1,indice2=indice2)
           cruces=crucesInicial
           iteracionesi = 0

           for i in rangoi:
                iteracionesj = 0

                # lo dejo en la pos i y miro todas las posiciones de p2 posibles para el nodo y
                for j in rangoj:
                       actual = cruces
##                       print "al ubicarlos asi tengo:",actual
##                       print "p1",p1Parcial
##                       print "p2",p2Parcial
                       if iteracionesj != len(rangoj) -1:
                           #lo que hacemos es contar los cruces asi como estan y swapeados para saber como
                           #cambia la cantidad de cruces
                           crucesj = crucesEntre(y,p2Parcial[j+1],p1Parcial,losEjesDe, indice2 = indice1)
                           crucesj1 = crucesEntre(p2Parcial[j+1],y,p1Parcial,losEjesDe, indice2 = indice1)
                           cruces = cruces - crucesj + crucesj1
                           #swapeo de verdad los nodos
                           auxj=p2Parcial[j]
                           p2Parcial[j] = p2Parcial[j+1]
                           p2Parcial[j+1] = auxj
                           
                       # si ponerlos en i,j me baja los cruces, actualizo
                       if cantCruces == None or actual < cantCruces:
                               cantCruces=actual
                               pos=(i,j)
                               
                       iteracionesj +=1
                       
                p2Parcial.remove(y)

                #ahora paso al nodo x a su proxima posicion
                if iteracionesi != len(rangoi) - 1:
                    p2Parcial.insert(j1,y)
                    crucesi = crucesEntre(x,p1Parcial[i+1],p2Parcial,losEjesDe,indice2=indice2)
                    crucesi1 = crucesEntre(p1Parcial[i+1],x,p2Parcial,losEjesDe,indice2=indice2)
                    cruces = crucesInicial - crucesi + crucesi1
                    crucesInicial = cruces
                    indice1[p1Parcial[i]] = i+1
                    indice1[p1Parcial[i+1]] = i
                    aux = p1Parcial[i]
                    p1Parcial[i] = p1Parcial[i+1]
                    p1Parcial[i+1] = aux
                iteracionesi += 1
           p1Parcial.remove(x)
           p1Parcial.insert(pos[0],x)
           p2Parcial.insert(pos[1],y)
           #print (x,y)
           #print p1Parcial
           #print p2Parcial
##           print "al eje ",(x,y),"lo inserte en",pos
##           print "al hacerlo el grafo tiene", cantCruces, "cruces"
##           print "p1:",p1Parcial
##           print "p2:",p2Parcial
           #aplico una mejora a la solucion dada: si crucesEntre(x,y) >= crucesEntre(y,x), es mejor intercambiarlo (solo vale para posicioes adyacentes)
       for each in v1:
            if not puesto[each]:
                p1Parcial.append(each)
       for each in v2:
            if not puesto[each]:
                p2Parcial.append(each)

       return Dibujo(grafo,p1Parcial,p2Parcial)

if __name__ == '__main__':
   g = generarGrafoBipartitoAleatorio(5,5,11)
   print 'nodos =', g.p1
   print 'nodos =', g.p2
   print 'ejes =', g.ejes
   dib = generarDibujoAleatorio(g,2,2)
   resultado = HeuristicaInsercionEjes(dib).resolver()
   print "ahora dio", resultado.contarCruces()
   DibujadorGrafoBipartito(resultado).grabar('dibujo.svg')


