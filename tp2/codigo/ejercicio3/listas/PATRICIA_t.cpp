#include "PATRICIA_t.h"

/*
 *  METODOS PUBLICOS
 */

PATRICIA :: PATRICIA(){
    cantElem = 0;
    raiz = new nodo;
    raiz->setExiste(true);
}

void PATRICIA :: agregar(const string& s){
    nodo::puntero* ptrActual;
    string palabraArmada;
    nodo* actual = raiz;
    
    bajar(actual, ptrActual, s, palabraArmada);

    if ((s != palabraArmada) || (!actual->getExiste())) {
        string cadena = s;
        quitarPrefijoEnComun(cadena, palabraArmada);
        quitarPrefijoEnComun(palabraArmada, s);
        //ahora cadena y palabraArmada no tienen elementos 
        //en comun (les quite el prefijo)

        if(!palabraArmada.empty()) {
            string resto = ptrActual->cadena;
            resto.erase(resto.length() - palabraArmada.length(), resto.length());
            //si palabraArmada sin prefijo es "so", y la cadena que estaba en el
            //puntero actual era "queso", entonces resto es "que".
            //resto lo voy a usar para partir el puntero y agregar en el medio
            //el nuevo elemento
            ptrActual->cadena = resto;
            
            nodo* nuevopadre = new nodo;
            nuevopadre->agregar(palabraArmada, ptrActual->siguiente);
            ptrActual->siguiente = nuevopadre;
            actual = nuevopadre;
        }

        actual->agregar(cadena);
        cantElem++;
    }
}

void PATRICIA :: sacar(const string& s){
    nodo::puntero* ptrActual;
    nodo::puntero* ptrAnterior;
    string palabraArmada;
    nodo* actual = raiz;
    
    ptrAnterior = bajar(actual, ptrActual, s, palabraArmada);

    if(!s.empty() && s == palabraArmada) {
        nodo* anterior = raiz;
        if (ptrAnterior != NULL)
            anterior = ptrAnterior->siguiente;

        if(actual->esHoja()) {
            anterior->sacar(ptrActual->cadena);
            delete actual;
        }
        else {
            if (actual->cardinal() == 1) {
                //hago merge del actual con el siguiente
                puntero* ptrSiguiente = actual->dameUno();
                ptrActual->cadena = ptrActual->cadena + ptrSiguiente->cadena;

                ptrActual->siguiente = ptrSiguiente->siguiente;
                delete actual;
            }
            else
                actual->setExiste(false);
        }

        cantElem--;

        //hago merge del anterior con el actual
        if ((anterior != NULL) && (anterior->cardinal() == 1) && (!anterior->getExiste())) {
            puntero* ptrAux = anterior->dameUno();

            ptrAnterior->cadena = ptrAnterior->cadena + ptrAux->cadena;

            ptrAnterior->siguiente = ptrAux->siguiente;
            delete anterior;
        }
    }
}

bool PATRICIA :: pertenece(const string& s) const{
    nodo* actual = raiz;
    puntero* ptrActual;
    string palabraArmada;

    bajar(actual, ptrActual, s, palabraArmada);
    return ((s == palabraArmada) && (actual->getExiste()));
}

unsigned int PATRICIA :: cardinal(void) const{
    return cantElem;
}

PATRICIA :: ~PATRICIA(){
    destruirPatricia(raiz);
}

/*
 *  METODOS PRIVADOS
 */

void PATRICIA :: quitarPrefijoEnComun(string& s1, const string& s2) const{
    string::const_iterator it1, it2;
    unsigned int cantLetras = 0;

    it1 = s1.begin();
    it2 = s2.begin();

    while(it1 != s1.end() && it2 != s2.end() && *it1 == *it2) {
        it1++;
        it2++;
        cantLetras++;
    }

    s1.erase(0, cantLetras);
}

nodo::puntero* PATRICIA :: bajar(nodo*& actual, nodo::puntero*& ptrActual, const string& s, string& palabraArmada) const{
    actual = raiz;
    puntero* ptrAnterior = NULL;
    ptrActual = NULL;
    palabraArmada.clear();
    bool encontro = true;
    string recortada = s;

    //verifico solo la primer letra pues con solo eso me alcanza
    puntero* aux = actual->elemento(recortada.substr(0,1));
    while(aux != NULL) {
        ptrAnterior = ptrActual;
        ptrActual = aux;
        actual = aux->siguiente;
        palabraArmada += aux->cadena;
        quitarPrefijoEnComun(recortada, aux->cadena);

        aux = actual->elemento(recortada.substr(0,1));
    }
    return ptrAnterior;
}

void PATRICIA :: verPatricia (nodo* n, const string& s, ostream& os) const{
    os << s << ":  ";
    os << *n;
    os << "\n-------------------------------------------" << endl;

    for(unsigned int i = 0; i < n->cardinal(); i++) {
        puntero* e = n->elemento(i);
        verPatricia(e->siguiente, e->cadena, os);
    }
}

void PATRICIA :: destruirPatricia (nodo* n) {
    for(unsigned int i = 0; i < n->cardinal(); i++) {
        puntero* e = n->elemento(i);
        destruirPatricia(e->siguiente);
    }
    delete n;
}

ostream& operator<<(ostream& os, const PATRICIA& p){
    os << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    p.verPatricia(p.raiz, "", os);
    os << "Cardinal = " << p.cantElem << endl;
    system("PAUSE");
    return os;
}