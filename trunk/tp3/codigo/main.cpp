#include <iostream>
#include "Dibujo.h"
#include "GrafoBipartito.h"
#include <math.h>
#include "BusquedaLocal.h"
#include "Tp3.h"
#include "HeuristicaConstructiva.h"
using namespace std;
#define print(a) cout<<a<<endl;

int main(int argc, char* argv[]) {
    string metodo = "1";        //metodo por defecto: Heuristica constructiva
    if (argc >= 2) {
        metodo = argv[1];
    }

    string ruta;
    if (argc >= 3) {
        ruta = argv[2];
    } else {
        ruta="Tp3.in";
    }
    ifstream entrada (ruta.c_str(), ios_base::in);

    assert(entrada.is_open());

    // preparo el archivo de salida
    if (argc >= 4) {
        ruta = argv[3];
    } else {
        ruta = "Tp3";
        ruta.append(metodo);
        ruta.append(".out");
    }
    ofstream salida (ruta.c_str(), ios_base::out);
    assert(salida.is_open());

    if (metodo.compare("1") == 0) {
        while (entrada.peek() != '-') { // Termina cuando encuentra el '-1'
            //cargamos un dibujo
            Dibujo d (entrada);
            // Tp3 se encarga de limpiar el grafo. ya se q el nombre es choto
            Tp3 tp3(d);

            //generamos un heuristica constructiva con el grafo ya limpio
            HeuristicaConstructiva hc(*tp3.dibujoLimpio);
            Dibujo dib = hc.construirSolucion();
            cout << "Heuristica Constructiva logro: " << dib.contarCruces() << " cruces" << endl;

            //construimos un nuevo dibujo con el orden dado por la heuristica, pero los nombres de nodos correctos
            Dibujo reconstruido = tp3.reconstruirDibujo(dib);
            cout << "Reconstruyendo el dibujo nos dio " << reconstruido.contarCruces() << " cruces (debe ser igual que el anterior :P)" << endl;
            reconstruido.guardar(salida);

            entrada.ignore();   //ignoro el caracter de fin de linea ('\n')
        }
    }
    if (metodo.compare("2") == 0) {
/*
        //a partir del dibujo limpio tambien armamos la busqueda local
        BusquedaLocal bl(*tp3.dibujoLimpio);
        //pedimos que nos mejore el dibujo de la heur constructiva
        //nos da uno nuevo
        Dibujo minLoc = bl.hallarMinimoLocal(dib);
        cout << "Hallando el minimo local se logro: " << minLoc.contarCruces() << " cruces" << endl;
*/
        //aca va el greedy y busqueda local cuando esten listos
    }
    if (metodo.compare("3") == 0) {
        //aca va el grasp
    }
    entrada.close();
    salida.close();
    system("PAUSE");
    return 0;
}
