#include "nodo_arreglos_PATRICIA.h"
#include <iostream>

nodo :: nodo() {
    _existe = false;
    for(int i = 0; i < 26; i++)
        arregloHijos[i] = NULL;
    cantElem = 0;
}

nodo :: ~nodo() {
    for(int i = 0; i < 26; i++) {
        delete arregloHijos[i];
    }
}

void nodo :: agregar (const string& s, nodo* nuevonodo) {
    if(s.empty()) {
        _existe = true;
    }
    else {
        int i = toupper((int)*s.begin()) - 65;
        if(arregloHijos[i] == NULL) {
            if(nuevonodo == NULL) {
                nuevonodo = new nodo;
            }

            nuevonodo->_existe = true;

            arregloHijos[i] = new eje;
            arregloHijos[i]->cadena = s;
            arregloHijos[i]->puntero = nuevonodo;
            cantElem++;
        }
    }
}

void nodo :: sacar (const string& s){
    int i = toupper((int)*s.begin()) - 65;
    if  (arregloHijos[i] != NULL) {
        delete arregloHijos[i];
        arregloHijos[i] = NULL;
        cantElem--;
    }
}

bool nodo :: pertenece (const string& s){
    int i = toupper((int)*s.begin()) - 65;

    return (arregloHijos[i]->cadena == s);
}

void nodo :: setExiste(bool b) {
    _existe = b;
}

unsigned int nodo :: cantHijos(void) {
    return cantElem;
}

bool nodo :: esHoja(void){
    for(int i = 0; i < 26; i++) {
        if (arregloHijos[i] != NULL)
            return false;
    }
    return true;
}

bool nodo :: getExiste(void){
    return _existe;
}

nodo::eje* nodo :: ejeQueEmpiezaCon(string c) {
    if(c.length() == 1) {
        return arregloHijos[toupper((int)*c.begin()) - 65];
    }

    return NULL;
}

nodo::eje* nodo :: iesimoEje(unsigned int i) {
    if(i >= 26)
        return NULL;
    return arregloHijos[i];
}

nodo::eje* nodo :: primerEje(void) {
    unsigned int i = 0;
    while(i < 26 && arregloHijos[i] == NULL) {
        i++;
    }

    return arregloHijos[i];
}

ostream& operator<<(ostream& os, const nodo& n){
	 if(n._existe)
	     os << "Existe" << endl;
    else
        os << "No existe" << endl;

    for(unsigned int i = 0; i < 26; i++) {
        if (n.arregloHijos[i] != NULL)
            os << n.arregloHijos[i]->cadena << "    ";
    }

    return os;
}
