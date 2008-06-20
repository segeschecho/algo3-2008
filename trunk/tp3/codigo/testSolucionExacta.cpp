#include "Dibujo.h"
#include "SolucionExacta.h"
#include "Tp3.h"


int main() {
    ifstream in("Tp3_chico.in");
    Dibujo d(in);

    list<nodo> p1, p2;
    p1.assign(d.grafo()->nodosEnP1().begin(), d.grafo()->nodosEnP1().end());
    p2.assign(d.grafo()->nodosEnP2().begin(), d.grafo()->nodosEnP2().end());
    cout << d << endl;
    Tp3 tp3(d);
    SolucionExacta s = SolucionExacta(*tp3.dibujoLimpio);
    cout << s.resolver().contarCruces() << " cruces!" << endl;
}
