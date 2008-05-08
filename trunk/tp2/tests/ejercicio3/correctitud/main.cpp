#include <iostream>
#include <string>
#include <assert.h>
#include "PATRICIA_t.h"

using namespace std;

void generarEntrada(void)
{
    ifstream entrada("palabras.txt", ios_base::in);
    ifstream entrada2("palabras.txt", ios_base::in);
    ofstream salida("Tp2Ej3.in", ios_base::out);

    int cantidadPalabras;
    entrada >> cantidadPalabras;
    entrada2 >> cantidadPalabras;

    salida << cantidadPalabras*6 << endl;   //agregar pertenece sacar pertenece cardinal

    for(int i = 0; i < cantidadPalabras; i++) {
        string palabra;
        entrada >> palabra;
        salida << "agregar " << palabra << endl;
        salida << "cardinal" << endl;
    }

    for(int i = 0; i < cantidadPalabras; i++) {
        string palabra;
        entrada2 >> palabra;
        salida << "pertenece " << palabra << endl;
        salida << "sacar " << palabra << endl;
        salida << "pertenece " << palabra << endl;
        salida << "cardinal" << endl;
    }

    salida << 0;
    salida.close();
    entrada.close();
    entrada2.close();
}

int main(int argc, char* argv[]) {
    cout << "Generando entrada... ";
    generarEntrada();
    cout << "OK!" << endl;
    ifstream in("Tp2Ej3.in", ifstream::in);

    if(!in.is_open()){
        cout << "no se encontro el archivo Tp2Ej3.in" << endl;
        return 1;
    }

    int cant;
    in >> cant;	
    bool res = true;
    bool perte = true;
    int contador = 0;

    cout << "Ejecutando testeo... ";
    while(cant > 0){
    	PATRICIA *pat = new PATRICIA();
        for(int i = 0; i < cant; i++){
            string inst;
	        in >> inst;
            if(inst == "agregar"){
                //tomo la palabra
                in >> inst;
                pat->agregar(inst);
                contador++;
            }
            else if(inst =="pertenece"){
                //tomo la palabra
                in >> inst;
                bool pertenece = pat->pertenece(inst);
                res = res && (pertenece == perte);
                assert(res);
                perte = !perte;
            }
            else if(inst == "sacar"){
                //tomo la palabra
                in >> inst;
                pat->sacar(inst);
                contador--;
            }
            else if(inst =="cardinal"){
                int card = pat->cardinal();
                res = res && (card == contador);
                assert(res);
            }
        }

        in >> cant;
	    delete pat;
    }

    in.close();
    cout << "EL PATRICIA ANDUVO JOYA!" << endl;
    return 0;
}