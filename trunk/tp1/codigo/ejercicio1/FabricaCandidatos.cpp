#include "FabricaCandidatos.h"

// Esta clase tiene por objetivo generar numeros enteros
// en orden creciente para ser usados como candidatos a 
// ser numeros primos.

FabricaCandidatos :: FabricaCandidatos() {
    numeroActual = 1;
    turno = 0;
    k = 1;
}

int FabricaCandidatos :: siguiente() {
    if (numeroActual == 1 || numeroActual == 2) {
        numeroActual += 1;
    } else if (numeroActual == 3 || numeroActual == 5) {
        numeroActual += 2;
    } else {
        if (turno == 0) {
            numeroActual = 6 * k + 5;
            k++;
            turno = 1;
        } else {
            numeroActual = 6 * k + 1;
            turno = 0;
        }
    }
    return numeroActual;
}
