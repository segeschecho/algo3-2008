#include <iostream>
#include <string>
#include <fstream>

#include <assert.h>
#include <math.h>
#include <time.h>

#include "FabricaCandidatos.h"

using namespace std;

#define CANT_VECES 10000

void primoDeMayorPotencia(unsigned long long int n, unsigned long long int& primo, unsigned int& potencia) {
    assert(n > 1);

    unsigned long long int mejorPrimo = 1;
    unsigned int mejorPotencia = 0;

    FabricaCandidatos fab = FabricaCandidatos();
    unsigned long long int primoActual = fab.siguiente();
    unsigned int potenciaActual = 0;
    
    unsigned long long int s = (unsigned long long int) ceil(sqrt((long double)n));

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
            s = (unsigned long long int) ceil(sqrt((long double)n));
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
        ruta = "Tp1Ej1.in";
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
    
    unsigned long long int primo, n;
    unsigned int potencia;
    f >> n;

//    unsigned long long int i = CANT_VECES;
//    unsigned long long int inicio = clock();
//    while(i > 0) {
        while (n != 0) {
            primoDeMayorPotencia(n, primo, potencia);
            o << n << " " << primo << " " << potencia << endl;
            f >> n;
        }
//        i--;
//    }

//    cout << "Milisegundos: " << (double)(clock() - inicio)/CANT_VECES/CLOCKS_PER_SEC << endl;
//    cout << primo << " " << potencia << endl;

    return 0;
}