#include "FabricaCandidatos.h"

// Esta clase tiene por objetivo generar numeros enteros
// en orden creciente para ser usados como candidatos a 
// ser numeros primos.

FabricaCandidatos :: FabricaCandidatos() {
    numeroActual = 1;
    turno = true;
    k = 1;
}

unsigned long long int FabricaCandidatos :: siguiente() {
    if (numeroActual == 1 || numeroActual == 2) {
        numeroActual += 1;
    } else if (numeroActual == 3 || numeroActual == 5) {
        numeroActual += 2;
    } else {
        if (turno) {
            numeroActual = 6 * k + 5;
            k++;
        } else {
            numeroActual = 6 * k + 1;
        }
        
        turno = !turno;
    }
    return numeroActual;
}
