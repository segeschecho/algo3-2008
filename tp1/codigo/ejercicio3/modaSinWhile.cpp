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
        if (!tachados[indiceDeAtras] && !tachados[indiceDeAdelante] && (a[indiceDeAtras] != a[indiceDeAdelante])) {
            tachados[indiceDeAtras] = true;
            tachados[indiceDeAdelante] = true;
        }

        // movemos los indices para que lleguen al proximo elemento sin tachar y que sean distintos
        if (indiceDeAtras < n && tachados[indiceDeAtras]) {
            indiceDeAtras++;
        }
        if (indiceDeAdelante < n && 
            (tachados[indiceDeAdelante] 
            || (!tachados[indiceDeAtras] && a[indiceDeAtras] == a[indiceDeAdelante]) )){
            
            indiceDeAdelante++;
        }
    }

    // buscamos el primer elemento sin tachar y sabemos que es la moda
    // o quedo solo 1 y es la moda, o quedaron varios iguales y que son la moda

    int k = 0;
    while ( k < n && tachados[k]) {
        k++;
    }
    
    delete [] tachados;
    return a[k];
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
    assert(f.is_open());

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
        cout << res;
        delete [] a;
        o << res << endl;
        f >> buffer;
    }
    return 0;
}

