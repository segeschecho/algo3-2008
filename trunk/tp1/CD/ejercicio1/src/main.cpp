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
	// primo actual es un abuso de notacion por decirlo de algun modo, ya que no necesariamente es primo
    int primoActual = fab.siguiente();
    int potenciaActual = 0;
    int limite = n;

    while (n != 1 && primoActual*primoActual <= limite) {
        if (n % primoActual == 0) {
            potenciaActual++;
            n = n / primoActual;
        } else {
			// el primo no divide a n, hay que ver si hay que actualizar la potencia
            if (potenciaActual >= mejorPotencia) {
                mejorPrimo = primoActual;
                mejorPotencia = potenciaActual;
            }
            potenciaActual = 0;
			//nuevo candidato
            primoActual = fab.siguiente();
			// actualizamos el limite
			limite = n;
        }
    }
    if (primoActual*primoActual > limite) {
        primoActual = n;
        potenciaActual = 1;
    }

    // vemos que ocurre con el ultimo primo
    if (potenciaActual >= mejorPotencia) {
        mejorPrimo = primoActual;
        mejorPotencia = potenciaActual;
    }
    
    primo = mejorPrimo;
    potencia = mejorPotencia;
}

void help() {
    cout << "Uso ./primos <infile> <outfile>" << endl;
    cout << "  o ./primos (sin parametros)" << endl;
    cout << "En el caso de la llamada sin parametros se toman los archivos" << endl;
    cout << "Tp1Ej1.in y Tp1Ej1.out como valores por defecto." << endl;
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
