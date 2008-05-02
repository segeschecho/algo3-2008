#include <iostream>
#include "PATRICIA_t.h"

using namespace std;

int main()
{
    PATRICIA patri;
    ifstream in("palabras500a1000letras.txt", ifstream::in);
    string *buff;
    int cant;

    if(!in.is_open()){
        cout << "no se puede encontrar el archivo" << endl;
        return 0;
    }

    //tomo la cantidad de palabras
    in >> cant;
    buff = new string[cant];

    for (int i = 0; i < cant; i++){
        getline(in, buff[i]);
    }

    //empiezo a contar las operaciones, en funcion del largo de las palabras
    for (int i = 0; i < cant; i++){
        patri.agregar(buff[i]);
        //descomentar para contar operaciones de agregar
        //cout << patri.operaciones << endl;
    }

    //descomentar para contar operaciones de pertenece
    /*
    for (int i = 0; i < cant; i++){
        patri.pertenece(buff[i]);
        cout << patri.operaciones << endl;
    }*/

    //descomentar para contar operaciones de sacar

    for (int i = 0; i < cant; i++){
        patri.sacar(buff[i]);
        cout << patri.operaciones << endl;
    }

    delete [] buff;
    return 0;
}
