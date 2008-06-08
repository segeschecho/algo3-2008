from HeuristicaDeLaMediana import *
from HeuristicaInsercionEjes import *
from HeuristicaInsercionNodos import *
import psyco
psyco.full()

def testHeuristicas(p1,p2,v1,v2,m):
    g =  generarGrafoBipartitoAleatorio(p1+v1, p2+v2, m)
    d = generarDibujoAleatorio(g, v1, v2)
    resMed = HeuristicaDeLaMediana(d).resolver()
    resInsN = HeuristicaInsercionNodos(d).resolver()
    resInsE = HeuristicaInsercionEjes(d).resolver()
    return (resMed.contarCruces(),resInsN.contarCruces(),resInsE.contarCruces())

def testEsparsos(p1Max):
    med = open("testEsparsoMed.m","w")
    insE = open("testEsparsoInsE.m","w")
    insN = open("testEsparsoInsN.m","w")
    med.write("med=[")
    insN.write("insN=[")
    insE.write("insE=[")
    for each in range(3,p1Max+1):
        res = testHeuristicas(each,each,each/2,each/2,2*each)
        med.write(str(res[0])+" ")
        insN.write(str(res[1])+" ")
        insE.write(str(res[2])+" ")
    med.write("];")
    insN.write("];")
    insE.write("];")
    p1 = open("testEsparso.m","w")
    p1.write("n="+str(range(3,p1Max+1))+";")

def testMitadDeEjes(p1Max):
    med = open("testMitadMed.m","w")
    insE = open("testMitadInsE.m","w")
    insN = open("testMitadInsN.m","w")
    med.write("med=[")
    insN.write("insN=[")
    insE.write("insE=[")
    for each in range(3,p1Max+1):
        res = testHeuristicas(each,each,each/2,each/2,(each*each)/2)
        med.write(str(res[0])+" ")
        insN.write(str(res[1])+" ")
        insE.write(str(res[2])+" ")
    med.write("];")
    insN.write("];")
    insE.write("];")
    p1 = open("testMitad.m","w")
    p1.write("n="+str(range(3,p1Max+1))+";")

def testDenso(p1Max):
    med = open("testDensoMed.m","w")
    insE = open("testDensoInsE.m","w")
    insN = open("testDensoInsN.m","w")
    med.write("med=[")
    insN.write("insN=[")
    insE.write("insE=[")
    for each in range(3,p1Max+1):
        res = testHeuristicas(each,each,each/2,each/2,(each*each)-each)
        med.write(str(res[0])+" ")
        insN.write(str(res[1])+" ")
        insE.write(str(res[2])+" ")
    med.write("];")
    insN.write("];")
    insE.write("];")
    p1 = open("testDenso.m","w")
    p1.write("n="+str(range(3,p1Max+1))+";")
    
testDenso(100)
