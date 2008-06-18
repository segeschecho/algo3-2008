#include "Tp3.h"
using namespace std;

int main(int argc, char *argv[]) {
    string ruta;
    if(argc >= 2) {
        ruta = argv[1];
    } else {
        ruta="Tp3.in";
    }

    // preparo el archivo de salida
    string salida;
    if(argc > 2) {
        salida = argv[2];
    } else {
        salida = "Tp3.out";
    }

    Dibujo d (ruta);
    GrafoBipartito* gPtr = d.grafo();
    HeuristicaConstructiva(d).construirSolucion().guardar(salida);

    system("PAUSE");
    return 0;
}
