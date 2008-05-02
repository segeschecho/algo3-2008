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
    opers = 1;
    if(s.empty()) {
        opers += 1;
        _existe = true;
    }
    else {
        opers += 3;
        int i = toupper((int)*s.begin()) - 65;
        if(arregloHijos[i] == NULL) {
            opers += 1;
            if(nuevonodo == NULL) {
                opers += 2;
                nuevonodo = new nodo;
                nuevonodo->_existe = true;
            }

            opers += 4;
            arregloHijos[i] = new eje;
            arregloHijos[i]->cadena = s;
            arregloHijos[i]->puntero = nuevonodo;
            cantElem++;
        }
    }
}

void nodo :: sacar (const string& s){
    opers = 3;
    int i = toupper((int)*s.begin()) - 65;
    if  (arregloHijos[i] != NULL) {
        opers += 3;
        delete arregloHijos[i];
        arregloHijos[i] = NULL;
        cantElem--;
    }
}

bool nodo :: pertenece (const string& s){
    opers = 3;
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
    opers = 3;
    for(int i = 0; i < 26; i++) {
        opers += 1;
        if (arregloHijos[i] != NULL){
            opers += 1;
            return false;
        }
        opers += 2;
    }
    opers += 1;
    return true;
}

bool nodo :: getExiste(void){
    return _existe;
}

nodo::eje* nodo :: ejeQueEmpiezaCon(string c) {
    opers = 1;
    if(c.length() == 1) {
        opers += 2;
        return arregloHijos[toupper((int)*c.begin()) - 65];
    }

    return NULL;
}

nodo::eje* nodo :: iesimoEje(unsigned int i) {
    opers += 2;
    if(i >= 26)
        return NULL;
    return arregloHijos[i];
}

nodo::eje* nodo :: primerEje(void) {
    opers += 4;
    unsigned int i = 0;
    while(i < 26 && arregloHijos[i] == NULL) {
        opers += 4;
        i++;
    }
    opers += 1;
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
