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


    // buscamos el primer elemento sin tachar y sabemos que es la moda
    // o quedo solo 1 y es la moda, o quedaron varios iguales y que son la moda


    /*int k = 0;
    while ( k < n && tachados[k]) {
        k++;
    }*/
    delete [] tachados;
    assert(indiceDeAtras < n);
    return a[indiceDeAtras];
}

int main(int argc, char* argv[]) {

    // leo los datos de entrada
    string ruta;
    if(argc >= 2) {
        ruta = argv[1];
    } else {
        ruta="Tp1Ej1.in";
    }
    fstream f (ruta.c_str());
    assert(f.is_open());

    // preparo el archivo de salida
    string salida;
    if(argc > 2) {
        salida = argv[2];
    } else {
        salida = "Tp1Ej1.out";
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

