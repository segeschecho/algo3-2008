from GrafoBipartito import ResolvedorConstructivo, Dibujo
from Dibujador import DibujadorGrafoBipartito
from GeneradorGrafos import generarGrafoBipartitoAleatorio, generarDibujoAleatorio
from HeuristicaInsercionNodos import *
from HeuristicaInsercionEjes import *
from HeuristicaRemocion import *
from HeuristicaMediana import *
from HeuristicaSplitting import *
from SolucionBasicaPoda import *
from medianaReloadad import *
import psyco 
psyco.full()

def testear(n1,n2,n3,n4,m,k=1):
    
    g = generarGrafoBipartitoAleatorio(n1,n2,m)
    
    dib = generarDibujoAleatorio(g,n3,n4)
    resultado1 = HeuristicaInsercionNodos(dib).resolver()
    resultado2 = HeuristicaInsercionEjes(dib).resolver()
  #  resultado3 = HeuristicaRemocion(dib).resolver()
    resultado4 = HeuristicaMediana(dib).resolver()
    resultado5 = HeuristicaSplitting(dib).resolver()
    resultado7 = HeuristicaMediana2(dib).resolver()
    resultado10 = ResolvedorBasicoConPoda(dib).resolver()
##    DibujadorGrafoBipartito(resultado1).grabar('insercionNodos.svg')
##    DibujadorGrafoBipartito(resultado2).grabar('insercionEjes.svg')
##    DibujadorGrafoBipartito(resultado3).grabar('remocion.svg')
##    DibujadorGrafoBipartito(resultado4).grabar('mediana.svg')
##    DibujadorGrafoBipartito(resultado5).grabar('splitting.svg')
##    DibujadorGrafoBipartito(resultado6).grabar('swap.svg')
##    DibujadorGrafoBipartito(resultado7).grabar('insercionEjes2.svg')
    if(resultado10.contarCruces() == 0):
        if resultado1.contarCruces() == 0:
            print "resultado insercionNodos: ", 1, "cruces"
        else:
            print "resultado insercionNodos: ", 0, "cruces"
        if resultado2.contarCruces() == 0:
            print "resultado inserccionEjes: ", 1, "cruces"
        else:
            print "resultado insercionEjes: ", 0, "cruces"
        if resultado4.contarCruces() == 0:
            print "resultado mediana: ", 1, "cruces"
        else:
            print "resultado mediana: ", 0, "cruces"
        if resultado5.contarCruces() == 0:
            print "resultado inserccionSplit: ", 1, "cruces"
        else:
            print "resultado inserccionSplit: ", 0, "cruces"
        if resultado7.contarCruces()==0:
             print "resultado mediana2: ", 1, "cruces"
        else:
            print "resultado mediana2: ", 0, "cruces"   
    else:
        print "resultado inserccionNodos: ", float(resultado1.contarCruces())/resultado10.contarCruces(), "cruces"
        print "resultado inserccionEjes:  ", float(resultado2.contarCruces())/resultado10.contarCruces(), "cruces"
          #print "resultado remocion:        ", resultado3.contarCruces(), "cruces"
        print "resultado mediana:         ", float(resultado4.contarCruces())/resultado10.contarCruces(), "cruces"
        print "resultado splitting:       ", float(resultado5.contarCruces())/resultado10.contarCruces(), "cruces"
        print "resultado mediana2:", float(resultado7.contarCruces())/resultado10.contarCruces()
    print "la posta:", resultado10.contarCruces()
##      print "resultado swap:            ", resultado6.contarCruces(), "cruces"
##    print "resultado inserccionEjes2: ", resultado7.contarCruces(), "cruces"
    
    return (resultado1.contarCruces(),resultado2.contarCruces(),resultado4.contarCruces(),resultado5.contarCruces(),resultado10.contarCruces())
   
nodos = open("testNodos.m","w")
ejes = open("testEjes.m","w")

mediana = open("testMediana.m","w")
split = open("testSplit.m","w")

n = open("testN.m","w")
nodos.write("nodos=[")
ejes.write("ejes=[")
mediana.write("mediana=[")
split.write("split=[")
n.write("n=[")
for i in range(1,10):
      j=i
      print "termine con i =",i
      if i != 69 or j != 69: 
          res=testear(7,7,2,2,i)
##          nodos.write(str(float(res[0])/res[4])+',')
##          ejes.write(str(float(res[1])/res[4])+',')
##
##          mediana.write(str(float(res[2])/res[4])+',')
##          split.write(str(float(res[3])/res[4])+',')
##          n.write(str(i)+',')
##      else:
##          res=testear(i,j,2*i/3,2*j/3,i*j/2)
##          nodos.write(str(res[0]))
##          ejes.write(str(res[1]))
##
##          mediana.write(str(res[2]))
##          split.write(str(res[3]))
##
##          n.write(str(i))
nodos.write("];")
ejes.write("];")

mediana.write("];")

n.write("];")      
            
