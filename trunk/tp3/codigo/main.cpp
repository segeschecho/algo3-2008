#include <iostream>
#include "Dibujo.h"
#include "GrafoBipartito.h"
#include <math.h>
#include "BusquedaLocal.h"
#include "Tp3.h"
#include "HeuristicaConstructiva.h"
using namespace std;
#define print(a) cout<<a<<endl;

int main(int argc, char* argv[]) {
    Dibujo d ("Tp3.in");
    GrafoBipartito* graf = d.grafo();
    cout<<"aaaaaaaasssasdadsada"<<endl;
//    for(vector<nodo> :: const_iterator it = graf->V1.begin(); it != graf->V1.end(); it++){
//        print(*it);
//        cout<<*((graf->ejes[*it]).begin())<<endl;;
//    }
    cout<<"emiliooooooooooooooooo"<<endl;

    Tp3 tp3(d,7,2,4,5);
    cout<<"por q programo tan mal???"<<endl;
    print("p1")
    cout<<*tp3.dibujoLimpio<<endl;
    HeuristicaConstructiva hc(*tp3.dibujoLimpio);

    Dibujo dib =hc.construirSolucion();
    cout<<"por favorrrr"<<endl;
    BusquedaLocal bl(*tp3.dibujoLimpio);

    Dibujo carlos = bl.hallarMinimoLocal(dib);

    Dibujo fabian =tp3.reconstruirDibujo(carlos);
    print("p1")
    for(vector<nodo> :: const_iterator it = fabian.nodosEnP1().begin(); it != fabian.nodosEnP1().end(); it++){
        print(*it)
    }
    print("p2");
    for(vector<nodo> :: const_iterator it = fabian.nodosEnP2().begin(); it != fabian.nodosEnP2().end(); it++){
        print(*it)
    }
    cout<<"ahora miremos el grafo"<<endl;
    print("v1")
    for(vector<nodo> :: const_iterator it = fabian.grafo()->nodosEnP1().begin(); it != fabian.grafo()->nodosEnP1().end(); it++){
        print(*it)
    }
    print("v2");
    for(vector<nodo> :: const_iterator it = fabian.grafo()->nodosEnP2().begin(); it != fabian.grafo()->nodosEnP2().end(); it++){
        print(*it)
    }
    vector<nodo> indice(fabian.nodosEnP1().size()+fabian.nodosEnP2().size());
    unsigned i = 0;
    for(vector<nodo> :: const_iterator it =fabian.nodosEnP1().begin(); it != fabian.nodosEnP1().end(); it++){
        indice[*it] = i;
        i++;
    }
    i = 0;
    for(vector<nodo> :: const_iterator it =fabian.nodosEnP2().begin(); it != fabian.nodosEnP2().end(); it++){
        indice[*it] = i;
        i++;
    }
    cout<<"cruces "<<contadorDeCruces(fabian.nodosEnP1(),fabian.nodosEnP2(),fabian.grafo()->ejes(),indice,indice)<<endl;
    cout<<"prueba "<<fabian.contarCruces();
    //delete graf;
/*    list<eje> ejes;
    eje e1, e2, e3, e4, e5, e6, e7, e8;
    vector<nodo> nodosV1, nodosV2, nodosP1, nodosP2;

    e1.primero = 0;
    e1.segundo = 88;
    e2.primero = 0;
    e2.segundo = 3;
    e3.primero = 1;
    e3.segundo = 2;

    e5.primero = 4;
    e5.segundo = 2;


    ejes.push_back(e1);
    ejes.push_back(e3);
    ejes.push_back(e2);
    ejes.push_back(e5);

    nodosV1.push_back(0);
    nodosV1.push_back(1);
    nodosV1.push_back(4);
    nodosV2.push_back(2);
    nodosV2.push_back(3);
    nodosV2.push_back(88);

    GrafoBipartito g(nodosV1, nodosV2, ejes);

    nodosP1.push_back(0);
    nodosP1.push_back(1);

    nodosP2.push_back(2);
    nodosP2.push_back(3);
    Dibujo d(&g, nodosP1, nodosP2);

    BusquedaLocal bl(d);

    nodosP1.push_back(4);
    nodosP2.push_back(88);
    Dibujo d2(&g, nodosP1,nodosP2);


    Dibujo d3 = bl.hallarMinimoLocal(d2);

    print(contadorDeCruces(d3.nodosEnP1(),d3.nodosEnP2(),g.ejes()));
    unsigned i = 0;
    while(i < d3.nodosEnP1().size()){
        print(d3.nodosEnP1()[i]);
        i++;
    }
    i = 0;
    while(i < d3.nodosEnP2().size()){
        print(d3.nodosEnP2()[i]);
        i++;
    }
*/
    system("PAUSE");
    return 0;
}
