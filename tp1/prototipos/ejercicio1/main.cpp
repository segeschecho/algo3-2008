#include <iostream>
#include <string>
#include <fstream>

#include <assert.h>
#include <math.h>

#include "FabricaCandidatos.h"

using namespace std;

void primoDeMayorPotencia(int n, int& primo, int& potencia) {
    assert(n > 1);

    int mejorPrimo = 1;
    int mejorPotencia = 0;

    FabricaCandidatos fab = FabricaCandidatos();
    int primoActual = fab.siguiente();
    int potenciaActual = 0;
    
    int s = (int) ceil(sqrt(n));

    while (n != 1) {
        // si me paso de la raiz, pruebo con el numero
        if (primoActual > s) {
            primoActual = n;
            potenciaActual = 1;
            break;
        }

        if (n % primoActual == 0) {
            potenciaActual++;
            n = n / primoActual;
        } else {
            if (potenciaActual >= mejorPotencia) {
                mejorPrimo = primoActual;
                mejorPotencia = potenciaActual;
            }

            potenciaActual = 0;
            primoActual = fab.siguiente();
            s = (int) ceil(sqrt(n));
        }
    }

    // vemos que ocurre con el ultimo primo
    if (potenciaActual >= mejorPotencia) {
        mejorPrimo = primoActual;
        mejorPotencia = potenciaActual;
    }
    
    primo = mejorPrimo;
    potencia = mejorPotencia;
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
    }
    return 0;
}
