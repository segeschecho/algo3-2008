#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

#include "Grafo.h"
#include "BuscadorCaminoTCI.h"

using namespace std;


void test_grafo() {
    pair<unsigned, unsigned> p1 = make_pair(0,1);
    pair<unsigned, unsigned> p2 = make_pair(0,2);
    pair<unsigned, unsigned> p3 = make_pair(3,4);

    list<pair<unsigned, unsigned> > l;
    l.push_back(p1);
    l.push_back(p2);
    l.push_back(p3);
    l.push_back(p3);

    Grafo g = Grafo(5, l);
    assert(!(g.estanConectados(2,4)));
    assert(!(g.estanConectados(0,3)));
    assert(g.estanConectados(0,1));
    assert(g.estanConectados(0,2));
    assert(g.estanConectados(3,4));
    assert(g.estanConectados(4,3));
    assert(g.n == 5);
    assert(g.m == 3);
    cout << "Grafo: todos los tests pasaron satisfactoriamente!" << endl;
}


void test_buscadorcamino() {
    list<pair<unsigned,unsigned> > l;
    l.push_back(make_pair(1,2));
    l.push_back(make_pair(2,3));
    l.push_back(make_pair(2,4));
    l.push_back(make_pair(2,5));
    l.push_back(make_pair(3,0));
    l.push_back(make_pair(4,0));
    l.push_back(make_pair(4,5));

    Grafo g = Grafo(6,l);
    BuscadorCaminoTCI b = BuscadorCaminoTCI(g);
    b.buscarCamino();
    cout << "BuscadorCaminoTCI: todos los tests pasaron satisfactoriamente!" << endl;
}



void help() {
    cout << "Uso ./barcos <infile> <outfile>" << endl;
    cout << "  o ./barcos (sin parametros)" << endl;
    cout << "En el caso de la llamada sin parametros se toman los archivos" << endl;
    cout << "Tp2Ej2.in y Tp2Ej2.out como valores por defecto." << endl;
}


int main(int argc, char* argv[]) {
    // leo los datos de entrada
    string ruta;
    if(argc >= 2) {
        ruta = argv[1];
    } else {
        ruta="Tp2Ej2.in";
    }
    fstream f (ruta.c_str());
    if(!f.is_open()) {
        cout << endl << "ERROR: No se pudo abrir el archivo de entrada!" << endl << endl;
        help();
        return 1;
    }

    // preparo el archivo de salida
    string salida;
    if(argc > 2) {
        salida = argv[2];
    } else {
        salida = "Tp2Ej2.out";
    }
    ofstream o(salida.c_str());

    int n, m;
    int a, b;

    while(true) {
        f >> n;
        f >> m;
        if (n == 0 && m == 0) {
            break;
        }

        cout << "Buscando caminos con " << n << " ciudades y ";
        cout << m << " acuerdos comerciales..." << endl;
        list<pair<unsigned, unsigned> > l;
        for(int i = 0; i < m; i++) {
            // el resolvedor usa indices de 0 a m-1, pero el
            // archivo provee indices entre 1 y m.
            f >> a; a--;
            f >> b; b--;
            l.push_back(make_pair(a,b));
        }
        Grafo g(n, l);
        BuscadorCaminoTCI b(g);
        b.guardarCamino(o);
    }
}
