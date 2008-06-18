from GrafoBipartito import GrafoBipartito, Dibujo
import Dibujador
from sets import Set

class ParserDibujoOUT:
    def __init__(self, archivo="Tp3.out"):
        # levanto el archivo
        f = open(archivo, 'r')

        # cantidad de nodos en P1
        cantLineas = int(f.readline())
        nodosP1 = []
        print 'nodosP1'
        for i in range(cantLineas):
            nodosP1.append(int(f.readline()))
            print nodosP1[i]
            
        # cantidad de nodos en P2
        cantLineas = int(f.readline())
        nodosP2 = []
        print 'nodosP2'
        for i in range(cantLineas):
            nodosP2.append(int(f.readline()))
            print nodosP2[i]

        # cantidad de ejes
        cantLineas = int(f.readline())
        ejes = []
        print 'ejes'
        for i in range(cantLineas):
            ejeArr = f.readline().split()
            ejes.append((int(ejeArr[0]), int(ejeArr[1])))
            print ejes[i]
        
        # fin del archivo
        f.close()

        g = GrafoBipartito(Set(nodosP1), Set(nodosP2), Set(ejes))
        d = Dibujo(g, nodosP1, nodosP2)

    def dibujo(self):
        return d

if __name__ == '__main__':
    dib = ParserDibujoOUT()
    DibujadorGrafoBipartito(dib).grabar('dibujoOUT.svg')
