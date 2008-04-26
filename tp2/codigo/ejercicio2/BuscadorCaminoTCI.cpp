#include "BuscadorCaminoTCI.h"

// implementacion razonable de la operacion modulo
// G++ es un capo!
unsigned resto(int a, int b) {
    if (a < 0) {
        return a % b + b;
    } else {
        return a % b;
    }
}

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
        b = resto((i+1),g.n);
        if(g.estanConectados(a,b)) {
            matA[a][b] = true;
            matB[a][b] = true;
        }
    }

    // caso general
    for(unsigned i = 2; i < g.n; i++) {
        for(unsigned j = 0; j < g.n; j++) {
            a = j;
            amas1 = resto((a+1),g.n);
            b = resto((j+i),g.n);
            bmenos1 = resto((b-1),g.n);

            matA[a][b] = (g.estanConectados(a,amas1) && matA[amas1][b]) || 
                         (g.estanConectados(a,b) && matB[amas1][b]);
            matB[a][b] = (g.estanConectados(b,bmenos1) && matB[a][bmenos1]) || 
                         (g.estanConectados(a,b) && matA[a][bmenos1]);
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
        b = resto((i-1),g.n);
        list<unsigned>* lp;
        list<unsigned> lr;
        if (matA[a][b]) {
            lp = caminoQueTerminaEnA(a,b);
            lr = *lp;
            delete lp;
            return lr;
        }
        if (matB[a][b]) {
            lp = caminoQueTerminaEnB(a,b);
            lr = *lp;
            delete lp;
            return lr;
        }
    }
    return camino;
}


list<unsigned>* BuscadorCaminoTCI :: caminoQueTerminaEnA(unsigned a, unsigned b) {
    list<unsigned>* l = new list<unsigned>;
    if ((b-a) == 1 || (b == 0 && a == g.n-1)) {
        l->push_back(b);
        l->push_back(a);
        return l;
    }

    int amas1 = resto((a+1),g.n);
    l->push_back(a);
    list<unsigned> :: iterator it = l->begin();

    if (g.estanConectados(a,amas1) && matA[amas1][b]) {
        list<unsigned>* tmp1 = caminoQueTerminaEnA(amas1,b);
        l->splice(it,*tmp1);
        delete tmp1;
        return l;
    }
    if (g.estanConectados(a,b) && matB[amas1][b]) {
        list<unsigned>* tmp2 = caminoQueTerminaEnB(amas1,b);
        l->splice(it,*tmp2);
        delete tmp2;
        return l;
    }

    cout << "No existe el camino que se intento generar!" << endl;
    abort();
}


list<unsigned>* BuscadorCaminoTCI :: caminoQueTerminaEnB(unsigned a, unsigned b) {
    list<unsigned>* l = new list<unsigned>();
    if ((b-a) == 1 || (b == 0 && a == g.n-1)) {
        l->push_back(a);
        l->push_back(b);
        return l;
    }

    int bmenos1 = resto((b-1),g.n);
    l->push_back(b);
    list<unsigned> :: iterator it = l->begin();

    if (g.estanConectados(b,bmenos1) && matB[a][bmenos1]) {
        list<unsigned>* tmp1 = caminoQueTerminaEnB(a,bmenos1);
        l->splice(it,*tmp1);
        delete tmp1;
        return l;
    }
    if (g.estanConectados(a,b) && matA[a][bmenos1]) {
        list<unsigned>* tmp2 = caminoQueTerminaEnA(a,bmenos1);
        l->splice(it,*tmp2);
        delete tmp2;
        return l;
    }

    cout << "No existe el camino que se intento generar!" << endl;
    abort();
}


void BuscadorCaminoTCI :: imprimirCamino() {
    list<unsigned> l = buscarCamino();

    if (l.size() == 0) {
        cout << "[]";
    }
    else {
        list<unsigned> :: iterator it = l.begin();
        cout << "[" << *it;
        it++;
        while(it != l.end()) {
            cout << "," << *it;
            it++;
        }
        cout << "]";
    }
}


void BuscadorCaminoTCI :: guardarCamino(ostream& o) {
    list<unsigned> l = buscarCamino();
    if (l.size() == 0) {
        o << "-1" << endl;
    }
    else {
        list<unsigned> :: iterator it = l.begin();
        o << (*it+1);
        it++;
        while(it != l.end()) {
            o << " " << (*it+1);
            it++;
        }
        o << endl;
    }
}
