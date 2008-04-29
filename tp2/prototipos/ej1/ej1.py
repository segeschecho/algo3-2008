#############################################################################
valor=[]
num = 0
visitado = []
fuerte = []
#############################################################################
# grafo sobre listas de adyacencia
# FIXME: a las 5 a.m me parecio re coherente que si llegan se llamen out
# y si salen se llaman in :S
class Grafo:
    def __init__(self,nodos, relacion):
        self.nodos = nodos
        self.verticesIn = [[] for x in range(nodos)]
        self.verticesOut = [[] for x in range(nodos)]
        for each in relacion:
            self.verticesIn[each[0]].append(each[1])
            self.verticesOut[each[1]].append(each[0])
    def __str__(self):
        ret = "grafo con: "+str(self.nodos)+" nodos\n"
        for each in range(self.nodos):
            for each1 in self.verticesIn[each]:
                ret += str((each,each1)) + " "
        return ret
############################################################################

#realiza busqueda en profundidad
#indexa los elementos segun el orden de la llamada recursiva
#es decir, "apila" los elementos
def auxbfp(grafo):
    global visitado
    global valor
    visitado = [0]*grafo.nodos
    valor = [0]*grafo.nodos
    global num
    num = 0
    for i in range(grafo.nodos):
        if visitado[i] == 0:
            bfp(grafo,i)
            
#la funcion que hace la logica del bfp que indexa
def bfp(grafo,nodo):
    global num
    global visitado
    global valor
    visitado[nodo] = 1
    for each in grafo.verticesIn[nodo]:
        if visitado[each] == 0:
            bfp(grafo,each)
    valor[num] = nodo
    num +=1

#transforma un grafo g en g^t, donde
# g = (x,v) -> g^t = (x,v')
# v'={(a,b) / (b,a) \in v}
# en criollo, tiene los mismos nodos, y las flechas al reves
def invertirGrafo(grafo):
    x=[]
    for each in range(grafo.nodos):
        for each1 in grafo.verticesIn[each]:
            x.append((each1,each))
    return Grafo(grafo.nodos,x)

# busqueda en profuncidad, parte de un nodo y mete todos los q visita en una lista
# en el contexto en que se llama, logra armar las componentes fuertemente conexas de g
def bfp2(grafo,nodo):
    global fuerte
    global visitado
    visitado[nodo] = 1
    for each in grafo.verticesIn[nodo]:
        if visitado[each] == 0:
            bfp2(grafo,each)
    fuerte.append(nodo)

# devuelve las componentes fuertemente conexas del grafo
# usando el algoritmo de Kosaraju
def armarFuertes(grafo):
    global visitado
    global fuerte
    global valor
    auxbfp(grafo)
    visitado=[0]*grafo.nodos
    g = invertirGrafo(grafo)
    fuertes = []
    valor.reverse()
    for each in valor :
        if visitado[each] == 0:
            bfp2(g,each)
            fuertes.append(fuerte)
            fuerte=[]
    return fuertes


def ejercicio1(grafo):
    global fuerte
    fuerte = [] 
    fuertes = armarFuertes(grafo) 
    dondeQuedo=[0]*grafo.nodos
    #en donde quedo guardo en que componente fuertemente conexa quedo cada elemento
    #es util para crear el grafo reducido con buen orden
    for i in range(len(fuertes)):
        for each1 in fuertes[i]:
            dondeQuedo[each1] = i
    x=[]
    # armo los vertices del nuevo grafo
    # filtro los vertices intra componente
    # pero quedan vertices repetidos
    # como diria page, la soba
    for i in range(grafo.nodos):
        for each in grafo.verticesIn[i]:
            if dondeQuedo[i] != dondeQuedo[each]:
                x.append((dondeQuedo[i],dondeQuedo[each]))
    #creo el grafo reducido
    g1=Grafo(len(fuertes),x)
    #galerazo: si el grafo de los partidos arreglados de un torneo, no tiene ciclos
    # el torneo se puede arreglar si y solo si hay un unico tipo tal que no le gana nadie
    # 0 no puede haber porq sino hay un ciclo en algun lado
    # si hay 2 o mas, no los puedo eliminar porq no les gana nadie
    # si hay uno, es la raiz de un pseudo-arbol (grafo dirigido aciclico) y es lo q busco
    #aplico galerazo para decidir quien gana
    yaHayUno=False
    quien = None
    for each in range(g1.nodos):
        if g1.verticesOut[each] == [] and not yaHayUno:
            quien = each
            yaHayUno = True
        elif g1.verticesOut[each] == [] and yaHayUno:
            print  "nadie"
            return
    if not yaHayUno:
        print "asdsadsadsadsadsadsadasdsasad la reconchaPuta"
    print fuertes[quien]
    
    
        
g = Grafo(9,[(0,1),(0,6),(6,7),(7,0),(1,3),(1,5),(5,4),(3,4),(3,2),(2,1),(2,0),(8,5),(4,8)])
ejercicio1(g)
g = Grafo(3,[(0,1),(1,2),(2,0)])
ejercicio1(g)
g= Grafo(3,[(0,1),(0,2)])
ejercicio1(g)
g = Grafo(3,[(0,1),(2,1)])
ejercicio1(g)
g = Grafo(10, [(0,1),(1,2),(2,3),(3,1),(3,4),(4,0),(4,5),(0,6),(6,5),(7,8)])
ejercicio1(g)
g = Grafo(8, [(0,1),(1,2),(1,3),(0,4),(4,5),(5,6),(5,7)])
ejercicio1(g)
g = Grafo(8, [(0,1),(0,2),(0,3),(0,4),(0,5),(0,6),(0,7),(1,2),(2,3),(3,4),(4,5),(5,6),(6,7)])
ejercicio1(g)
g = Grafo(7, [(0,1),(1,2),(0,3),(3,4),(4,5),(4,6),(6,5),(6,3)])

