from GrafoBipartito import *
from HeuristicaInsercionEjes import HeuristicaInsercionEjes
from BusquedaLocalReInsercion import *
from BusquedaLocalMix import *
from HeuristicaDeLaMediana import HeuristicaDeLaMediana
from BusquedaLocalMediana import BusquedaLocalMediana
from HeuristicaInsercionNodos import *
from SolucionSwapperPoda import ResolvedorSwapperConPoda
import psyco
psyco.full()
class GraspInsercionReInsercion (Grasp):
    def resolver(self,dibujo):
        marcados1 = dibujo.l1[:]
        marcados2 = dibujo.l2[:]
        print marcados1
        print marcados2
        losEjesDe = {}
        for each in dibujo.g.p1 :
            losEjesDe[each] = []
        for each in dibujo.g.p2 :
            losEjesDe[each] = []
        for each in dibujo.g.ejes:
            losEjesDe[each[0]].append(each[1])
            losEjesDe[each[1]].append(each[0])
        k = 0.3
        print "antes de hacer nada hay", contadorDeCruces(marcados1 + [x for x in dibujo.g.p1 if x not in marcados1], marcados2 + [x for x in dibujo.g.p2 if x not in marcados2],losEjesDe)
        mejorSol = HeuristicaInsercionNodos(dibujo).resolver()
        blie = BusquedaLocalMediana()
        blie.mejorar(mejorSol,marcados1,marcados2,losEjesDe)
        mejoresCruces = contadorDeCruces(mejorSol.l1,mejorSol.l2,losEjesDe)
        print "la solucion inicial tiene", mejoresCruces,"cruces"
        sinMejorar = 0
        
        while (sinMejorar < 100):
            res =  HeuristicaInsercionEjes(dibujo).resolver(alfa=k)
            blie.mejorar(res,marcados1,marcados2,losEjesDe)
            nuevosCruces = contadorDeCruces(res.l1,res.l2,losEjesDe)
            print "en esta iteracion encontre uno de ",nuevosCruces,"cruces"
            if nuevosCruces < mejoresCruces:
                mejorSol = res
                mejoresCruces = nuevosCruces
                sinMejorar=0
                print "mejore a una sol con: ", mejoresCruces
            else:
                sinMejorar +=1
        DibujadorGrafoBipartito(mejorSol,marcados1=marcados1,marcados2=marcados2).grabar('grasp.svg')
        print "lo mejor que encontre fue", mejoresCruces
        print "solucion posta ",ResolvedorSwapperConPoda(dibujo).resolver()
        return mejorSol
    
g =  generarGrafoBipartitoAleatorio(15, 15, 30)
d = generarDibujoAleatorio(g,11, 11)
sol = GraspInsercionReInsercion().resolver(d)
