#include "nodoPATRICIA.h"
#include <iostream>

void nodo :: agregar (const string& s, nodo* nuevonodo) {
    if(s.empty()) {
        _existe = true;
    }
    else {
        list<puntero>::iterator it = listaHijos.begin();
        while(it != listaHijos.end() && (it->cadena) < s) {
            it++;
        }

        if((it == listaHijos.end()) || (it != listaHijos.end() && (it->cadena) != s)) {
            if(nuevonodo == NULL) {
                nuevonodo = new nodo;
            }

            nuevonodo->_existe = true;

            puntero nuevoptr;
            nuevoptr.cadena = s;
            nuevoptr.siguiente = nuevonodo;

            listaHijos.insert(it, nuevoptr);
        }
    }
}

void nodo :: sacar (const string& s){
    list<puntero>::iterator it = listaHijos.begin();
    while(it != listaHijos.end() && (it->cadena) != s) {
        it++;
    }

    if(it != listaHijos.end()) {
        listaHijos.erase(it);
    }
}

bool nodo :: pertenece (const string& s){
    list<puntero>::iterator it = listaHijos.begin();
    while(it != listaHijos.end() && (it->cadena) != s) {
        it++;
    }

    return (it != listaHijos.end());
}

void nodo :: setExiste(bool b) {
    _existe = b;
}

unsigned int nodo :: cardinal(void) {
    return (unsigned int) listaHijos.size();
}

bool nodo :: esHoja(void){
    return (unsigned int) listaHijos.size() == 0;
}

bool nodo :: getExiste(void){
    return _existe;
}

nodo::puntero* nodo :: elemento(string c) {
    if(c.length() > 1)
        return NULL;

    list<nodo::puntero>::iterator it = listaHijos.begin();
    while(it != listaHijos.end() && c != it->cadena.substr(0,1)) {
        it++;
    }

    if(it == listaHijos.end())
        return NULL;

    return (puntero*)&(*it);
}

nodo::puntero* nodo :: elemento(int i) {
    list<nodo::puntero>::iterator it = listaHijos.begin();
    unsigned int contador = 0;

    while(it != listaHijos.end() && i != contador) {
        contador++;
        it++;
    }

    if(it == listaHijos.end())
        return NULL;

    return (puntero*)&(*it);
}

nodo::puntero* nodo :: dameUno(void) {
    return (puntero*)&(*(listaHijos.begin()));
}

ostream& operator<<(ostream& os, const nodo& n){
    list<nodo::puntero>::const_iterator it = n.listaHijos.begin();
    n._existe ? os << "Existe" << endl : os << "No existe" << endl;
    while(it != n.listaHijos.end()) {
        os << it->cadena << "    ";
        it++;
    }

    return os;
}
