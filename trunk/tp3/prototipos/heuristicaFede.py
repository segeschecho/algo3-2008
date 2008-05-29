from GrafoBipartito import *
# grafo: todos los nodos y ejes, p1 p2 estaRel(v,u)
#dibujo: l1, l2 los nodos que no se pueden mover
class heuristicaFede (ResolvedorConstructivo):
 def _contarCruces(self,p1,p2,ejes,x,y,ejesAMirar):
    cantidad = 0
    i1=p1.index(x)
    i2=p2.index(y)
    for i in range(i1):
	for j in range(i2+1,len(p2)):
		if((i,j) in ejes):
			cantidad += 1
    for i in range(i1+1,len(p1)):
	for j in range(0,i2):
		if((i,j) in ejes):
			cantidad += 1
    return cantidad

 def _esPosibleInsertar(self,x,y,p1Parcial,p2Parcial,i,j,marcadosl1,marcadosl2):
    marcados1 = marcadosl1
    marcados2 = marcadosl2
    if x not in marcados1:
	if y not in marcados2:
	    return True
        else:
            posYMarcado = marcados2.index(y)
            anterior=-1
            siguiente=len(p2Parcial)+10
	    if posYMarcado != 0:
                anterior= p2Parcial.index(marcados2[posYMarcado-1])
            if posYMarcado != len(marcados2):
                siguiente = p2Parcial.index(marcados2[posYMarcado+1])
            return anterior < j and j <= siguiente
    if y not in marcados2:
            posxMarcado = marcados1.index(x)
            anterior=-1
            siguiente=len(p1Parcial)+10
	    if posxMarcado != 0:
                anterior= p1Parcial.index(marcados1[posxMarcado-1])
            if posxMarcado != len(marcados1):
                siguiente = p1Parcial.index(marcados1[posxMarcado+1])
            return anterior < i and i <= siguiente
    else:
	    posYMarcado = marcados2.index(y)
            anterior=-1
            siguiente=len(p2Parcial)+10
	    if posYMarcado != 0:
                anterior= p2Parcial.index(marcados2[posYMarcado-1])
            if posYMarcado != len(marcados2):
                siguiente = p2Parcial.index(marcados2[posYMarcado+1])
            posxMarcado = marcados1.index(x)
            anteriorX=-1
            siguienteX=len(p1Parcial)+10
	    if posxMarcado != 0:
                anteriorX= p1Parcial.index(marcados1[posxMarcado-1])
            if posxMarcado != len(marcados1):
                siguienteX = p1Parcial.index(marcados1[posxMarcado+1])
            return anteriorX < i and i <= siguienteX and anterior < j and anterior <= siguiente

 def resolver(self):
    # Mariconadas
    p1 = list(self.dibujo.g.p1)
    p2 = list(self.dibujo.g.p2)
    grafo = self.dibujo.g
    dibujo=self.dibujo

    marcadosl1 = list(self.dibujo.l1)
    marcadosl2 = list(self.dibujo.l2)
    print "marcadosl1: ",marcadosl1
    print "marcadosl2: ",marcadosl2
    v1 = [x for x in p1 if x not in marcadosl1]
    print "v1: ", v1
    v2 = [y for y in p2 if y not in marcadosl2]
    print "v2: ", v2
    p1Parcial = marcadosl1 + v1
    print "p1Parcial: ", p1Parcial
    p2Parcial = marcadosl2 + v2
    print "p2Parcial: ", p2Parcial
    ejes = list(grafo.ejes)
    print "ejes: ",ejes
    ejesSinPoner = [ (x,y) for (x,y) in ejes if (x in v1 or y in v2) ]
    print "ejesSinPoner: ",ejesSinPoner
    ejesPuestos = [ (x,y) for (x,y) in ejes if (x in marcadosl1 and y in marcadosl2) ]
    print "ejesPuestos: ", ejesPuestos
    for each in ejesSinPoner:
	(x,y) = each
	cantCruces = None
	Pos = (None, None)
        p1Parcial.remove(x)
        p2Parcial.remove(y)
	print "p1parcial",p1Parcial
	print "p2parcial",p2Parcial
	for i in range(len(grafo.p1)+1):
             for j in range(len(grafo.p2)+1):
		if self._esPosibleInsertar(x,y,p1Parcial,p2Parcial,i,j,marcadosl1,marcadosl2):
		    ejesAMirar = [(k,j) for (k,j) in ejesPuestos if k==x or j == y]
                    actual =self._contarCruces(p1Parcial[0:i]+[x]+p1Parcial[i:],p2Parcial[0:i]+[y]+p2Parcial[i:],ejesPuestos,x,y,ejesAMirar)
                    if cantCruces == None or actual < cantCruces:
                            cantCruces=actual
                            pos=(i,j)
                else:
		     pass

        ejesPuestos.append((x,y))
        p1Parcial.insert(pos[0],x)
        p2Parcial.insert(pos[1],y)
    return Dibujo(grafo,p1Parcial,p2Parcial)
		
                 
a = GrafoBipartito(Set([1,2,3]),Set([4,5,6]),Set([(2,5),(3,4),(3,6),(1,6)]))
dib=Dibujo(a,[1,2],[4,5])
f = heuristicaFede(dib)
dibujo = f.resolver()
print(dibujo.l1)
print(dibujo.l2)

              