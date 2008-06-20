#include <iostream>
#include "FiltroGrafos.h"
#include "SolucionExacta.h"
#include "Grasp.h"

using namespace std;

void help() {
    cout << "Uso ./cruces <metodo> <infile> <outfile>" << endl;
    cout << "  o ./cruces <metodo>" << endl;
    cout << "En la llamada sin parametros se toma Tp3.in y Tp3.out por defecto" << endl;
    cout << "Metodos posibles: exacto, constructivo, mejora, grasp" << endl;
}

int main(int argc, char* argv[]) {
    string metodo = "constructivo";
    if (argc >= 2) {
        metodo = argv[1];
        if (!(metodo.compare("constructivo") == 0 ||
             metodo.compare("exacto") == 0 ||
             metodo.compare("mejora") == 0 ||
             metodo.compare("grasp") == 0)) {
            cout << endl << "ERROR: El metodo " << metodo << " no es valido!" << endl;
            help();
            return 1;
        }
    }


    string ruta = "Tp3.in";
    string salida = "Tp3.out";
    
    if (argc == 4) {
        ruta = argv[2];
        salida = argv[3];
    }

    if (argc != 4 && argc != 2) {
        cout << endl << "ERROR: El formato de los parámetros es incorrecto!" << endl;
        help();
        return 1;
    }

    ifstream f (ruta.c_str());
    if (!f.is_open()) {
        cout << endl << "ERROR: No se pudo abrir el archivo de f!" << endl;
        help();
        return 1;
    }

    ofstream o (salida.c_str());
    if (!o.is_open()) {
        cout << endl << "ERROR: No se pudo abrir el archivo de salida!" << endl;
        help();
        return 1;
    }


    if (metodo.compare("constructivo") == 0) {
        while (f.peek() != '-') {
            Dibujo d (f);
            FiltroGrafos filtro(d);

            HeuristicaConstructiva hc(*filtro.dibujoLimpio);
            Dibujo dib = hc.construirSolucion();
            cout << "Heuristica Constructiva logro: " << dib.contarCruces() << " cruces." << endl;
            
            Dibujo reconstruido = filtro.reconstruirDibujo(dib);
            reconstruido.guardar(o);

            f.ignore(2, '\n');
        }
    }
    else if (metodo.compare("mejora") == 0) {
        // FIXME
        cout << "Emilio trolo!!" << endl;
    }
    else if (metodo.compare("grasp") == 0) {
        while (f.peek() != '-') {
            Dibujo d (f);
            FiltroGrafos filtro(d);

            Grasp gp(*filtro.dibujoLimpio);
            Dibujo dib (gp.resolver(1));
            cout << "Grasp logro: " << dib.contarCruces() << " cruces." << endl;

            Dibujo reconstruido = filtro.reconstruirDibujo(dib);
            reconstruido.guardar(o);

            f.ignore(2,'\n');
        }
    }
    else if (metodo.compare("exacto") == 0) {
        while (f.peek() != '-') {
            Dibujo d(f);
            FiltroGrafos filtro(d);
            
            SolucionExacta s(*filtro.dibujoLimpio);
            Dibujo dib (s.resolver());
            cout << "El algoritmo exacto logro: " << dib.contarCruces() << " cruces." << endl;
            
            Dibujo reconstruido = filtro.reconstruirDibujo(dib);
            reconstruido.guardar(o);

            f.ignore(2,'\n');
        }
    }
    f.close();
    o.close();
    return 0;
}
