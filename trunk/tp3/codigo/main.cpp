#include <iostream>
#include "Dibujo.h"
#include "GrafoBipartito.h"
#include <math.h>

using namespace std;


int main(int argc, char* argv[]) {
    list<eje> ejes;
    eje e1, e2, e3, e4, e5, e6, e7, e8;
    vector<nodo> nodosV1, nodosV2, nodosP1, nodosP2;

    e1.primero = 8;
    e1.segundo = 2;

    e2.primero = 8;
    e2.segundo = 3;

    e3.primero = 1;
    e3.segundo = 2;

    e4.primero = 1;
    e4.segundo = 3;

    e5.primero = 5;
    e5.segundo = 2;

    e6.primero = 8;
    e6.segundo = 6;

    e7.primero = 5;
    e7.segundo = 3;

    e8.primero = 0;
    e8.segundo = 6;

    ejes.push_back(e1);
    ejes.push_back(e2);
    ejes.push_back(e3);
    ejes.push_back(e4);
    ejes.push_back(e5);
    ejes.push_back(e6);
    ejes.push_back(e7);
    ejes.push_back(e8);

    nodosV1.push_back(0);
    nodosV1.push_back(8);
    nodosV1.push_back(1);
    nodosV1.push_back(5);
    nodosV2.push_back(2);
    nodosV2.push_back(3);
    nodosV2.push_back(6);

    GrafoBipartito g(nodosV1, nodosV2, ejes);

    nodosP1.push_back(8);
    nodosP1.push_back(1);
    nodosP1.push_back(5);
    nodosP2.push_back(2);
    nodosP2.push_back(3);
    nodosP2.push_back(6);

    Dibujo d(&g, nodosP1, nodosP2);

    cout << contadorDeCruces(d.nodosL1, d.nodosL2, g.diccEjes) << endl;
    cout << crucesEntre(8,1, d.nodosL2, g.diccEjes) << endl;
    unsigned int v = 0;
    cout << crucesPorAgregarEnLosBordes(true, d.nodosL1, d.nodosL2, g.diccEjes, &v) << endl;

    system("PAUSE");
    return 0;
}