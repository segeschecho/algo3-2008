#include <iostream>
#include <cstdlib>
#include "FiltroGrafos.h"
#include "SolucionExacta.h"
#include "Grasp.h"
#include "cmdline/CmdLine.h"
#include <string>
#include "hr_time.h"
static CStopWatch* timer;
static CStopWatch* timer2;
using namespace std;

void help() {
	
    cout << "Uso ./cruces <params>"<<endl;
	cout << "-i file: archivo de entrada"<<endl;
	cout << "-o file: archivo de salida (se le agrega postfijo de metodo)"<<endl;
	cout << "Metodos Posibles: "<< endl;
	cout << "-e: exacto        "<<endl;
	cout << "-c: contructiva   "<<endl;
	cout << "-l: local         "<<endl;
	cout << "-g: grasp         "<<endl;
	cout << "-a: todas las aproximadas"<<endl;
	cout << "-t: todos los metodos"<<endl;
	cout << "por defecto: -a "<<endl;
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
	ofstream outE,outL,outG,outC,salidaTest,salidaCruces,salidaTestConst,salidaCrucesConst;
	ofstream grasp1,grasp2,grasp3,grasp4,grasp5,grasp6,grasp7,grasp8;
	string g1,g2,g3,g4,g5,g6,g7,g8;
	g1=i;
	g1.append("1.m");
	g2=i;
	g2.append("2.m");
	g3=i;
	g3.append("3.m");
	g4=i;
	g4.append("4.m");
	g5=i;
	g5.append("5.m");
	g6=i;
	g6.append("6.m");
	g7=i;
	g7.append("7.m");
	g8=i;
	g8.append("8.m");
	ofstream grasp1t,grasp2t,grasp3t,grasp4t,grasp5t,grasp6t,grasp7t,grasp8t;
	string g1t,g2t,g3t,g4t,g5t,g6t,g7t,g8t;
	g1t=i;
	g1t.append("1t.m");
	g2t=i;
	g2t.append("2t.m");
	g3t=i;
	g3t.append("3t.m");
	g4t=i;
	g4t.append("4t.m");
	g5t=i;
	g5t.append("5t.m");
	g6t=i;
	g6t.append("6t.m");
	g7t=i;
	g7t.append("7t.m");
	g8t=i;
	g8t.append("8t.m");
	grasp1t.open(g1t.c_str());
	grasp2t.open(g2t.c_str());
	grasp3t.open(g3t.c_str());
	grasp4t.open(g4t.c_str());
	grasp5t.open(g5t.c_str());
	grasp6t.open(g6t.c_str());
	grasp7t.open(g7t.c_str());
	grasp8t.open(g8t.c_str());
	grasp1.open(g1.c_str());
	grasp2.open(g2.c_str());
	grasp3.open(g3.c_str());
	grasp4.open(g4.c_str());
	grasp5.open(g5.c_str());
	grasp6.open(g6.c_str());
	grasp7.open(g7.c_str());
	grasp8.open(g8.c_str());
	grasp1<<"g1=[";
	grasp2<<"g2=[";
	grasp3<<"g3=[";
	grasp4<<"g4=[";
	grasp5<<"g5=[";
	grasp6<<"g6=[";
	grasp7<<"g7=[";
	grasp8<<"g8=[";
	grasp1t<<"t1=[";
	grasp2t<<"t2=[";
	grasp3t<<"t3=[";
	grasp4t<<"t4=[";
	grasp5t<<"t5=[";
	grasp6t<<"t6=[";
	grasp7t<<"t7=[";
	grasp8t<<"t8=[";
	string tiempos,cruces,crucesC,tiemposC;
	tiempos = i;
	string tlocal = "tiempoLocal.m";
	string clocal = "crucesLocal.m"; 
	string clocalc = "crucesLocalC.m";
	string tlocalc = "tiempoLocalC.m";
	tiempos.append(tlocal);
	cruces=i;
	cruces.append(clocal);
	salidaTest.open(tiempos.c_str());
	salidaCruces.open(cruces.c_str());
	salidaCruces<<"cruces=[";
	salidaTest<<"tiempo=[";
	crucesC = i;
	tiemposC = i;
	tiemposC.append(tlocalc);
	crucesC.append(clocalc);
    salidaTestConst.open(tiemposC.c_str());
	salidaCrucesConst.open(crucesC.c_str());
	salidaCrucesConst<<"crucesC=[";
	salidaTestConst<<"tiempoC=[";
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
    cout<<"iter=[";
	while(f.peek() != '-'){
		Dibujo d (f);
		timer= new CStopWatch();
		timer->startTimer();
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
			timer->stopTimer( );
			salidaTestConst<<timer->getElapsedTime();
			salidaTestConst<<" ";
			salidaCrucesConst<< dib.contarCruces()<<" ";
            reconstruido.guardar(outC);
			delete timer;
		}
		if(todas || aproximados || local){
			timer= new CStopWatch();
			timer2= new CStopWatch();
			timer->startTimer();
			timer2->startTimer();
            HeuristicaConstructiva hc(*filtro.dibujoLimpio);
			BusquedaLocal bl(*filtro.dibujoLimpio);
            Dibujo dib = hc.construirSolucion();
			timer2->stopTimer( );
            salidaTestConst<<timer2->getElapsedTime();
			salidaTestConst<<" ";
			salidaCrucesConst<< dib.contarCruces()<<" ";
			Dibujo dibu = bl.hallarMinimoLocal(dib);
			timer->stopTimer( );
			salidaTest<<timer->getElapsedTime();
			salidaTest<<" ";
			salidaCruces<< dibu.contarCruces()<<" ";
            //cout << "Heuristica Local logro: " << dibu.contarCruces() << " cruces." << endl;
            delete timer;
			delete timer2;
            //Dibujo reconstruido = filtro.reconstruirDibujo(dibu);
            //reconstruido.guardar(outL);
		}
		if(todas || aproximados || grasp){
            Grasp gp(*filtro.dibujoLimpio);
            /*timer= new CStopWatch();
			timer->startTimer();
            Dibujo dib1 (gp.resolver1(0.65));
			timer->stopTimer();
			grasp1<<dib1.contarCruces()<<" ";
			grasp1t<<timer->getElapsedTime()<<" ";
			delete timer;*/
			timer= new CStopWatch();
			timer->startTimer();
            Dibujo dib2 (gp.resolver2(0.65));
			timer->stopTimer();
			grasp2<<dib2.contarCruces()<<" ";
			grasp2t<<timer->getElapsedTime()<<" ";
			delete timer;
			/*timer= new CStopWatch();
			timer->startTimer();
            Dibujo dib3 (gp.resolver3(0.65));
			timer->stopTimer();
			grasp3<<dib3.contarCruces()<<" ";
			grasp3t<<timer->getElapsedTime()<<" ";
			delete timer;*/
			timer= new CStopWatch();
			timer->startTimer();
            Dibujo dib4 (gp.resolver4(0.65));
			timer->stopTimer();
			grasp4<<dib4.contarCruces()<<" ";
			grasp4t<<timer->getElapsedTime()<<" ";
			delete timer;
			/*timer= new CStopWatch();
			timer->startTimer();
            Dibujo dib5 (gp.resolver5(0.65));
			timer->stopTimer();
			grasp5<<dib5.contarCruces()<<" ";
			grasp5t<<timer->getElapsedTime()<<" ";
			delete timer;*/
			timer= new CStopWatch();
			timer->startTimer();
            Dibujo dib6 (gp.resolver6(0.65));
			timer->stopTimer();
			grasp6<<dib6.contarCruces()<<" ";
			grasp6t<<timer->getElapsedTime()<<" ";
			delete timer;
			/*timer= new CStopWatch();
			timer->startTimer();
            Dibujo dib7 (gp.resolver7(0.65));
			timer->stopTimer();
			grasp7<<dib7.contarCruces()<<" ";
			grasp7t<<timer->getElapsedTime()<<" ";
			delete timer;*/
			timer= new CStopWatch();
			timer->startTimer();
            Dibujo dib8 (gp.resolver8(0.65));
			timer->stopTimer();
			grasp8<<dib8.contarCruces()<<" ";
			grasp8t<<timer->getElapsedTime()<<" ";
			delete timer;
            cout << "Grasp logro: " << dib8.contarCruces() << " cruces." << endl;
            
			//Dibujo reconstruido = filtro.reconstruirDibujo(dib);
           // reconstruido.guardar(outG);
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
	f.close();
    
	cout<<"];";
	salidaTest<<"];";
	salidaCruces<<"]";
	salidaCruces.close();
	salidaTest.close();
	salidaTestConst<<"];";
	salidaCrucesConst<<"]";
	salidaCrucesConst.close();
	salidaTestConst.close();
    grasp1<<"];";
	grasp2<<"];";
	grasp3<<"];";
	grasp4<<"];";
	grasp5<<"];";
	grasp6<<"];";
	grasp7<<"];";
	grasp8<<"];";
	grasp1t<<"];";
	grasp2t<<"];";
	grasp3t<<"];";
	grasp4t<<"];";
	grasp5t<<"];";
	grasp6t<<"];";
	grasp7t<<"];";
	grasp8t<<"];";
	return 0;
}
