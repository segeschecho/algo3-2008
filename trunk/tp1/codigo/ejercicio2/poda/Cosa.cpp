#include "Cosa.h"

Cosa :: Cosa(unsigned v, unsigned c) {
    operaciones++;
    operaciones++;
    valor = v;
    peso = c;
}

std::ostream& operator<< (std::ostream& o, const Cosa& c) {
    return o << "Cosa de valor: " << c.valor << " y costo " << c.peso << endl;

}
