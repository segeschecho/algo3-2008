#include <iostream>
#include <string>
#include <fstream>

#include <assert.h>

using namespace std;

int moda(int* a, int n) {
    int indiceDeAtras = 0;
    int indiceDeAdelante = 0;

    //en tachados guardaremos que elementos descartamos porq encontramos uno distinto
    bool* tachados = new bool[n];
    for (int i = 0; i < n; i++) {
        tachados[i] = false;
    }

    while (indiceDeAdelante < n) {
        // si son distintos pasan a estar tachados
        if (a[indiceDeAtras] != a[indiceDeAdelante]) {
            tachados[indiceDeAtras] = true;
            tachados[indiceDeAdelante] = true;

            // movemos los indices para que lleguen al proximo elemento sin tachar, y ademas que valga
            // que el de adelante quede adelante
            while (indiceDeAtras < n && tachados[indiceDeAtras]) {
                indiceDeAtras++;
            }
            while (indiceDeAdelante < n && (tachados[indiceDeAdelante] || indiceDeAdelante <= indiceDeAtras)) {
                indiceDeAdelante++;
            }
        }

        // si eran iguales, avanzamos buscando otro diferente
        else {
            indiceDeAdelante++;
        }
    }


	//indice de atras esta en un elemento que es la moda

    delete [] tachados;
    assert(indiceDeAtras < n);
    return a[indiceDeAtras];
}

void help() {
    cout << "Uso ./moda <infile> <outfile>" << endl;
    cout << "  o ./moda (sin parametros)" << endl;
    cout << "En el caso de la llamada sin parametros se toman los archivos" << endl;
    cout << "Tp1Ej3.in y Tp1Ej3.out como valores por defecto." << endl;
}


int main(int argc, char* argv[]) {

    // leo los datos de entrada
    string ruta;
    if(argc >= 2) {
        ruta = argv[1];
    } else {
        ruta="Tp1Ej3.in";
    }
    fstream f (ruta.c_str());
    if(!f.is_open()) {
        cout << endl << "ERROR: No se pudo abrir el archivo de entrada!" << endl << endl;
        help();
        return 1;
    }

    // preparo el archivo de salida
    string salida;
    if(argc > 2) {
        salida = argv[2];
    } else {
        salida = "Tp1Ej3.out";
    }
    ofstream o (salida.c_str());

    int buffer, elementos;
    f >> buffer;
    while (buffer != 0) {
        elementos = buffer;
        int* a = new int[elementos];
        int i = 0;
        while (elementos > 0) {
            f >> a[i];
            i++;
            elementos--;
        }
        int res = moda(a,buffer);
        delete [] a;
        o << res << endl;
        f >> buffer;
    }
    return 0;
}

