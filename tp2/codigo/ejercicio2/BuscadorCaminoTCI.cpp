#include "BuscadorCaminoTCI.h"

BuscadorCaminoTCI :: BuscadorCaminoTCI(Grafo& grafo) : g(grafo) {
    resuelto = false;
    // pido memoria para las matrices
    // donde cacheo los resultados del resolvedor
    matA = new bool*[g.n];
    matB = new bool*[g.n];
    for(unsigned i = 0; i < g.n; i++) {
        matA[i] = new bool[g.n];
        matB[i] = new bool[g.n];
    }

    // lleno la matriz de falses
    for(unsigned i = 0; i < g.n; i++) {
        for(unsigned j = 0; j < g.n; j++) {
            matA[i][j] = false;
            matB[i][j] = false;
        }
    }
}


BuscadorCaminoTCI :: ~BuscadorCaminoTCI() {
    for(unsigned i = 0; i < g.n; i++) {
        delete[] matA[i];
        delete[] matB[i];
    }
    delete[] matA;
    delete[] matB;
}


void BuscadorCaminoTCI :: resolver() {
    if (resuelto) {
        return;
    }

    int a, amas1;
    int b, bmenos1;

    // caso base
    for(unsigned i = 0; i < g.n; i++) {
        a = i;
        b = (i+1) % g.n;
        if(g.estanConectados(a,b)) {
            matA[a][b] = true;
            matB[a][b] = true;
        }
    }

    // caso general
    for(unsigned i = 2; i < g.n; i++) {
        for(unsigned j = 0; j < g.n; j++) {
            a = j;
            amas1 = (a+1) % g.n;
            b = (j+i) % g.n;
            bmenos1 = (b-1) % g.n;

            matA[a][b] = (matA[a][amas1] && matA[amas1][b]) || (matA[a][b] && matB[amas1][b]);
            matB[a][b] = (matA[b][bmenos1] && matB[a][bmenos1]) || (matA[a][b] && matA[a][bmenos1]);
        }
    }

    resuelto = true;
}

list<unsigned> BuscadorCaminoTCI :: buscarCamino() {
    if (g.m < (g.n - 1)) {
        return camino;
    }

    if (!resuelto) {
        resolver();
    }

    // me fijo si hay algun camino posible - de haberlo, lo construyo y devuelvo
    // en caso contrario devuelvo camino (es una lista vacia)
    int a, b;
    for(unsigned i = 0; i < g.n; i++) {
        a = i;
        b = (i-1) % g.n;

        if (matA[a][b]) {
            return caminoQueTerminaEnA(a,b);
        }
        if (matB[a][b]) {
            return caminoQueTerminaEnB(a,b);
        }
    }

    return camino;
}


list<unsigned> BuscadorCaminoTCI :: caminoQueTerminaEnA(unsigned a, unsigned b) {
    list<unsigned> l;
    if ((b-a) == 1 || (b == 0 && a == g.n-1)) {
        l.push_back(b);
        l.push_back(a);
        return l;
    }

    int amas1 = (a+1) % g.n;
    list<unsigned> tmp;
    list<unsigned> :: iterator it = l.begin();
    l.push_back(a);

    if (matA[a][amas1] && matA[amas1][b]) {
        caminoQueTerminaEnA(amas1,b).swap(tmp);
        l.splice(it,tmp);
        return l;
    }
    if (matA[a][b] && matB[amas1][b]) {
        caminoQueTerminaEnB(amas1,b).swap(tmp);
        l.splice(it,tmp);
        return l;
    }

    cout << "No existe el camino que se intento generar!" << endl;
    abort();
}


list<unsigned> BuscadorCaminoTCI :: caminoQueTerminaEnB(unsigned a, unsigned b) {
    list<unsigned> l;
    if ((b-a) == 1 || (b == 0 && a == g.n-1)) {
        l.push_back(a);
        l.push_back(b);
        return l;
    }

    int bmenos1 = (b-1) % g.n;
    list<unsigned> tmp;
    list<unsigned> :: iterator it = l.begin();
    l.push_back(b);

    if (matA[b][bmenos1] && matB[a][bmenos1]) {
        caminoQueTerminaEnB(a,bmenos1).swap(tmp);
        l.splice(it,tmp);
        return l;
    }
    if (matA[a][b] && matA[a][bmenos1]) {
        caminoQueTerminaEnA(a,bmenos1).swap(tmp);
        l.splice(it,tmp);
        return l;
    }

    cout << "No existe el camino que se intento generar!" << endl;
    abort();
}
