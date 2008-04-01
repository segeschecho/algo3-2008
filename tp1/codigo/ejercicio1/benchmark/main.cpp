#include <iostream>
#include <string>
#include <fstream>
#include "contador.h"
#include <assert.h>
#include <math.h>

#include "FabricaCandidatos.h"

using namespace std;

void primoDeMayorPotencia(int n, int& primo, int& potencia) {
    assert(n > 1);

    int mejorPrimo = 1;
    operaciones ++;
    int mejorPotencia = 0;
    operaciones ++;
    FabricaCandidatos fab = FabricaCandidatos();
    operaciones ++;
    int primoActual = fab.siguiente();
    operaciones ++;
    int potenciaActual = 0;
    operaciones ++;

    int s = (int) ceil(sqrt(n));
    operaciones =operaciones + 3;
    operaciones ++;
    while (n != 1) {
        // si me paso de la raiz, pruebo con el numero
        operaciones ++;
        if (primoActual > s) {
            primoActual = n;
            operaciones ++;
            potenciaActual = 1;
            operaciones ++;
            break;
        }
        operaciones ++;
        if (n % primoActual == 0) {

            potenciaActual++;
            operaciones ++;
            n = n / primoActual;
            operaciones ++;
        } else {
            operaciones ++;
            if (potenciaActual >= mejorPotencia) {
                mejorPrimo = primoActual;
                operaciones ++;
                mejorPotencia = potenciaActual;
                operaciones ++;
            }

            potenciaActual = 0;
            operaciones ++;
            primoActual = fab.siguiente();
            operaciones ++;
            s = (int) ceil(sqrt(n));
            operaciones = operaciones + 3;
        }
    }

    // vemos que ocurre con el ultimo primo
    operaciones ++;
    if (potenciaActual >= mejorPotencia) {
        operaciones ++;
        mejorPrimo = primoActual;
        operaciones ++;
        mejorPotencia = potenciaActual;
    }

    primo = mejorPrimo;
    operaciones ++;
    potencia = mejorPotencia;
    operaciones ++;
}

int main(int argc, char* argv[]) {
    // leo los datos de entrada
    string ruta;
    if(argc >= 2) {
        ruta = argv[1];
    } else {
        ruta="Tp1Ej1.in";
    }
    fstream f (ruta.c_str());
    assert(f.is_open());

    // preparo el archivo de salida
    string salida;
    if(argc > 2) {
        salida = argv[2];
    } else {
        salida = "Tp1Ej1.out";
    }
    ofstream o (salida.c_str());

    int primo, potencia;
    int n;
    f >> n;
    while (n != 0) {
        primoDeMayorPotencia(n, primo, potencia);
        o << n << " " << primo << " " << potencia << endl;
        f >> n;
        cout<<operaciones<<endl;
        operaciones = 0;
    }

    return 0;
}
