from math import ceil, sqrt

class FabricaPrimos:
    def __init__(self):
        self.fab = FabricaCandidatos()
        self.primosHastaAhora = []

    def _esPrimo(self, n):
        s = sqrt(n)
        for each in self.primosHastaAhora:
            if each > s:
                return True
            if n % each == 0:
                return False

        return True


    def next(self):
        cand = self.fab.next()
        while not self._esPrimo(cand):
            cand = self.fab.next()

        self.primoActual = cand
        self.primosHastaAhora.append(cand)
        return self.primoActual


class FabricaCandidatos:
    def __init__(self):
        self.numeroActual = 1
        # Optimizacion loca: los primos mayores que 5 son 6k+1 o 6k+5
        # turno = 0 -> el siguiente candidato es 6 * k + 5
        # turno = 1 -> el siguiente candidato es 6 * k + 1
        self.turno = 0
        self.k = 1

    def next(self):
        if self.numeroActual in [1,2]:
            self.numeroActual = self.numeroActual + 1
        elif self.numeroActual in [3,5]:
            self.numeroActual = self.numeroActual + 2
        else:
            if self.turno == 0:
                self.numeroActual = 6 * self.k + 5
                self.k = self.k + 1
                self.turno = 1
            else:
                self.numeroActual = 6 * self.k + 1
                self.turno = 0
        
        return self.numeroActual

def primoDeMayorPotencia(n):
    assert(n > 1)

    mejorPrimo = 1
    mejorPotencia = 0

    f = FabricaPrimos()
    primoActual = f.next()
    potenciaActual = 0
    
    s = int(ceil(sqrt(n)))

    while n != 1:
        # si me paso de la raiz, pruebo con el numero
        if primoActual > s:
            primoActual = n
            potenciaActual = 1
            break
            
        if n % primoActual == 0:
            potenciaActual += 1
            n = n / primoActual
        else:
            if potenciaActual >= mejorPotencia:
                mejorPrimo = primoActual
                mejorPotencia = potenciaActual

            potenciaActual = 0
            primoActual = f.next()
            s = int(ceil(sqrt(n)))

    
    if potenciaActual >= mejorPotencia:
        mejorPrimo = primoActual
        mejorPotencia = potenciaActual

    return mejorPrimo, mejorPotencia


if __name__ == '__main__':
    import sys
    print primoDeMayorPotencia(int(sys.argv[1]))
