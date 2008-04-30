#include "nodo_listas_PATRICIA.h"
#include <iostream>

ostream& operator<<(ostream& os, const nodo& n){
    list<nodo::eje>::const_iterator it = n.listaEjes.begin();
    n._existe ? os << "Existe" << endl : os << "No existe" << endl;
    while(it != n.listaEjes.end()) {
        os << it->cadena << "    ";
        it++;
    }

    return os;
}

/*
 *  METODOS PUBLICOS
 */

void nodo :: agregar (const string& s, nodo* nuevonodo) {
    if(s.empty()) {
        _existe = true;
    }
    else {
        list<eje>::iterator it = listaEjes.begin();
        while(it != listaEjes.end() && (it->cadena) < s) {
            it++;
        }

        //Si llego al final de la lista, entonces no tengo problemas al agregarlo, pero
        //si quedo por la mitad, verifico que el elemento no este ya definido, asi no hay duplicados.
        if((it == listaEjes.end()) || (it != listaEjes.end() && (it->cadena) != s)) {
            if(nuevonodo == NULL) {
                nuevonodo = new nodo;
            }

            nuevonodo->_existe = true;

            eje nuevoptr;
            nuevoptr.cadena = s;
            nuevoptr.puntero = nuevonodo;

            listaEjes.insert(it, nuevoptr);
        }
    }
}

void nodo :: sacar (const string& s){
    list<eje>::iterator it = listaEjes.begin();
    while(it != listaEjes.end() && (it->cadena) != s) {
        it++;
    }

    if(it != listaEjes.end()) {
        listaEjes.erase(it);
    }
}

bool nodo :: pertenece (const string& s){
    list<eje>::iterator it = listaEjes.begin();
    while(it != listaEjes.end() && (it->cadena) != s) {
        it++;
    }

    return (it != listaEjes.end());
}

bool nodo :: getExiste(void){
    return _existe;
}

void nodo :: setExiste(bool b) {
    _existe = b;
}

unsigned int nodo :: cantHijos(void) {
    return (unsigned int) listaEjes.size();
}

bool nodo :: esHoja(void){
    return (unsigned int) listaEjes.size() == 0;
}

/*
 *  METODOS PRIVADOS
 */

nodo::eje* nodo :: ejeQueEmpiezaCon(string c) {
    if(c.length() > 1)
        return NULL;

    list<nodo::eje>::iterator it = listaEjes.begin();
    while(it != listaEjes.end() && c != it->cadena.substr(0,1)) {
        it++;
    }

    //si llego al final de la lista, quiere decir que no encontro el elemento
    if(it == listaEjes.end())
        return NULL;

    return (eje*)&(*it);
}

nodo::eje* nodo :: iesimoEje(int i) {
    list<nodo::eje>::iterator it = listaEjes.begin();
    unsigned int contador = 0;

    while(it != listaEjes.end() && i != contador) {
        contador++;
        it++;
    }

    //si llego al final de la lista, quiere decir que no encontro el elemento
    if(it == listaEjes.end())
        return NULL;

    return (eje*)&(*it);
}

nodo::eje* nodo :: primerEje(void) {
    return (eje*)&(*(listaEjes.begin()));
}
