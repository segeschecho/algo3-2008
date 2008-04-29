import random
import psyco
psyco.full()

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

def armarDigrafo(n,m):
    matriz=[[ 0 for x in range(n)] for y in range(n)]
    pares = [(x,y) for x in range(n) for y in range(n) if x != y]
    z=random.sample(pares,m)
##    for i in range(m):
##        x=random.randint(0,n-1)
##        y=random.randint(0,n-1)
##        while x == y or matriz[y][x] == 1 or matriz[x][y] == 1:
##            x=random.randint(0,n-1)
##            y=random.randint(0,n-1)
    for (x,y) in z:
        matriz[x][y] = 1
    relacion = [(x,y) for x in range(n) for y in range(n) if matriz[x][y] == 1]
    return relacion

def resolver(grafo):
    global visitado
    res = []
    for each in range(grafo.nodos):
        visitado = [0]*grafo.nodos
        if bfp(grafo,each) == grafo.nodos:
            res.append(each)
            
    return res
    
def test(n,m):
        outp = open("test"+str(n)+str(m)+"salida.txt","w")
        outp1 = open("test"+str(n)+str(m)+".txt","w")
        for each in range(100,n):
            each1=((each-1)*each)/2
        for each1 in range(1,min(((each-1)*each)/2,m)):
            rel = armarDigrafo(each,each1)
            outp1.write(str(each)+" "+str(each1)+"\n")
            if(len(rel) != each1):
                print "putaaaaaaaaaaaa"
                return
            for each2 in rel:
                outp1.write(str(each2[0]+1)+" "+ str(each2[1]+1)+"\n")
            g = Grafo(each,rel)
            res = resolver(g)
            sol = str(len(res))
            for each3 in res:
                sol +=" "+str(each3+1)
            outp.write(sol+"\n")
        outp1.write("0 0")

                 
visitado =[]
def bfp(grafo,nodo):
    global visitado
    if visitado[nodo] == 1:
        return 0
    visitado[nodo] = 1
    res = 0
    for each in grafo.verticesIn[nodo]:
        if visitado[each] == 0:
            res+=bfp(grafo,each)
    return 1+res


test(100,1000)
