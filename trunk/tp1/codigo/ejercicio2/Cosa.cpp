#include "Cosa.h"

Cosa :: Cosa(unsigned v, unsigned p) {
    valor = v;
    peso = p;
}

std::ostream& operator<< (std::ostream& o, const Cosa& c) {
    return o << "Cosa de valor: " << c.valor << " y costo " << c.peso << endl;

}
