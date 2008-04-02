#include "Cosa.h"

Cosa :: Cosa(unsigned v, unsigned c) {
    valor = v;
    costo = c;
}

std::ostream& operator<< (std::ostream& o, const Cosa& c) {
    return o << "Cosa de valor: " << c.valor << " y costo " << c.costo << endl;

}
