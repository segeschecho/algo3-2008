#include <iostream>
#include <string>

#include "PATRICIA_t.h"

using namespace std;

int main(int argc, char* argv[]) {
     string ruta;
    if(argc >= 2) {
        ruta = argv[1];
    } else {
        ruta="Tp2Ej3.in";
    }
    // preparo el archivo de salida
    string salida;
    if(argc > 2) {
        salida = argv[2];
    } else {
        salida = "Tp2Ej3.out";
    }
    int cant = 0;
    ifstream in(ruta.c_str(), ifstream::in);
    ofstream out(salida.c_str(), ifstream::out);

    if(!in.is_open()){
        cout << "no se encontro el archivo" << endl;
        return 1;
    }

    if(!out.is_open()){
        cout << "no se puede crear el archivo" << endl;
        return 1;
    }

    in >> cant;	
    while(cant > 0){
	PATRICIA *pat = new PATRICIA();
        for(int i = 0; i < cant; i++){

            string inst;
	    in >> inst;
            if(inst == "agregar"){
                //tomo la palabra
                in >> inst;
		//cout<<"agregando "<<inst<<endl;
                pat->agregar(inst);
            }
            else if(inst =="pertenece"){
                //tomo la palabra
                in >> inst;
                out << pat->pertenece(inst);
                if(i + 1 < cant)
                    out << " ";
            }
            else if(inst == "sacar"){
                //tomo la palabra
                in >> inst;
                pat->sacar(inst);
            }
            else if(inst =="cardinal"){
                out << pat->cardinal();
                if(i + 1 < cant)
                    out << " ";
            }
        }
	in>>cant;
	delete pat;
        
    }

    in.close();
    out.close();
    return 0;
 
}
    //patri.agregar("tatetito");
    /*cout << patri << endl << endl;
    patri.agregar("taqetito");
    cout << patri << endl << endl;
    patri.agregar("ttetito");
    cout << patri << endl << endl;

    cout << patri << endl << endl;
    patri.sacar("ttetito");
    cout << patri << endl << endl;
    patri.sacar("tatetito");
    cout << patri << endl << endl;
    patri.sacar("taqetito");
    cout << patri << endl << endl;
    patri.agregar("iii");
    patri.agregar("zero");
    patri.agregar("emiliano");
    patri.agregar("caballete");
    patri.agregar("anan");
    patri.agregar("caca");
    patri.agregar("cacona");
    patri.agregar("ze");

    patri.agregar("ana");
    patri.agregar("emi");
    patri.agregar("cacapupu");
    patri.agregar("cacique");
    patri.agregar("caconete");
    patri.agregar("emilio");
    patri.agregar("anana");

    cout << "VERDADEROS\n";
    patri.pertenece("iiii") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("i") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("iii") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("zero") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("emiliano") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("caballete") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("anan") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("caca") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("cacona") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("ze") ? cout << "TRUE" << endl : cout << "FALSE" << endl;

    patri.pertenece("ana") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("emi") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("cacapupu") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("cacique") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("caconete") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("emilio") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("anana") ? cout << "TRUE" << endl : cout << "FALSE" << endl;

    cout << "FALSOS\n";
    patri.pertenece("ananana") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("em") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("cac") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("caciques") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("caconeta") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("egmilio") ? cout << "TRUE" << endl : cout << "FALSE" << endl;
    patri.pertenece("emili") ? cout << "TRUE" << endl : cout << "FALSE" << endl;

    cout << patri << endl << endl;
    patri.sacar("iii");
    cout << patri << endl << endl;
    patri.sacar("i");
    cout << patri << endl << endl;
    patri.sacar("iiii");
    cout << patri << endl << endl;
    patri.sacar("emilio");
    cout << patri << endl << endl;
    patri.sacar("emiliano");
    cout << patri << endl << endl;
    patri.sacar("emi");
    cout << patri << endl << endl;
    patri.sacar("cacona");
    cout << patri << endl << endl;
    patri.sacar("cacique");
    cout << patri << endl << endl;
    patri.sacar("caconete");
    cout << patri << endl << endl;
    patri.sacar("caballete");
    cout << patri << endl << endl;
    patri.sacar("caca");
    cout << patri << endl << endl;
    patri.sacar("cacapupu");
    cout << patri << endl << endl;
    patri.sacar("ze");
    cout << patri << endl << endl;
    patri.sacar("anana");
    cout << patri << endl << endl;
    patri.sacar("anan");
    cout << patri << endl << endl;
    patri.sacar("ana");
    cout << patri << endl << endl;
    patri.sacar("zero");
    cout << patri << endl << endl;
    system("PAUSE");
    return 0;
}*/
