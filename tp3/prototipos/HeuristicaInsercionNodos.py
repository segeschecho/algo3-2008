# Heuristica de agregar nodos de a uno y a acomodarlos
from GrafoBipartito import ResolvedorConstructivo, Dibujo
from Dibujador import DibujadorGrafoBipartito
from GeneradorGrafos import generarGrafoBipartitoAleatorio, generarDibujoAleatorio

class HeuristicaEmilio(ResolvedorConstructivo):

    def resolver(self):
        d = self.dibujo
        g = self.dibujo.g
        res1 = d.l1
        res2 = d.l2
        movilesEnV1 = [x for x in g.p1 if not x in d.l1] # los moviles de V1
        movilesEnV2 = [x for x in g.p2 if not x in d.l2] # los moviles de V2
        print 'noMovilesV1 =', res1
        print 'noMovilesV2 =', res2
        print 'movilesEnV1 =', movilesEnV1
        print 'movilesEnV2 =', movilesEnV2

        for v in movilesEnV1:
            dibujo = self._insertarNodo(v, res1, True)
        print 'res1 =', res1

        for v in movilesEnV2:
            dibujo = self._insertarNodo(v, res2, False)
        print 'res2 =', res2
        
        return dibujo

    def _insertarNodo(self, v, Vi, agregoEnV1):
        Vi.insert(0, v)
        aux = Vi
        if(agregoEnV1):
            mejorDibujo = Dibujo(g, Vi, d.l2)
        else:
            mejorDibujo = Dibujo(g, d.l1, Vi)

        crucesMejorDibujo = mejorDibujo.contarCruces()

        for i in range(len(Vi)):
            aux.remove(v)
            aux.insert(i + 1, v)
            if(agregoEnV1):
                dibujoCandidato = Dibujo(g, aux, d.l2)
            else:
                dibujoCandidato = Dibujo(g, d.l1, aux)

            crucesCandidato = dibujoCandidato.contarCruces()
            if crucesCandidato < crucesMejorDibujo :
                Vi = aux
                mejorDibujo = dibujoCandidato
                crucesMejorDibujo = crucesCandidato

        return mejorDibujo
#        crucesMejorPos = self._contarCruces(v, Vi, 0)
        
#        for i in range(len(Vi) + 1):
#            crucesActual = self._contarCruces(v, Vi, i)
#            print 'Cruces de', v, 'en la posicion', i, '=', crucesActual
#            if crucesActual < crucesMejorPos:
#                crucesMejorPos = crucesActual
#                mejorPos = i

#    def _contarCruces(self,v, Vi, pos): 
#        ejes = self.dibujo.g.ejes

#        ejesDeV = [x for x in ejes if (x[0] == v or  x[1] == v)]
#        res = 0
#        for e in [x for x in ejes if not x in ejesDeV]:
#            for ev in ejesDeV:
#                if (e[0] > ev[0] and e[1] < ev[1]) or (e[0] < ev[0] and e[1] > ev[1]):
#                    res = res + 1
#        return res

if __name__ == '__main__':
    g = generarGrafoBipartitoAleatorio(2,2,3)
    print 'nodos =', g.p1
    print 'nodos =', g.p2
    print 'ejes =', g.ejes
    d = generarDibujoAleatorio(g,1,1)
    resultado = HeuristicaEmilio(d).resolver()
    DibujadorGrafoBipartito(resultado).grabar('dibujo.svg')
