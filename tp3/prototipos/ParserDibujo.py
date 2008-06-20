from GrafoBipartito import GrafoBipartito, Dibujo
from Dibujador import DibujadorGrafoBipartito 
from sets import Set

# Parsea un archivo .in con una sola instancia y produce
# el dibujo asociado.
class ParserDibujoIn:
    def __init__(self, archivo="Tp3.in"):
        f = open(archivo, 'r')
        nf1 = int(f.readline())
        fijo1 = []
        nodos1 = []
        for i in range(nf1):
            n = int(f.readline())
            fijo1.append(n)
            nodos1.append(n)
        nf2 = int(f.readline())
        fijo2 = []
        nodos2 = []
        for i in range(nf2):
            n = int(f.readline())
            fijo2.append(n)
            nodos2.append(n)
        ejes = []
        nejes = int(f.readline())
        for i in range(nejes):
            a,b = f.readline().split()
            ejes.append((int(a),int(b)))

        nm1 = int(f.readline())
        for i in range(nm1):
            n = int(f.readline())
            nodos1.append(n)

        nm2 = int(f.readline())
        for i in range(nm2):
            n = int(f.readline())
            nodos2.append(n)

        nejes = int(f.readline())
        for i in range(nejes):
            a,b = f.readline().split()
            ejes.append((int(a),int(b)))

        f.close()

        g = GrafoBipartito(Set(nodos1), Set(nodos2), Set(ejes))
        self.d = Dibujo(g, fijo1, fijo2)

    def dibujo(self):
        return self.d
        
        
# Parsea un archivo .out con una sola instancia y devuelve
# el dibujo asociado.
class ParserDibujoOut:
    def __init__(self, archivo="Tp3.out"):
        # levanto el archivo
        f = open(archivo, 'r')

        # ignoro los cruces
        f.readline()
        # cantidad de nodos en P1
        cantLineas = int(f.readline())
        nodosP1 = []
        for i in range(cantLineas):
            nodosP1.append(int(f.readline()))
            print nodosP1[i]
            
        # cantidad de nodos en P2
        cantLineas = int(f.readline())
        nodosP2 = []
        for i in range(cantLineas):
            nodosP2.append(int(f.readline()))
            print nodosP2[i]

        # cantidad de ejes
        cantLineas = int(f.readline())
        ejes = []
        for i in range(cantLineas):
            ejeArr = f.readline().split()
            ejes.append((int(ejeArr[0]), int(ejeArr[1])))
            print ejes[i]
        
        # fin del archivo
        f.close()

        g = GrafoBipartito(Set(nodosP1), Set(nodosP2), Set(ejes))
        self.d = Dibujo(g, nodosP1, nodosP2)

    def dibujo(self):
        return self.d

if __name__ == '__main__':
    dib = ParserDibujoIn('../codigo/Tp3_chico.in').dibujo()
    print dib
    from SolucionSwapperTablaPoda import ResolvedorSwapperTablaConPoda
    s = ResolvedorSwapperTablaConPoda(dib).resolver()
    print s
