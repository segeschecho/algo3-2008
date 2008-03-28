from sets import Set

class Cosa:
    def __init__(self, costo, valor):
        self.costo = costo
        self.valor = valor

class Candidato:
    def __init__(self, conj, valor=None):
        self.conj = conj

        if valor is None:
            self.valor = self._calcularValor(conj)
        else:
            self.valor = valor

    def _calcularValor(conj):
        s = 0
        for i in conj:
            s += i.valor
        return s


class Mochila:
        def __init__(self, cosas, capacidad):
            self.cosas = cosas
            self.capacidad = capacidad

cosas = [Cosa(3,4),
         Cosa(7,2),
         Cosa(2,5),
         Cosa(3,4),
         Cosa(6,4)
        ]
tabla = [Candidato(Set(), 0)]

m = Mochila(cosas, 10)
