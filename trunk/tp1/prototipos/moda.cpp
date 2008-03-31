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
  int i = 0;
  int j = 0;
  int* b = new int[n];
  for(int i = 0; i < n; i++) {
      b[i] = 0;
  }
  while(j < n) {
    if (a[i] != a[j]) {
        b[i] = 1;
        b[j] = 1;
        while (i < n && b[i] == 1) {
            i++;
        }
        while (j < n && (b[j] == 1 || j <= i)){
            j++;
        }
    }
    else{
        j++;
    }
  }
  int k = 0;
  while( k < n && b[k] != 0){
      k++;
  }
  delete [] b;
  assert(k < n);
  return a[k];
}

int main(int argc, char* argv[]){
    string ruta;
    if(argc < 2){
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

