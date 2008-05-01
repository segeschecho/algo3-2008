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
    nodo::eje* ejeActual;
    string palabraArmada;
    nodo* actual = raiz;

    //primero bajo por las ramas hasta no econtrar mas prefijo
    bajar(actual, ejeActual, s, palabraArmada);

    //si s == palabraArmada y el actual sobre el que estoy ya existe, entonces
    //la clave ya se encuentra definida. En esos casos no agrego nada.
    if ( !((s == palabraArmada) && (actual->getExiste())) ) {
        string cadena = s;
        quitarPrefijoEnComun(cadena, palabraArmada);
        quitarPrefijoEnComun(palabraArmada, s);
        //ahora cadena y palabraArmada no tienen elementos
        //en comun (les quite el prefijo)

        //si palabraArmada no queda vacia luego de quitarle el prefijo,
        //quiere decir que tengo que partir el eje actual
        if(!palabraArmada.empty()) {
            bool existia = actual->getExiste();
            size_t longitud = (ejeActual->cadena).length() - palabraArmada.length();
            (ejeActual->cadena).erase(longitud, (ejeActual->cadena).length());
            //ahora ejeActual->cadena tiene la parte final de la palabraArmada

            nodo* nuevopadre = new nodo;
            nuevopadre->agregar(palabraArmada, actual);
            if(existia)
                actual->setExiste(true);
            else
                actual->setExiste(false);

            ejeActual->puntero = nuevopadre;
            actual = nuevopadre;
        }

        //finalmente, agrego la parte final del string s
        actual->agregar(cadena);
        cantElem++;
    }
}

void PATRICIA :: sacar(const string& s){
    nodo::eje* ejeActual;
    nodo::eje* ejeAnterior;
    string palabraArmada;
    nodo* actual = raiz;

    //primero bajo por las ramas hasta no econtrar mas prefijo
    ejeAnterior = bajar(actual, ejeActual, s, palabraArmada);

    //me aseguro de haber encontrado la clave a borrar
    if(!s.empty() && s == palabraArmada && actual->getExiste()) {
        nodo* anterior = raiz;
        if (ejeAnterior != NULL)
            anterior = ejeAnterior->puntero;

        //si el actual es hoja, lo borro y luego verifico si tengo que mergear
        if(actual->esHoja()) {
            anterior->sacar(ejeActual->cadena);
            delete actual;

            //hago merge del anterior con el actual en caso de haber borrado una hoja 
            if ((anterior != NULL) && (anterior->cantHijos() == 1) && (!anterior->getExiste())) {
                nodo::eje* aux = anterior->primerEje();

                ejeAnterior->cadena = ejeAnterior->cadena + aux->cadena;

                ejeAnterior->puntero = aux->puntero;
                delete anterior;
            }
        }
        else {
            //si el actual a sacar tiene 1 solo hijo
            if (actual->cantHijos() == 1) {
                //hago merge del actual con el siguiente
                nodo::eje* ejeSiguiente = actual->primerEje();
                ejeActual->cadena = ejeActual->cadena + ejeSiguiente->cadena;

                ejeActual->puntero = ejeSiguiente->puntero;
                delete actual;
            }
            else
                actual->setExiste(false);
        }
        cantElem--;
    }
}

bool PATRICIA :: pertenece(const string& s) const{
    nodo* actual = raiz;
    nodo::eje* ejeActual;
    string palabraArmada;

    bajar(actual, ejeActual, s, palabraArmada);
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

bool PATRICIA :: quitarPrefijoEnComun(string& s1, const string& s2) const{
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
    return cantLetras == s2.length();
}

nodo::eje* PATRICIA :: bajar(nodo*& actual, nodo::eje*& ejeActual, const string& s, string& palabraArmada) const{
    actual = raiz;
    nodo::eje* ejeAnterior = NULL;
    ejeActual = NULL;
    palabraArmada.clear();
    string recortada = s;
    //recortada es el string s sacandole los prefijos encontrados cada vez que bajamos por una rama

    //verifico solo la primer letra pues con solo eso me alcanza
    nodo::eje* aux = actual->ejeQueEmpiezaCon(recortada.substr(0,1));
    bool puedoBajar = (aux != NULL);
    while(aux != NULL && puedoBajar) {
        ejeAnterior = ejeActual;
        ejeActual = aux;
        actual = aux->puntero;
        palabraArmada += aux->cadena;
        puedoBajar = quitarPrefijoEnComun(recortada, aux->cadena);

        aux = actual->ejeQueEmpiezaCon(recortada.substr(0,1));
    }
    return ejeAnterior;
}

void PATRICIA :: verPatricia (nodo* n, const string& s, ostream& os) const{
    os << s << ":  ";
    os << *n;
    os << "\n-------------------------------------------" << endl;

    for(unsigned int i = 0; i < 26; i++) {
        nodo::eje* e = n->iesimoEje(i);
        if(e != NULL)
            verPatricia(e->puntero, e->cadena, os);
    }
}

void PATRICIA :: destruirPatricia (nodo* n) {
    for(unsigned int i = 0; i < 26; i++) {
        nodo::eje* e = n->iesimoEje(i);
        if(e != NULL)
            destruirPatricia(e->puntero);
    }

    delete n;
}

ostream& operator<<(ostream& os, const PATRICIA& p){
    p.verPatricia(p.raiz, "", os);
    os << "Cardinal = " << p.cantElem << endl;
    return os;
}

void PATRICIA :: parser(void){
    int cant = 0;
    ifstream in("Tp2Ej3.in", ifstream::in);
    ofstream out("Tp2Ej3.out", ifstream::out);

    if(!in.is_open()){
        cout << "no se encontro el archivo" << endl;
        return;
    }

    if(!out.is_open()){
        cout << "no se puede crear el archivo" << endl;
        return;
    }

    in >> cant;

    while(cant > 0){
        for(int i = 0; i < cant; i++){
            char inst [256];
            in >> inst;

            if(strcmp(inst, "agregar") == 0){
                //tomo la palabra
                in >> inst;
                this->agregar(inst);
            }
            else if(strcmp(inst, "pertenece") == 0){
                //tomo la palabra
                in >> inst;
                out << this->pertenece(inst);
                if(i + 1 < cant)
                    out << " ";
            }
            else if(strcmp(inst, "sacar") == 0){
                //tomo la palabra
                in >> inst;
                this->sacar(inst);
            }
            else if(strcmp(inst, "cardinal") == 0){
                out << this->cardinal();
                if(i + 1 < cant)
                    out << " ";
            }
        }
        in >> cant;
    }

    in.close();
    out.close();
}
