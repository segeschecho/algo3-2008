#include <iostream>
#include <string>

#include "PATRICIA_t.h"

using namespace std;

int main(int argc, char* argv[]) {
    PATRICIA patri;
    patri.agregar("tatetito");
    cout << patri << endl << endl;
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
    /*
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
*/
    system("PAUSE");
    return 0;
}