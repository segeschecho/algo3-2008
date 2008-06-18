#include "Tp3.h"
using namespace std;

int main(int argc, char* argv[]) {
    Dibujo d ("Tp3.in");
    cout << "Leido el archivo de entrada!" << endl;
    HeuristicaConstructiva h(d);
    h.construirSolucion();
    BusquedaLocal bl(d);
}
