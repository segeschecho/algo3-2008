#include <iostream>
#include <string>
#include "PATRICIA_t.h"

using namespace std;

int main(int argc, char* argv[]) {
    PATRICIA patri;
    patri.agregar("iiii");
    patri.agregar("i");
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

    cout << patri;
    patri.sacar("iii");
    cout << patri;
    patri.sacar("i");
    cout << patri;
    patri.sacar("iiii");
    cout << patri;
    patri.sacar("emilio");
    cout << patri;
    patri.sacar("emiliano");
    cout << patri;
    patri.sacar("emi");
    cout << patri;
    patri.sacar("cacona");
    cout << patri;
    patri.sacar("cacique");
    cout << patri;
    patri.sacar("caconete");
    cout << patri;
    patri.sacar("caballete");
    cout << patri;
    patri.sacar("caca");
    cout << patri;
    patri.sacar("cacapupu");
    cout << patri;
    patri.sacar("ze");
    cout << patri;
    patri.sacar("anana");
    cout << patri;
    patri.sacar("anan");
    cout << patri;
    patri.sacar("ana");
    cout << patri;
    patri.sacar("zero");
    cout << patri;

    return 0;
}