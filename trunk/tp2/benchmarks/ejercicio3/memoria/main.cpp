#include <iostream>
#include "PATRICIA_t.h"
#include "memorymgr.h"
#include "heap.h"

using namespace std;

int main()
{
    ofstream archivoSalida("memoriaEnFuncionPalabrasArreglos.m", ios_base::out);
    PATRICIA patri;
    ifstream in("palabras.words", ifstream::in);

    if(!in.is_open()){
        cout << "no se puede encontrar el archivo" << endl;
        return 0;
    }

    //tomo la cantidad de palabras
    int cant;
    in >> cant;
    size_t espacioArreglo = HeapFactory::GetDefaultHeap()->getPeak();
    string *buff = new string[cant];
    espacioArreglo = HeapFactory::GetDefaultHeap()->getPeak() - espacioArreglo;

//    int bm1 = HeapFactory::GetDefaultHeap()->GetMemoryBookmark();

    for (int i = 0; i < cant; i++){
        getline(in, buff[i]);
    }

    archivoSalida << "x = [";
    //empiezo a contar las operaciones, en funcion del largo de las palabras
    for (int i = 0; i < cant; i++){
        patri.agregar(buff[i]);
        archivoSalida << HeapFactory::GetDefaultHeap()->getPeak() - espacioArreglo << endl;
        //descomentar para contar operaciones de agregar
        //cout << patri.operaciones << endl;
    }
    archivoSalida << "];";

    archivoSalida.close();

    //descomentar para contar operaciones de pertenece
    /*
    for (int i = 0; i < cant; i++){
        patri.pertenece(buff[i]);
        cout << patri.operaciones << endl;
    }*/

    //descomentar para contar operaciones de sacar
    /*
    for (int i = 0; i < cant; i++){
        patri.sacar(buff[i]);
        cout << patri.operaciones << endl;
    }*/

    delete [] buff;
 
//    HeapFactory::GetMemoryReport(cout);

    system("PAUSE");

    return 0;
}