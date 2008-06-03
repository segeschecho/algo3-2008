from GrafoBipartito import ResolvedorConstructivo, Dibujo
from Dibujador import DibujadorGrafoBipartito
from GeneradorGrafos import generarGrafoBipartitoAleatorio, generarDibujoAleatorio
#from HeuristicaInsercionNodos import *
from HeuristicaInsercionEjes import *
from HeuristicaRemocion import *
from HeuristicaMediana import *
from HeuristicaSplitting import *
from psyco import *
psyco.full()

def testear(n1,n2,n3,n4,m):
    g = generarGrafoBipartitoAleatorio(n1,n2,m)
    print 'nodos =', g.p1
    print 'nodos =', g.p2
    print 'ejes =', g.ejes
    dib = generarDibujoAleatorio(g,n3,n4)
    #resultado1 = HeuristicaInsercionNodos(dib).resolver()
    resultado2 = HeuristicaInsercionEjes(dib).resolver()
    resultado3 = HeuristicaRemocion(dib).resolver()
    resultado4 = HeuristicaMediana(dib).resolver()
    resultado5 = HeuristicaSplitting(dib).resolver()
    #DibujadorGrafoBipartito(resultado1).grabar('insercionNodos.svg')
    DibujadorGrafoBipartito(resultado2).grabar('insercionEjes.svg')
    DibujadorGrafoBipartito(resultado3).grabar('remocion.svg')
    DibujadorGrafoBipartito(resultado4).grabar('mediana.svg')
    DibujadorGrafoBipartito(resultado5).grabar('splitting.svg')
    #print "resultado inserccionNodos: ", resultado1.contarCruces(), "cruces"
    print "resultado inserccionEjes:  ", resultado2.contarCruces(), "cruces"
    print "resultado remocion:        ", resultado3.contarCruces(), "cruces"
    print "resultado mediana:         ", resultado4.contarCruces(), "cruces"
    print "resultado splitting:       ", resultado5.contarCruces(), "cruces"

print "HOLAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
testear(100,100,2,1,400)
