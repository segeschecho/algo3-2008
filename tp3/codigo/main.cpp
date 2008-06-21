#include <iostream>
#include <cstdlib>
#include "FiltroGrafos.h"
#include "SolucionExacta.h"
#include "Grasp.h"
#include "cmdline/CmdLine.h"
#include <string>
using namespace std;

void help() {
    cout << "Uso ./cruces <params>" << endl;
    cout << "-i file: archivo de entrada" << endl;
    cout << "-o file: archivo de salida (se le agrega postfijo de metodo)" << endl;
    cout << "Metodos Posibles:" << endl;
    cout << "-e: exacto" << endl;
    cout << "-c: contructiva" << endl;
    cout << "-l: local" << endl;
    cout << "-g: grasp" << endl;
    cout << "-a: todas las aproximadas" << endl;
    cout << "-t: todos los metodos" << endl;
    cout << "por defecto: -a " << endl;
}

int main(int argc, char* argv[]) {
    CCmdLine cmdLine;
    bool todas=false, aproximados=false, constructiva=false,local=false,grasp=false,exacta=false;
    if (cmdLine.SplitLine(argc, argv) < 1) {
        cout << "Se ejecutan metodos aproximados por defecto" << endl << endl;;
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
        cout << "Se ejecutan metodos aproximados por defecto" << endl << endl;;
        aproximados = true;
    }
    ifstream f (i.c_str());
    if (!f.is_open()) {
        cout << endl << "ERROR: No se pudo abrir el archivo de f!" << endl;
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

    while(f.peek() != '-'){
	    Dibujo d (f);
        FiltroGrafos filtro(d);
    	
	    if(todas || exacta){
		    SolucionExacta s(*filtro.dibujoLimpio);
            Dibujo dib (s.resolver());
            cout << "El algoritmo exacto logro: " << dib.contarCruces() << " cruces." << endl;
            
            Dibujo reconstruido = filtro.reconstruirDibujo(dib);
            reconstruido.guardar(outE);
	    }
	    if(todas || aproximados || constructiva){
            HeuristicaConstructiva hc(*filtro.dibujoLimpio);
            Dibujo dib = hc.construirSolucion();
            cout << "Heuristica Constructiva logro: " << dib.contarCruces() << " cruces." << endl;
            
            Dibujo reconstruido = filtro.reconstruirDibujo(dib);
            reconstruido.guardar(outC);
	    }
	    if(todas || aproximados || local){
            HeuristicaConstructiva hc(*filtro.dibujoLimpio);
		    BusquedaLocal bl(*filtro.dibujoLimpio);
            Dibujo dib = hc.construirSolucion();
		    cout<<dib<<endl;
		    Dibujo dibu = bl.hallarMinimoLocal(dib);
		    cout<<dibu<<endl;
            cout << "Heuristica Local logro: " << dibu.contarCruces() << " cruces." << endl;

            Dibujo reconstruido = filtro.reconstruirDibujo(dibu);
            reconstruido.guardar(outL);
	    }
	    if(todas || aproximados || grasp){
            Grasp gp(*filtro.dibujoLimpio);
            Dibujo dib (gp.resolver(0.65));
            cout << "Grasp logro: " << dib.contarCruces() << " cruces." << endl;
            
		    Dibujo reconstruido = filtro.reconstruirDibujo(dib);
            reconstruido.guardar(outG);
	    }

        f.ignore(2, '\n');
    }
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
    return 0;
}
