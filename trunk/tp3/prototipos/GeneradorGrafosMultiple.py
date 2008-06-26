#!/usr/bin/python
# -*- coding: utf-8 -*-

from GrafoBipartito import GrafoBipartito, Dibujo

from sets import Set
import random

def generarGrafoEntradaTp(iv1,iv2,v1,v2,m):
    p1 = range(v1)
    p2 = range(v1,v1+v2)
    ip1 = range(v1+v2,v1+v2+iv1)
    ip2 = range(v1+v2+iv1,v1+v2+iv1+iv2)
    p1 +=ip1
    p1=Set(p1)
    p2 +=ip2
    p2 = Set(p2)
    ejesPosibles = [(a,b) for a in p1 for b in p2]
    ejes = random.sample(ejesPosibles,m)

    return GrafoBipartito(p1,p2,Set(ejes))
def generarDibujoAleatorioEntrada(iv1,iv2,v1,v2,m):
    g = generarGrafoEntradaTp(iv1,iv2,v1,v2,m)
    l1 = range(v1)
    random.shuffle(l1)
    l2 = range(v1,v1+v2)
    random.shuffle(l2)
    return Dibujo(g,l1,l2)

def generarGrafoBipartitoAleatorio(n1=10,n2=10,m=25):
    p1 = range(n1)
    p2 = range(n1,n1+n2)
    maxEjes = n1 * n2
    if m > n1 * n2:
        raise ValueError, "Error: K_(%s,%s) tiene %s ejes (se pidieron %s)." % (n1, n2, n1*n2, m)
    
    # FIXME: esto es un poco ineficiente
    # se pueden generar pares al azar e ir insertandolos
    # hasta que el conjunto tiene el cardinal deseado
    ejesPosibles = [(a,b) for a in p1 for b in p2]
    ejes = random.sample(ejesPosibles,m)

    return GrafoBipartito(Set(p1),Set(p2),Set(ejes))

def generarDibujoAleatorio(g, n1=5, n2=5):
    assert n1 <= len(g.p1), "Error: El dibujo no puede tener más nodos que la particion p1."
    assert n2 <= len(g.p2), "Error: El dibujo no puede tener más nodos que la particion p2."

    p1 = list(g.p1)
    p2 = list(g.p2)
    l1 = random.sample(p1, n1)
    l2 = random.sample(p2, n2)

    return Dibujo(g, l1, l2)

def generarEntrada(iv1,iv2,v1,v2,m, out):
    d=generarDibujoAleatorioEntrada(iv1,iv2,v1,v2,m)
    out.write(str(v1)+"\n")
    for each in d.l1:
        out.write(str(each+1)+"\n")
    out.write(str(v2)+"\n")
    for each in d.l2:
        out.write(str(each+1)+"\n")
    ejesInternos = [(x,y) for (x,y) in d.g.ejes if x in d.l1 and y in d.l2]
    out.write(str(len(ejesInternos))+"\n")
    for each in ejesInternos:
        out.write(str(each[0]+1)+" "+str(each[1]+1)+"\n")
    out.write(str(iv1)+"\n")
    for each in range(v1+v2,v1+v2+iv1):
        out.write(str(each+1)+"\n")
    out.write(str(iv2)+"\n")
    for each in range(v1+v2+iv1, v1+v2+iv1+iv2):
        out.write(str(each+1)+"\n")
    ejesNuevos = [(x,y) for (x,y) in d.g.ejes if (x,y) not in ejesInternos]
    out.write(str(len(ejesNuevos))+"\n")
    for (x,y) in ejesNuevos:
        out.write(str(x+1)+" " +str(y+1)+"\n")

def test_generadores():
    g = generarGrafoBipartitoAleatorio(n1=10, n2=10, m=25)
    d = generarDibujoAleatorio(g, n1=5, n2=5)
    print g
    print
    print d

if __name__ == '__main__':
    size = 50
    pctMov = 0.2
    pctFij = 0.8
    pctEje = 0.8
    
    out=open("testHeuristicasCasosGrandes"+str(int(pctFij*100))+str(int(pctEje*100))+".in",'w')
    for i in range(2, size + 1):
        print i
        ejesTotal = (int(i*pctMov) + int(i*pctFij))*(int(i*pctMov) + int(i*pctFij))
        generarEntrada(int(i*pctMov),int(i*pctMov),int(i*pctFij),int(i*pctFij),int(ejesTotal*pctEje), out)
    out.write("-1"+"\n")
    out.flush()
    out.close()

    pctMov = 0.5
    pctFij = 0.5
    pctEje = 0.5
    
    out=open("testHeuristicasCasosGrandes"+str(int(pctFij*100))+str(int(pctEje*100))+".in",'w')
    for i in range(2, size + 1):
        print i
        ejesTotal = (int(i*pctMov) + int(i*pctFij))*(int(i*pctMov) + int(i*pctFij))
        generarEntrada(int(i*pctMov),int(i*pctMov),int(i*pctFij),int(i*pctFij),int(ejesTotal*pctEje), out)
    out.write("-1"+"\n")
    out.flush()
    out.close()

    pctMov = 0.8
    pctFij = 0.2
    pctEje = 0.2
    
    out=open("testHeuristicasCasosGrandes"+str(int(pctFij*100))+str(int(pctEje*100))+".in",'w')
    for i in range(2, size + 1):
        print i
        ejesTotal = (int(i*pctMov) + int(i*pctFij))*(int(i*pctMov) + int(i*pctFij))
        generarEntrada(int(i*pctMov),int(i*pctMov),int(i*pctFij),int(i*pctFij),int(ejesTotal*pctEje), out)
    out.write("-1"+"\n")
    out.flush()
    out.close()
