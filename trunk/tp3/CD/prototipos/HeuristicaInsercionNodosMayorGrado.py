# Heuristica de agregar nodos de a uno y a acomodarlos
from GrafoBipartito import ResolvedorConstructivo, Dibujo, GrafoBipartito
from Dibujador import DibujadorGrafoBipartito
from GeneradorGrafos import generarGrafoBipartitoAleatorio, generarDibujoAleatorio
from sets import *

class HeuristicaInsercionNodosMayorGrado(ResolvedorConstructivo):
    def resolver(self, alfa=1):
        d = self.dibujo
        g = self.dibujo.g

        res1 = d.l1[:]
        res2 = d.l2[:]
        movilesEnV1 = [x for x in g.p1 if not x in d.l1] # los moviles de V1
        movilesEnV2 = [x for x in g.p2 if not x in d.l2] # los moviles de V2

        dibujo = Dibujo(g,res1[:],res2[:])

        while(movilesEnV1 != [] or movilesEnV2 != []):
            if movilesEnV1 != [] :
                v = movilesEnV1.pop(self._indiceMayorGrado(movilesEnV1, movilesEnV2, dibujo, alfa))
                #print 'v en v1', v
                dibujo = self._insertarNodo(v, res1, True, dibujo)
                res1 = dibujo.l1[:]
            if movilesEnV2 != [] :
                v = movilesEnV2.pop(self._indiceMayorGrado(movilesEnV2, movilesEnV1, dibujo, alfa))
                #print 'v en v2', v
                dibujo = self._insertarNodo(v, res2, False, dibujo)
                res2 = dibujo.l2[:]


        # ahora intento mejorar el resultado con un sort loco por cruces entre pares de nodos
        for i in range(len(res1)-1):
            ejesDe = {}
            v1 = res1[i]
            v2 = res1[i+1]
            if v1 not in d.l1 or v2 not in d.l1:    # verifico que v1 y v2 se puedan mover
                ejesDe[v1] = [x[1] for x in dibujo.g.ejes if x[0] == v1]
                ejesDe[v2] = [x[1] for x in dibujo.g.ejes if x[0] == v2]
                
                if self._crucesEntre(v1, v2, res1, res2, ejesDe) > self._crucesEntre(v2, v1, res1, res2, ejesDe):
                    res1[i] = v2
                    res1[i+1] = v1
                    dibujo = Dibujo(g, res1, res2)

        
        return dibujo

    def _indiceMayorGrado(self, movilesEnVi, movilesEnVj, dibujo, alfa):
        indiceMayor = 0
        ejesMayor = [x for x in dibujo.g.ejes if (x[0] == movilesEnVi[0] and x[1] not in movilesEnVj) or (x[1] == movilesEnVi[0] and x[0] not in movilesEnVj)]
        for i in range(len(movilesEnVi)):
            ejesIesimo = [x for x in dibujo.g.ejes if (x[0] == movilesEnVi[i] and x[1] not in movilesEnVj) or (x[1] == movilesEnVi[i] and x[0] not in movilesEnVj)]
            if len(ejesIesimo) > len(ejesMayor)*alfa:
                indiceMayor = i
                ejesMayor = ejesIesimo

        return indiceMayor

    def _insertarNodo(self, v, Vi, agregoEnV1, dibujo):
        g = self.dibujo.g
        aux = Vi[:]
        aux.insert(0, v)
        if agregoEnV1:
            mejorDibujo = Dibujo(g, aux[:], dibujo.l2)
        else:
            mejorDibujo = Dibujo(g, dibujo.l1, aux[:])

        crucesMejorDibujo = mejorDibujo.contarCruces()

        for i in range(len(Vi)):
            aux.remove(v)
            aux.insert(i + 1, v)
            if(agregoEnV1):
                dibujoCandidato = Dibujo(g, aux[:], dibujo.l2)
            else:
                dibujoCandidato = Dibujo(g, dibujo.l1, aux[:])

            crucesCandidato = dibujoCandidato.contarCruces()
            #print 'crucesCandidato', crucesCandidato
            #print 'crucesMejorDibujo', crucesMejorDibujo
            if crucesCandidato < crucesMejorDibujo :
                mejorDibujo = dibujoCandidato
                crucesMejorDibujo = crucesCandidato
        #print 'mejorDibujo', mejorDibujo
        #print 'cruces posta', mejorDibujo._contarCruces()
        return mejorDibujo

    def _crucesEntre(self,x,y,p1,p2,losEjesDe):
         indiceX = p1.index(x)
         indiceY = p1.index(y)
         acum = 0
         for each in losEjesDe[x]:
             indiceEach = p2.index(each)
             for each2 in losEjesDe[y]:
                  if indiceEach > p2.index(each2):
                     acum += 1
         return acum

if __name__ == '__main__':
    p1 = Set([1,2,3,4])
    p2 = Set([5,6,7,8])
    l1 = [2,4]
    l2 = [6,7,8]
    ejes = Set([(1,7), (2,5), (2,8), (3,6), (3,7), (3,8), (4,8)])
    dib = Dibujo(GrafoBipartito(p1,p2,ejes), l1, l2)
#    DibujadorGrafoBipartito(dib).grabar('dibujo.svg')
    resultado = HeuristicaInsercionNodosMayorGrado(dib).resolver(1)
    DibujadorGrafoBipartito(resultado).grabar('resultado.svg')
