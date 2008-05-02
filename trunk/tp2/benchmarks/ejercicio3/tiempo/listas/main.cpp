#include <iostream>
#include <string>

#include "PATRICIA_t.h"
#include "hr_time.h"

using namespace std;

int main(int argc, char* argv[]) {
    PATRICIA patri;
    int cant = 0;
    int i = 0;
    double tiempo = 0;
    CStopWatch timer;

    ifstream in("palabras.words", ifstream::in);
    if(!in.is_open()){
        cout << "no se encontro el archivo" << endl;
        return 0;
    }

    in >> cant;
    string *buff = new string[cant];
    i = 0;
    getline(in, buff[i]);
    while(i < cant){
        //levanto las palabras y las guardo en el buffer!
        getline(in, buff[i]);
        i++;
    }

    //hago las pruebas de tiempo, cargo palabras de a 100 y tomo el tiempo
    i = (int)(cant/100);

    cout << "cantidad de pruebas: " << i << endl;

    for(int j = 0; j < i; j++){
        timer.startTimer();
        for(int k = 0; k < 100; k++){
            patri.agregar(buff[k*j]);
        }
        timer.stopTimer();
        tiempo += timer.getElapsedTime();
        cout << tiempo << endl;
    }


    delete [] buff;
    return 0;
}
