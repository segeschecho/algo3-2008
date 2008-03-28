class Cosa:
    def __init__(self, costo, valor):
        self.costo = costo
        self.valor = valor

    def __repr__(self):
        return "<Cosa de valor %s y peso %s>" % (self.valor, self.costo)

class Mochila:
        def __init__(self, cosas, capacidad):
            self.cosas = cosas
            self.capacidad = capacidad

# Halla el valor maximo que se puede cargar con programacion dinamica.
def knapDinamico(m):
    return knapDinAux(len(m.cosas), m.capacidad, m)

def knapDinAux(i,j,m):
    if i == 0 or j == 0:
        return 0
    elif m.cosas[i-1].valor > j:
        return knapDinAux(i-1, j, m)
    else:
        return max(knapDinAux(i-1,j,m), m.cosas[i-1].valor + knapDinAux(i-1, j-m.cosas[i-1].costo, m))



# Halla la combinacion de objetos que produce el mejor valor
# haciendo backtracking.

def knapBT(m):
    return knapBTAux([], m.cosas, m.capacidad)

# FIXME: estas funciones se usan indiscriminadamente y provocan
# mucha repeticion de cuentas. Habria que crear una clase que wrapee
# la lista de candidatos que estoy usando y cachee el costo y valor
# asociados a la misma.

def costo(cand):
    s = 0
    for each in cand:
        s += each.costo
    return s

def valor(cand):
    s = 0
    for each in cand:
        s += each.valor
    return s

def knapBTAux(candActual, restantes, capacidad):
    if restantes == []:
        return candActual
    else:
        a = knapBTAux(candActual, restantes[1:], capacidad)
        if costo(candActual) + restantes[0].costo <= capacidad:
            b = knapBTAux(candActual + [restantes[0]], restantes[1:], capacidad)
            if valor(b) > valor(a):
                return b
        return a

if __name__ == '__main__':
    cosas = [Cosa(3,4),
             Cosa(7,2),
             Cosa(2,5),
             Cosa(3,4),
             Cosa(6,4)
            ]

    m = Mochila(cosas, 10)

    print "La mejor solucion es %s con un valor de %s." % (knapBT(m), knapDinamico(m))
