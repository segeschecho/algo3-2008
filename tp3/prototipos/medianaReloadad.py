from GrafoBipartito import *
from GeneradorGrafos import *
from Dibujador import *
from SolucionBasicaPoda import *
# grafo: todos los nodos y ejes, p1 p2 estaRel(v,u)
#dibujo: l1, l2 los nodos que no se pueden mover
class HeuristicaMediana2 (ResolvedorConstructivo):
    def calcularMediana(self,each,indicesV2,ejesDe):
        med=[]
        for each2 in ejesDe[each]:
            med += [indicesV2[each2]]
        med.sort()
        if len(ejesDe[each]) % 2 == 1:
            return med[len(ejesDe[each])/2]
        elif len(ejesDe[each]) > 0:
            return int(round((med[len(ejesDe[each])/2] + med[(len((ejesDe[each]))-1)/2])/2.0) )
        else:
            return 0
    def disponerSegunMediana(self,v1,medianasV1,ejesDe,largoV2,marcados1):
        #primero ordeno los v1 por grado, hago binsort
        ordenados = [[] for x in range(largoV2+1)]
        for each in v1:
            ordenados[len(ejesDe[each])].append(each)
        #los voy a meter en un arreglo que tiene tantos lugares como
        #max v1,v2 porq si v2 es mas largo que v1 la mediana puede ser muy
        #grande, y si v1 es mas grande tengo q meter a todos :D
        metidos = [None for x in range(max(len(v1),largoV2)+1)]
        #la idea es ir metiendo a los de mayor grado
        while ordenados != []:
            grado = ordenados.pop()
            for each in grado:
                if each not in marcados1:
                    if metidos[medianasV1[each]] == None:
                        metidos[medianasV1[each]] = each
                    else:
                        i = 1
                        loPuse = False
                        while(True):
                            if medianasV1[each] + i < len(metidos):
                                if metidos[medianasV1[each]+i] == None:
                                    metidos[medianasV1[each]+i] = each
                                    break
                                if medianasV1[each] - i >= 0:
                                    if metidos[medianasV1[each]-i] == None:
                                        metidos[medianasV1[each]-i] = each
                                        break
                            elif medianasV1[each] - i >= 0:
                                if metidos[medianasV1[each]-i] == None:
                                    metidos[medianasV1[each]-i] = each
                                    break
                            else:
                                raise Exception("indice re sacado")
                            i+=1
                else:
                    #primero averiguo el rango donde lo puedo poner
                    i = marcados1.index(each)
                    anterior = 0

                    siguiente = len(metidos)
                    k = 0
                    if i != 0:
                        while (i -1 - k) >= 0:
                            if marcados1[i-1-k] in metidos:
                                anterior = metidos.index(marcados1[i-1-k])
                                break
                            k+=1
                    k=0
                    if i != len(marcados1)- 1:
                        while(i+1+k <= len(marcados1)-1):
                            if marcados1[i+1+k] in metidos:
                                siguiente = metidos.index(marcados1[i+1+k])
                                break
                            k+=1
                    #despues trato de ponerlo:
                    loMeti = False
                    if medianasV1[each] == None:
                        if medianasV1[each] > anterior and medianasV1[each] < siguiente:
                            metidos[medianasV1[each]] = each
                            loMeti = True
                    if not loMeti:
                        i = 1
                        loPuse = False
                        while(True):
         
                            if medianasV1[each] + i < len(metidos):
                                if metidos[medianasV1[each]+i] == None:
                                    pos = medianasV1[each]+i
                                    break
                            elif medianasV1[each] - i >= 0:
                                if metidos[medianasV1[each]-i] == None:
                                    pos = medianasV1[each]-i
                                    break
                            else:
                                pos = None
                                break
                            i+=1
                        if pos != None and pos > anterior and pos < siguiente:
                            
                            metidos[pos] = each
                        else:
                            if abs(anterior-medianasV1[each]) < abs(siguiente-medianasV1[each]):
                              
                                metidos.insert(anterior+1,each)
                            else:
                                
                                metidos.insert(siguiente,each)         
                    
        v1Aux = [x for x in metidos if x != None]
        return v1Aux
    def corregirDesvios(self,v1Aux,v2,marcados,ejesDe):
        for fede in range(2):
            #primero hacemos swap desde arriba hacia abajo
            for i in range(len(v1Aux)-1):
                if v1Aux[i] not in marcados or v1Aux[i+1] not in marcados:
                    if contadorDeCruces([v1Aux[i],v1Aux[i+1]],v2,ejesDe) > contadorDeCruces([v1Aux[i+1],v1Aux[i]],v2,ejesDe):
                        aux = v1Aux[i]
                        v1Aux[i] = v1Aux[i+1]
                        v1Aux[i+1] = aux
            for i in range(1,len(v1Aux)):
                if v1Aux[len(v1Aux)-i] not in marcados or v1Aux[len(v1Aux)-i -1] not in marcados:
                    if contadorDeCruces([ v1Aux[len(v1Aux)-i -1],v1Aux[len(v1Aux)-i]],v2,ejesDe) > contadorDeCruces([v1Aux[len(v1Aux)-i], v1Aux[len(v1Aux)-i -1]],v2,ejesDe):

                        aux = v1Aux[len(v1Aux)-i]
                        v1Aux[len(v1Aux)-i] = v1Aux[len(v1Aux)-i -1]
                        v1Aux[len(v1Aux)-i -1] = aux
        return v1Aux
            
    def resolver(self):
        #nodos sin marcar en cada particio
        sinMarcar1 = [x for x in self.dibujo.g.p1 if x not in self.dibujo.l1]
        sinMarcar2 = [x for x in self.dibujo.g.p2 if x not in self.dibujo.l2]
        #nodos marcados (posicion relativa fija)
        
        marcados1 = self.dibujo.l1
        marcados2 = self.dibujo.l2
        print "marcados1",marcados1
        print "marcados2",marcados2
        #nodos totales
        v1 = sinMarcar1 + marcados1
        v2 = sinMarcar2 + marcados2
        #inicializa arreglo de medianas para los nodos de v1
        medianaV1={}
        #ejesDe: listas de adyacencias
        ejesDe = {}
        #lo inicializo
        for each in v1+v2:
            ejesDe[each] = []
        #la completo
        for each in self.dibujo.g.ejes:
            ejesDe[each[0]].append(each[1])
            ejesDe[each[1]].append(each[0])
        #para calcular las medianas voy a necesitar saber las posiciones de
        #cada nodo de v2
        for each in range(2):
            indicesV2 ={}
            for i in range(len(v2)):
                indicesV2[v2[i]] = i
            #calculo las medianas de v1
            for each in v1:
                medianaV1[each] = self.calcularMediana(each,indicesV2,ejesDe)
            #los dispongo segun la mediana
            v1Aux = self.disponerSegunMediana(v1,medianaV1,ejesDe,len(v2),marcados1)
            #se hace una pasada para corregir errores por desempate
            v1 = self.corregirDesvios(v1Aux,v2,marcados1,ejesDe)
            # ahora se repite el proceso pero para v2
            indicesV1 ={}
            medianaV2={}
            for i in range(len(v1)):
                indicesV1[v1[i]] = i
            #calculo las medianas de v2
            for each in v2:
                medianaV2[each] = self.calcularMediana(each,indicesV1,ejesDe)
            #los dispongo segun la mediana
            v2Aux = self.disponerSegunMediana(v2,medianaV2,ejesDe,len(v1),marcados2)
            #se hace una pasada para corregir errores por desempate
            v2 = self.corregirDesvios(v2Aux,v1,marcados2,ejesDe)
            # ahora se repite el proceso pero para v2
        return Dibujo(self.dibujo.g,v1,v2)
        
        

if __name__ == '__main__':
    g = generarGrafoBipartitoAleatorio(7,7,32)
    print 'nodos =', g.p1
    print 'nodos =', g.p2
    print 'ejes =', g.ejes
    dib = generarDibujoAleatorio(g,2,2)
    resultado = HeuristicaMediana2(dib).resolver()
    resultado2 = ResolvedorBasicoConPoda(dib).resolver()
    print "mediana", resultado.contarCruces()
    print "posta", resultado2.contarCruces()
    DibujadorGrafoBipartito(resultado).grabar('dibujo.svg')
