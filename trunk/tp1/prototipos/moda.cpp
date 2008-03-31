#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>
using namespace std;

/*
  i=0
    j=1
    b=[0]*len(a)
    while j < len(a):
            if a[i] != a[j]:
                b[i]=1
                b[j]=1
                while i < len(a) and b[i] == 1:
                    i=i+1
                while j < len(a) and (b[j] == 1 or j <= i):
                    j=j+1

            else:
                j=j+1
    k=0
    while b[k] != 0:
        k=k+1
    print a
    print b
    return a[k]
*/
int moda(int* a, int n) {
  int indiceDeAtras = 0;
  int indiceDeAdelante = 0;
  //en tachados guardaremos que elementos descartamos porq encontramos uno distinto
  bool* tachados = new bool[n];
  for(int i = 0; i < n; i++) {
      tachados[i] = false;
  }

  while(indiceDeAdelante < n) {
    //si son distintos pasan a estar tachados
    if (a[indiceDeAtras] != a[indiceDeAdelante]) {
        tachados[indiceDeAtras] = true;
        tachados[indiceDeAdelante] = true;
        // movemos los indices para que lleguen al proximo elemento sin tachar, y ademas que valga
        // que el de adelante quede adelante
        while (indiceDeAtras < n && tachados[indiceDeAtras] ) {
            indiceDeAtras++;
        }
        while (indiceDeAdelante < n && (tachados[indiceDeAdelante] || indiceDeAdelante <= indiceDeAtras)){
            indiceDeAdelante++;
        }
    }
    else{
        // si eran iguales, avanzamos buscando otro diferente
        indiceDeAdelante++;
    }
  }
  int k = 0;
  // buscamos el primer elemento sin tachar y sabemos que es la moda
  // o quedo solo 1 y es la moda, o quedaron varios iguales y que son la moda
  while( k < n && tachados[k]){
      k++;
  }
  delete [] tachados;
  assert(k < n);
  return a[k];
}

int main(int argc, char* argv[]){
    string ruta;
    if(argc >= 2){
        ruta = argv[1];
    }
    else{
        ruta="Tp1Ej3.in";
    }
    fstream f (ruta.c_str());
    string salida;
    if(argc > 2)
        salida = argv[2];
    else
        salida = "Tp1Ej3.out";

    ofstream o (salida.c_str());
    assert(f.is_open());
    int buffer;
    int elementos;
    f >> buffer;
    while(buffer != 0){
        elementos = buffer;
        int* a = new int[elementos];
        int i = 0;
        while(elementos > 0){
            f >> a[i];
            i++;
            elementos--;
        }
        int res = moda(a,buffer);
        cout << res;
        delete a;
        o << res << endl;
        f >> buffer;
    }
    o.close();
    f.close();

    return 0;
}

