# Heuristica de agregar nodos de a uno y a acomodarlos
from GrafoBipartito import ResolvedorConstructivo

class HeuristicaEmilio(ResolvedorConstructivo):
    def resolver(self):
        d = self.dibujo
        g = self.dibujo.g
        res1 = [x for x in g.p1 if not x in g.l1] # los no movibles de V1
        res2 = [x for x in g.p2 if not x in g.l2] # los no movibles de V2
        moviblesEnV1 = [x for x in g.l1 if not x in g.p1] # los movibles de V1
        moviblesEnV2 = [x for x in g.l2 if not x in g.p2] # los movibles de V2

        for v in moviblesEnV1:
            insertarNodo(v, res1)

        for v in moviblesEnV2:
            _insertarNodo(v, res2)

        dibujo = Dibujo(g, res1, res2)
        return dibujo

    def _insertarNodo(self,v, Vi):
        mejorPos = 0
        crucesMejorPos = _contarCruces(v, Vi, 0)
        for i in range(len(Vi)):
            crucesActual = _contarCruces(v, Vi, i)
            if crucesActual < crucesMejorPos:
                crucesMejorPos = crucesActual
                mejorPos = i

        Vi.insert(mejorSol, v)

    def _contarCruces(self,v, Vi, pos): 
        ejes = self.g.ejes

        ejesDeV = [x for x in ejes if x[0] == v |  x[1] == v]
        res = 0
        for e in ejes:
            for ev in ejesDeV:
                if (e[0]>ev[0] &  e[1]<ev[1]) | (e[0]<ev[0] &  e[1]>ev[1]):
                    res = res + 1


def main():
    

if __name__ == '__main__':
    main()