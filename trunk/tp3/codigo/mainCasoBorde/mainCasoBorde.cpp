#include <iostream>
#include <cstdlib>
#include <string>

#include "FiltroGrafos.h"
#include "SolucionExacta.h"
#include "Grasp.h"
#include "cmdline/CmdLine.h"

using namespace std;

void help() {
    cout << "Uso: ./cruces <params>" << endl;
    cout << "  -i inicio: cantidad de nodos del primer caso a ejecutar" << endl;
    cout << "  -f fin: cantidad de nodos del ultimo caso a ejecutar" << endl;
    cout << "  -o file: archivo de salida (se le agrega sufijo del método)" << endl;
    cout << "Métodos Posibles:" << endl;
    cout << "  -e: exacto" << endl;
    cout << "  -c: constructiva" << endl;
    cout << "  -l: búsqueda local" << endl;
    cout << "  -g: grasp" << endl;
    cout << "  -a: todas las heurísticas" << endl;
    cout << "  -t: todos los métodos" << endl;
    cout << "Método por defecto: -a " << endl;
    cout << "Valores por defecto de inicio y fin: 5 y 99 respectivamente" << endl;
    cout << "Parametros inicio y fin deben cumplir que: son impares, mayores que 5, y inicio < fin";
    cout << endl;
}

void armarCasoBordeConstructiva(vector<nodo>& fijos1, vector<nodo>& fijos2, vector<nodo>& todos1, vector<nodo>& todos2, list<eje>& listaEjes, unsigned int size) {
    nodo v = 0;

    while (v < (size - 3)/2) {
        todos1.push_back(v);
        fijos1.push_back(v);
        v++;
    }

    while (v < (size - 3)/2 + 2) {
        todos2.push_back(v);
        fijos2.push_back(v);
        v++;
    }

    // hay 1 solo movil en la particion 1
    todos1.push_back(v);
    v++;

    while (v < size) {
        todos2.push_back(v);
        v++;
    }

    // ahora armo la lista de ejes
    vector<nodo>::const_iterator it1 (todos1.begin());
    vector<nodo>::const_iterator it2 (todos2.begin());
    // salteo los 2 fijos de p2
    it2++;
    it2++;

    for (unsigned int i = 0; i < todos1.size() - 1; i++) {
        eje e;
        e.primero = *it1;
        e.segundo = *it2;
        listaEjes.push_back(e);
        it1++;
        it2++;
    }

    eje e;
    e.primero = *it1;
    e.segundo = *(todos2.begin());
    listaEjes.push_back(e);
    e.segundo = *(todos2.begin() + 1);
    listaEjes.push_back(e);
    e.segundo = *(todos2.begin() + 2);
    listaEjes.push_back(e);
}

