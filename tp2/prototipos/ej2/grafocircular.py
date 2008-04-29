#!/usr/bin/python
# -*- coding: iso-8859-1 -*-

class GrafoCircular:
    def __init__(self,n,acuerdos):
        self.n = n
        self.lista_acuerdos = acuerdos

        # creo la matriz de acuerdos
        self.acuerdos = []
        outp1 = open("test"+".txt","w")
        
        for i in range(n):
            self.acuerdos.append([0]*n)
            
        for a in acuerdos:
            self.acuerdos[a[0]][a[1]] = 1
            self.acuerdos[a[1]][a[0]] = 1
        self.m = sum([sum(x) for x in self.acuerdos]) / 2    
        outp1.write(str(n)+" "+str(self.m)+"\n")
        for i in range(n):
            for j in range(i,n):
                if self.acuerdos[i][j] == 1:
                    outp1.write(str(i+1)+" "+str(j+1)+"\n")
        outp1.write("0 0")    
        # FIXME: la version de produccion no lleva esto
        # cuantos acuerdos hay? (para benchmarking posterior)
        

        # operacion loca
        print "Sergio trolo!!!"

    def estanConectados(self,a,b):
        return bool(self.acuerdos[a][b])

    def __repr__(self):
        
        return '<GrafoCircular de %s ciudades y %s acuerdos>' % (self.n, self.m)
