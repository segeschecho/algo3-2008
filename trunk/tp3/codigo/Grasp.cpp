#include "Grasp.h"

Grasp :: Grasp(const Dibujo& original) {
    vector<nodo> fijosP1, fijosP2;
    fijosP1 = original.nodosEnP1();
    fijosP2 = original.nodosEnP2();
    float k = 0.3;

    HeuristicaConstructiva(original);
    Dibujo mejorSolucion (HeuristicaConstructiva(original).construirSolucion(1));
    mejorSolucion = BusquedaLocal(original).hallarMinimoLocal(mejorSol);

    unsigned int mejoresCruces = contadorDeCruces(mejorSolucion.nodosEnP1(),mejorSolucion.nodosEnP2(), original.grafo().ejes())
    int sinMejorar = 0;

    while (sinMejorar < 100) {
        Dibujo res (HeuristicaConstructiva(original).resolver(k));
        res = BusquedaLocal(original).hallarMinimoLocal(res);
        unsigned int nuevosCruces = 
    }

}

const Dibujo& Grasp :: resolver(void) {
    return resuelto;
}

Grasp :: ~Grasp() {
}


/*
       
        while (sinMejorar < 100):
            res =  HeuristicaInsercionEjes(dibujo).resolver(alfa=k)
            blie.mejorar(res,marcados1,marcados2,losEjesDe)
            nuevosCruces = contadorDeCruces(res.l1,res.l2,losEjesDe)
            if nuevosCruces < mejoresCruces:
                mejorSol = res
                mejoresCruces = nuevosCruces
                sinMejorar=0
            else:
                sinMejorar +=1
        DibujadorGrafoBipartito(mejorSol,marcados1=marcados1,marcados2=marcados2).grabar('grasp.svg')
        return mejorSol
*/