int main(int argc, char* argv[]) {
    // inicializo el generador de numeros aleatorios
    srand(time(NULL));

    CCmdLine cmdLine;
    bool todas=false, aproximados=false, constructiva=false,local=false,grasp=false,exacta=false;
    cout << endl;
    cout << "---------------------------------------------------------------------" << endl;
    cout << "Constructor de dibujos de grafos bipartitos a partir de un caso borde" << endl;
    cout << "González, Martínez, Sainz-Trápaga" << endl;
    cout << "Algoritmos y Estructuras de Datos 3 - FCEN, UBA (2008)" << endl;
    cout << "---------------------------------------------------------------------" << endl << endl;

    if (cmdLine.SplitLine(argc, argv) < 1) {
        cout << "Se ejecutan métodos aproximados por defecto." << endl;
        cout << "Para ver las opciones utilice el parámetro -h." << endl << endl;
        aproximados = true;
    } else {
        if (cmdLine.HasSwitch("-h")) {
            help();
            exit(0);
        }

        if (cmdLine.HasSwitch("-a")) {
            aproximados = true;
        }
        if (cmdLine.HasSwitch("-t")) {
            todas = true;
        }
        if (cmdLine.HasSwitch("-c")) {
            constructiva = true;
        }
        if (cmdLine.HasSwitch("-l")) {
            local = true;
        }
        if (cmdLine.HasSwitch("-g")) {
            grasp = true;
        }
        if (cmdLine.HasSwitch("-e")) {
            exacta = true;
        }
    }

    unsigned int desde, hasta;
    try {
        desde = atoi(cmdLine.GetArgument("-i",0).c_str());
    } catch (...) {
        desde = 5;
    }

    try {
        hasta = atoi(cmdLine.GetArgument("-f",0).c_str());
    } catch (...) {
        hasta = 99;
    }

    if ((desde < 5) || (hasta < 5) || (desde > hasta) || (desde % 2 == 0) || (hasta % 2 == 0)) {
        cout << "Parametros inicio y/o fin invalidos. Seteados a valores por defecto." << endl;
        desde = 5;
        hasta = 99;
    }

    string o;

    try {
        o = cmdLine.GetArgument("-o",0);
    } catch (...) {
        o = "Tp3.out";
    }

    if (!(todas || aproximados || constructiva || local || grasp || exacta)) {
        cout << "Se ejecutan métodos aproximados por defecto." << endl;
        cout << "Para ver las opciones utilice el parámetro -h." << endl << endl;
        aproximados = true;
    }

    ofstream outE,outL,outG,outC;
    if (todas || exacta) {
        string salidaExacta = o;
        string :: iterator it = salidaExacta.begin();
        while (it != salidaExacta.end() && *it != '.') {
            it++;
        }
        salidaExacta.insert(it,'E');

        outE.open(salidaExacta.c_str());
        if (!outE.is_open()) {
            cout << endl << "ERROR: No se pudo abrir el archivo de salida!" << endl;
            help();
            return 1;
        }
    }

    if (todas || aproximados || constructiva) {
        string salidaConstructiva = o;
        string :: iterator it = salidaConstructiva.begin();
        while (it != salidaConstructiva.end() && *it != '.') {
            it++;
        }
        salidaConstructiva.insert(it,'C');
        outC.open(salidaConstructiva.c_str());
        if (!outC.is_open()) {
            cout << endl << "ERROR: No se pudo abrir el archivo de salida!" << endl;
            help();
            return 1;
        }
    }

    if (todas || aproximados || local) {
        string salidaLocal = o;
        string :: iterator it = salidaLocal.begin();
        while (it != salidaLocal.end() && *it != '.') {
            it++;
        }
        salidaLocal.insert(it,'L');
        outL.open(salidaLocal.c_str());
        if (!outL.is_open()) {
            cout << endl << "ERROR: No se pudo abrir el archivo de salida!" << endl;
            help();
            return 1;
        }
    }

    if (todas || aproximados || grasp) {
        string salidaGrasp = o;
        string :: iterator it = salidaGrasp.begin();
        while (it != salidaGrasp.end() && *it != '.') {
            it++;
        }
        salidaGrasp.insert(it,'G');
        outG.open(salidaGrasp.c_str());
        if (!outG.is_open()) {
            cout << endl << "ERROR: No se pudo abrir el archivo de salida!" << endl;
            help();
            return 1;
        }
    }
    unsigned lecturas = 0;
    for (unsigned int i = desde; i <= hasta; i+=2) {
        vector<nodo> fijos1;
        vector<nodo> fijos2;
        vector<nodo> todos1;
        vector<nodo> todos2;
        list<eje> listaEjes;
		armarCasoBordeConstructiva(fijos1, fijos2, todos1, todos2, listaEjes, i);
        GrafoBipartito g (todos1, todos2, listaEjes);
        Dibujo d (&g, fijos1, fijos2);

        if (todas || exacta) {
            if(lecturas != 0){
                outE<<endl;
		    }
			SolucionExacta s(d);
            Dibujo dib (s.resolver());
            cout << "El algoritmo exacto logró:         " << dib.contarCruces() << " cruces" << endl;
            dib.guardar(outE);
        }
        if (todas || aproximados || constructiva) {
			if (lecturas != 0){
				outC<<endl;
			}
            HeuristicaConstructiva hc(d);
            Dibujo dib = hc.construirSolucion(1.0, false);
            cout << "La heurística constructiva logró:  " << dib.contarCruces() << " cruces" << endl;
            dib.guardar(outC);
        }
        if (todas || aproximados || local) {
			if(lecturas != 0){
				outL<<endl;
			}
			HeuristicaConstructiva hc(d);
            BusquedaLocal bl(d);
            Dibujo dib = hc.construirSolucion(1.0, false);
            Dibujo dibu = bl.hallarMinimoLocal(dib);
            cout << "La búsqueda local logró:           " << dibu.contarCruces() << " cruces" << endl;
            dibu.guardar(outL);
        }
        if (todas || aproximados || grasp) {
			if(lecturas != 0){
				outG<<endl;
			}
			Grasp gp(d);
            Dibujo dib (gp.resolver());
            cout << "Grasp logró:                       " << dib.contarCruces() << " cruces" << endl;
            dib.guardar(outG);
        }

        lecturas++;
    }
    if (todas || exacta) {
        outE.close();
    }
    if (todas || aproximados || constructiva) {
        outC.close();
    }
    if (todas || aproximados || local) {
        outL.close();
    }
    if (todas || aproximados || grasp) {
        outG.close();
    }
    cout << endl;
    return 0;
}
