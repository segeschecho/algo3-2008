#include "PATRICIA_t.h"


/*
 *  METODOS PUBLICOS
 */

PATRICIA :: PATRICIA(){
    raiz.existe = true;
}

void PATRICIA :: agregar(const string& s){
    nodo* actual = raiz;
    nodo* padre = NULL;
    
    padre = bajar(actual);
}

void PATRICIA :: sacar(const string& s){
}

void PATRICIA :: pertenece(const string& s){
}

unsigned int PATRICIA :: cardinal(){
    return 0;
}

PATRICIA :: ~PATRICIA(){
}




/*
 *  METODOS PRIVADOS
 */

void PATRICIA :: quitarPrefijo(string& s1, string& prefijo, const string& s2){
    string::const_iterator it1, it2;
    unsigned int cantLetras = 0;
    string prefijo;

    it1 = s1.begin();
    it2 = s2.begin();

    while(*it1 == *it2) {
        prefijo += *it1;
        it1++;
        it2++;
        cantLetras++;
    }

    s1.erase(0, cantLetras);
    copia = prefijo;
}
