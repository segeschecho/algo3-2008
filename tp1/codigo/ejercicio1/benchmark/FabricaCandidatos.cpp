#include "FabricaCandidatos.h"
#include "contador.h"
// Esta clase tiene por objetivo generar numeros enteros
// en orden creciente para ser usados como candidatos a
// ser numeros primos.

FabricaCandidatos :: FabricaCandidatos() {
    numeroActual = 1;
    turno = 0;
    k = 1;
    operaciones = operaciones + 3;
}

int FabricaCandidatos :: siguiente() {
    operaciones = operaciones + 3;
    if (numeroActual == 1 || numeroActual == 2) {
        numeroActual += 1;
        operaciones ++;
        operaciones = operaciones + 3;
        return numeroActual;

    }
    operaciones = operaciones + 3;
    if ( numeroActual == 3 || numeroActual == 5) {
        operaciones++;
        numeroActual += 2;
        return numeroActual;

    } else {
        operaciones ++;
        if (turno == 0) {
            numeroActual = 6 * k + 5;
            operaciones ++;
            operaciones ++;
            k++;
            operaciones ++;
            turno = 1;
            operaciones ++;
        } else {
            numeroActual = 6 * k + 1;
            operaciones ++;
            operaciones ++;
            turno = 0;
            operaciones ++;
        }
    }
    return numeroActual;
}
