#include "Dibujo.h"
#include "SolucionExacta.h"
#include "FiltroGrafos.h"


int main() {
    ifstream in("Tp3_chico.in");
    Dibujo d(in);

    list<nodo> p1, p2;
    p1.assign(d.grafo()->nodosEnP1().begin(), d.grafo()->nodosEnP1().end());
    p2.assign(d.grafo()->nodosEnP2().begin(), d.grafo()->nodosEnP2().end());
    cout << d << endl;
    FiltroGrafos tp3(d);
    SolucionExacta s = SolucionExacta(*tp3.dibujoLimpio);
    Dibujo dib = s.resolver();
    cout << dib << endl;
}
