#include <iostream>
#include <cstdlib>
#include <string>

#include "FiltroGrafos.h"
#include "SolucionExacta.h"
#include "Grasp.h"
#include "cmdline/CmdLine.h"
#include "hr_time.h"

using namespace std;

void help() {
    cout << "Uso: ./cruces <params>" << endl;
    cout << "  -i file: archivo de entrada" << endl;
    cout << "  -o file: archivo de salida (se le agrega sufijo del método)" << endl;
    cout << "Métodos Posibles:" << endl;
    cout << "  -e: exacto" << endl;
    cout << "  -c: constructiva" << endl;
    cout << "  -l: búsqueda local" << endl;
    cout << "  -g: grasp" << endl;
    cout << "  -a: todas las heurísticas" << endl;
    cout << "  -t: todos los métodos" << endl;
    cout << "Método por defecto: -a " << endl;
    cout << endl;
}

int main(int argc, char* argv[]) {
    // inicializo el generador de numeros aleatorios
    srand(time(NULL));

    CCmdLine cmdLine;
    CStopWatch timer;

    bool todas=false, aproximados=false, constructiva=false,local=false,grasp=false,exacta=false;
    cout << endl;
    cout << "---------------------------------------------------------------------" << endl;
    cout << "Constructor de dibujos de grafos bipartitos" << endl;
    cout << "González, Martínez, Sainz-Trápaga" << endl;
    cout << "Algoritmos y Estructuras de Datos 3 - FCEN, UBA (2008)" << endl;
    cout << "---------------------------------------------------------------------" << endl << endl;

    if (cmdLine.SplitLine(argc, argv) < 1) {
        cout << "Se ejecutan métodos aproximados por defecto." << endl;
        cout << "Para ver las opciones utilice el parámetro -h." << endl << endl;
        aproximados = true;
    }
    else{
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

    string i, o;
    try {
        i = cmdLine.GetArgument("-i",0);
    }
    catch(...){
        i = "Tp3.in";
    }

    try {
        o = cmdLine.GetArgument("-o",0);
    }
    catch(...){
        o = "Tp3.out";
    }

    if(!(todas || aproximados || constructiva || local || grasp || exacta)){
        cout << "Se ejecutan métodos aproximados por defecto." << endl;
        cout << "Para ver las opciones utilice el parámetro -h." << endl << endl;
        aproximados = true;
    }

    ifstream f (i.c_str());
    if (!f.is_open()) {
        cout << endl << "ERROR: No se pudo abrir el archivo de entrada!" << endl;
        help();
        return 1;
    }
    ofstream outE,outL,outG,outC;
    if(todas || exacta){
        string salidaExacta = o;
        string :: iterator it = salidaExacta.begin();
        while(it != salidaExacta.end() && *it != '.'){
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

    if(todas || aproximados || constructiva){
        string salidaConstructiva = o;
        string :: iterator it = salidaConstructiva.begin();
        while(it != salidaConstructiva.end() && *it != '.'){
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

    if(todas || aproximados || local){
        string salidaLocal = o;
        string :: iterator it = salidaLocal.begin();
        while(it != salidaLocal.end() && *it != '.'){
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

    if(todas || aproximados || grasp){
        string salidaGrasp = o;
        string :: iterator it = salidaGrasp.begin();
        while(it != salidaGrasp.end() && *it != '.'){
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

    ofstream tiempos("tiempos.m");
    ofstream cruces("cruces.m");

    tiempos << "tiempos = [\n";
    tiempos.precision(20);
    cruces << "cruces = [\n";
    while(f.peek() != '-'){
        timer.startTimer();
	    Dibujo d (f);
        FiltroGrafos filtro(d);

	    if(todas || exacta){
		    SolucionExacta s(*filtro.dibujoLimpio);
            Dibujo dib (s.resolver());
            unsigned int cantCruces = dib.contarCruces();
            cout << "El algoritmo exacto logró:         " << cantCruces << " cruces" << endl;
            cruces << cantCruces << endl;

            Dibujo reconstruido = filtro.reconstruirDibujo(dib);
            timer.stopTimer();
            reconstruido.guardar(outE);
	    }
	    if(todas || aproximados || constructiva){
            HeuristicaConstructiva hc(*filtro.dibujoLimpio);
            Dibujo dib = hc.construirSolucion(1.0, false);
            unsigned int cantCruces = dib.contarCruces();
            cout << "La heurística constructiva logró:  " << cantCruces << " cruces" << endl;
            cruces << cantCruces << endl;

            Dibujo reconstruido = filtro.reconstruirDibujo(dib);
            timer.stopTimer();
            reconstruido.guardar(outC);
	    }
	    if(todas || aproximados || local){
            HeuristicaConstructiva hc(*filtro.dibujoLimpio);
		    BusquedaLocal bl(*filtro.dibujoLimpio);
            Dibujo dib = hc.construirSolucion(1.0, false);
		    Dibujo dibu = bl.hallarMinimoLocal(dib);
            unsigned int cantCruces = dib.contarCruces();
            cout << "La búsqueda local logró:           " << cantCruces << " cruces" << endl;
            cruces << cantCruces << endl;

            Dibujo reconstruido = filtro.reconstruirDibujo(dibu);
            timer.stopTimer();
            reconstruido.guardar(outL);
	    }
	    if(todas || aproximados || grasp){
            Grasp gp(*filtro.dibujoLimpio);
            // FIXME: este parámetro está hardcodeado acá que probablemente
            // no es la mejor idea, no hay que olvidárselo.
            Dibujo dib (gp.resolver8(0.65));
            unsigned int cantCruces = dib.contarCruces();
            cout << "Grasp logró:                       " << cantCruces << " cruces" << endl;
            cruces << cantCruces << endl;

		    Dibujo reconstruido = filtro.reconstruirDibujo(dib);
            timer.stopTimer();
            reconstruido.guardar(outG);
	    }
        unsigned int fin = clock();
        tiempos << timer.getElapsedTime() << endl;
        f.ignore(2, '\n');
    }
    tiempos << "];\n";
    cruces << "];\n";
    tiempos.close();
    cruces.close();
    if(todas || exacta){
	    outE.close();
    }
    if(todas || aproximados || constructiva){
	    outC.close();
    }
    if(todas || aproximados || local){
	    outL.close();
    }
    if(todas || aproximados || grasp){
	    outG.close();
    }
    cout << endl;
    return 0;
}
