from GrafoBipartito import ResolvedorConstructivo, Dibujo
from Dibujador import DibujadorGrafoBipartito
from GeneradorGrafos import generarGrafoBipartitoAleatorio, generarDibujoAleatorio
from HeuristicaInsercionNodos import *

from HeuristicaInsercionEjes import *
from HeuristicaRemocion import *
from HeuristicaMediana import *
from HeuristicaSplitting import *
from HeuristicaSwap import *
from psyco import *
psyco.full()

def testear(n1,n2,n3,n4,m,k=1):
    
    g = generarGrafoBipartitoAleatorio(n1,n2,m)
    
    dib = generarDibujoAleatorio(g,n3,n4)
    resultado1 = HeuristicaInsercionNodos(dib).resolver()
    resultado2 = HeuristicaInsercionEjes(dib).resolver()
    resultado3 = HeuristicaRemocion(dib).resolver()
    resultado4 = HeuristicaMediana(dib).resolver()
    resultado5 = HeuristicaSplitting(dib).resolver()
    resultado6 = HeuristicaSwap(dib).resolver()
##    DibujadorGrafoBipartito(resultado1).grabar('insercionNodos.svg')
##    DibujadorGrafoBipartito(resultado2).grabar('insercionEjes.svg')
##    DibujadorGrafoBipartito(resultado3).grabar('remocion.svg')
##    DibujadorGrafoBipartito(resultado4).grabar('mediana.svg')
##    DibujadorGrafoBipartito(resultado5).grabar('splitting.svg')
##    DibujadorGrafoBipartito(resultado6).grabar('swap.svg')
##    DibujadorGrafoBipartito(resultado7).grabar('insercionEjes2.svg')
##    print "resultado inserccionNodos: ", resultado1.contarCruces(), "cruces"
##    print "resultado inserccionEjes:  ", resultado2.contarCruces(), "cruces"
##    print "resultado remocion:        ", resultado3.contarCruces(), "cruces"
##    print "resultado mediana:         ", resultado4.contarCruces(), "cruces"
##    print "resultado splitting:       ", resultado5.contarCruces(), "cruces"
##    print "resultado swap:            ", resultado6.contarCruces(), "cruces"
##    print "resultado inserccionEjes2: ", resultado7.contarCruces(), "cruces"
    
    return (resultado1.contarCruces(),resultado2.contarCruces(),resultado3.contarCruces(),resultado4.contarCruces(),resultado5.contarCruces(),resultado6.contarCruces())
   
nodos = open("testNodos.m","w")
ejes = open("testEjes.m","w")
remocion = open("testRemocion.m","w")
mediana = open("testMediana.m","w")
split = open("testSplit.m","w")
swap = open("testSwap.m","w")
n = open("testN.m","w")
nodos.write("nodos=[")
ejes.write("ejes=[")
remocion.write("remocion=[")
mediana.write("mediana=[")
split.write("split=[")
swap.write("swap=[")
n.write("n=[")
for i in range(20,70):
      j=i
      if i != 69 or j != 69: 
          res=testear(i,j,2*i/3,2*j/3,i*j/2)
          nodos.write(str(res[0])+',')
          ejes.write(str(res[1])+',')
          remocion.write(str(res[1])+',')
          mediana.write(str(res[1])+',')
          split.write(str(res[1])+',')
          swap.write(str(res[1])+',')
          n.write(str(i+j)+',')
      else:
          res=testear(i,j,2*i/3,2*j/3,i*j/2)
          nodos.write(str(res[0]))
          ejes.write(str(res[1]))
          remocion.write(str(res[2]))
          mediana.write(str(res[3]))
          split.write(str(res[4]))
          swap.write(str(res[5]))
          n.write(str(i+j))
nodos.write("];")
ejes.write("];")
remocion.write("];")
mediana.write("];")
split.write("];")
swap.write("];")
n.write("];")      
            
