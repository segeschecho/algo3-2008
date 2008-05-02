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
    opers = 1;
    if(s.empty()) {
        opers = 1;
        _existe = true;
    }
    else {
        opers += 4;
        list<eje>::iterator it = listaEjes.begin();
        while(it != listaEjes.end() && (it->cadena) < s) {
            it++;
            opers += 4;
        }

        //Si llego al final de la lista, entonces no tengo problemas al agregarlo, pero
        //si quedo por la mitad, verifico que el elemento no este ya definido, asi no hay duplicados.
        opers += 5;
        if((it == listaEjes.end()) || (it != listaEjes.end() && (it->cadena) != s)) {
            opers += 1;
            if(nuevonodo == NULL) {
                opers += 1;
                nuevonodo = new nodo;
            }

            opers += 1;
            nuevonodo->_existe = true;

            opers += 2;
            eje nuevoptr;
            nuevoptr.cadena = s;
            nuevoptr.puntero = nuevonodo;

            opers += s.length();
            listaEjes.insert(it, nuevoptr);
        }
    }
}

void nodo :: sacar (const string& s){
    opers = 3;
    list<eje>::iterator it = listaEjes.begin();
    while(it != listaEjes.end() && (it->cadena) != s) {
        it++;
        opers += 4;
    }

    opers += 1;
    if(it != listaEjes.end()) {
        listaEjes.erase(it);
        //opers += (*it).cadena.length();
    }
}

bool nodo :: pertenece (const string& s){
    opers = 4;
    list<eje>::iterator it = listaEjes.begin();
    while(it != listaEjes.end() && (it->cadena) != s) {
        it++;
        opers += 4;
    }

    opers += 1;
    return (it != listaEjes.end());
}

bool nodo :: getExiste(void){
    return _existe;
}

void nodo :: setExiste(bool b) {
    _existe = b;
}

unsigned int nodo :: cantHijos(void) {
    opers += 1;
    return (unsigned int) listaEjes.size();
}

bool nodo :: esHoja(void){
    opers += 1;
    return (unsigned int) listaEjes.size() == 0;
}

/*
 *  METODOS PRIVADOS
 */

nodo::eje* nodo :: ejeQueEmpiezaCon(string c) {
    opers += 1;
    if(c.length() > 1){
        opers += 1;
        return NULL;
    }

    opers += 4;
    list<nodo::eje>::iterator it = listaEjes.begin();
    while(it != listaEjes.end() && c != it->cadena.substr(0,1)) {
        it++;
        opers += 4;
    }

    //si llego al final de la lista, quiere decir que no encontro el elemento
    opers += 1;
    if(it == listaEjes.end()){
        opers += 4;
        return NULL;
    }

    opers += 2;
    return (eje*)&(*it);
}

nodo::eje* nodo :: iesimoEje(int i) {
    opers += 2;
    list<nodo::eje>::iterator it = listaEjes.begin();
    unsigned int contador = 0;

    opers += 3;
    while(it != listaEjes.end() && i != contador) {
        contador++;
        it++;
        opers += 5;
    }

    //si llego al final de la lista, quiere decir que no encontro el elemento
    opers += 1;
    if(it == listaEjes.end()){
        opers += 1;
        return NULL;
    }

    opers += 2;
    return (eje*)&(*it);
}

nodo::eje* nodo :: primerEje(void) {
    opers += 2;
    return (eje*)&(*(listaEjes.begin()));
}
