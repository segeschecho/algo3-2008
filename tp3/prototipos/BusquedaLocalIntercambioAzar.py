import random
from HeuristicaInsercionEjes import *
import psyco
psyco.full()
class busquedaLocalIntercambio:
    
    def swapValido(self,i,j,l,marcados):
        if i in marcados:
            if j in marcados:
                return False
            else:
                k = marcados.index(i)
                indAnterior = -1
                indSiguiente = len(l)+1
                if k != 0:
                   indAnterior = l.index(marcados[k-1])
                if k != len(marcados)-1:
                   indSiguiente = l.index(marcados[k+1])
                return indAnterior < k and k < indSiguiente
        elif j not in marcados:
            return True
        else:
            return self.swapValido(j,i,l,marcados)
            
    def mejorar(self,dibujo,marcados1,marcados2,losEjesDe):
        #buscamos la vecindad
        vecindad = []
        ejes = list(dibujo.g.ejes)
        
        for i in range(len(dibujo.l1)):
            each = dibujo.l1[i]
            for j in range(i,len(dibujo.l1)):
                each2=dibujo.l1[j]
                if self.swapValido(each,each2,dibujo.l1,marcados1):
                    if each in marcados1 or each2 in marcados1:
                        print (each,each2)
                    vecindad.append((each,each2))
        for i in range(len(dibujo.l2)):
            each = dibujo.l2[i]
            for j in range(i,len(dibujo.l2)):
                each2=dibujo.l2[j]
                if self.swapValido(each,each2,dibujo.l2,marcados2):
                    vecindad.append((each,each2))
        cruces = contadorDeCruces(dibujo.l1,dibujo.l2,losEjesDe)
        pos = None
        for each in vecindad:
            #esto se puede saber por el valor de each[0]
            #determino en q li eesta y hago swap
            if each[0] in dibujo.l1:
                donde = 0
                i = dibujo.l1.index(each[0])
                j = dibujo.l1.index(each[1])
                dibujo.l1[i]=each[1]
                dibujo.l1[j] = each[0]
            else:
                donde = 1
                i = dibujo.l2.index(each[0])
                j = dibujo.l2.index(each[1])
                dibujo.l2[i]=each[1]
                dibujo.l2[j] = each[0]
            #me fijo la cantidad de cruces actual, luego de swapear
            actual = contadorDeCruces(dibujo.l1,dibujo.l2,losEjesDe)
            #si mejora me la guardo 
            if actual < cruces:
                cruces = actual
                pos = (i,j,each[0],each[1],donde)
                #pos tiene indices, valores, y q particion
            if donde == 0:
               dibujo.l1[i]=each[0]
               dibujo.l1[j] = each[1]
            else:
                dibujo.l2[i]=each[0]
                dibujo.l2[j] = each[1]
        if pos != None:
            if pos[4] == 0:
                dibujo.l1[pos[0]] = pos[3]
                dibujo.l1[pos[1]] = pos[2]
                
            else:
                dibujo.l2[pos[0]] = pos[3]
                dibujo.l2[pos[1]] = pos[2]
            #se hace return del nuevo dibujo y True si es que hubo cambios
            return (Dibujo(dibujo.g,dibujo.l1,dibujo.l2),True)
        return (dibujo,False)

if __name__ == '__main__':
   g = generarGrafoBipartitoAleatorio(13,13,47)
   print 'nodos =', g.p1
   print 'nodos =', g.p2
   print 'ejes =', g.ejes
   ejes = g.ejes
   dib = generarDibujoAleatorio(g,20,40)
   marcadosl1 = dib.l1[:]
   marcadosl2 = dib.l2[:]
   resultado = HeuristicaInsercionEjes(dib).resolver()
   print resultado.contarCruces()
   DibujadorGrafoBipartito(resultado).grabar('sinLocal.svg')
   losEjesDe = {}
   for each in dib.l1+dib.l2:
       losEjesDe[each] = []
   for each in ejes:
        losEjesDe[each[0]].append(each[1])
        losEjesDe[each[1]].append(each[0])
   caca = busquedaLocalIntercambio().mejorar(resultado,marcadosl1,marcadosl2,losEjesDe)
   i=0
   
   while(caca[1]):
       print "mejora",contadorDeCruces(resultado.l1,resultado.l2,losEjesDe)
       resultado = caca[0]
       caca = busquedaLocalIntercambio().mejorar(resultado,marcadosl1,marcadosl2,losEjesDe)
       if caca[1]:
           i=0
       else:
           i+=1
   resultado=caca[0]
   print contadorDeCruces(resultado.l1,resultado.l2,losEjesDe)
   DibujadorGrafoBipartito(resultado).grabar('Local.svg')
