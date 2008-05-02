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
    operaciones = 1;
    nodo::eje* ejeActual;
    string palabraArmada;
    nodo* actual = raiz;

    //primero bajo por las ramas hasta no econtrar mas prefijo
    bajar(actual, ejeActual, s, palabraArmada);

    //si s == palabraArmada y el actual sobre el que estoy ya existe, entonces
    //la clave ya se encuentra definida. En esos casos no agrego nada.
    operaciones += 3;
    if ( !((s == palabraArmada) && (actual->getExiste())) ) {
        operaciones += 1;
        string cadena = s;
        quitarPrefijoEnComun(cadena, palabraArmada);
        quitarPrefijoEnComun(palabraArmada, s);
        //ahora cadena y palabraArmada no tienen elementos
        //en comun (les quite el prefijo)

        //si palabraArmada no queda vacia luego de quitarle el prefijo,
        //quiere decir que tengo que partir el eje actual
        operaciones += 1;
        if(!palabraArmada.empty()) {
            operaciones += 3;
            bool existia = actual->getExiste();
            size_t longitud = (ejeActual->cadena).length() - palabraArmada.length();
            (ejeActual->cadena).erase(longitud, (ejeActual->cadena).length());
            //ahora ejeActual->cadena tiene la parte final de la palabraArmada

            operaciones += 1;
            nodo* nuevopadre = new nodo;
            nuevopadre->agregar(palabraArmada, actual);
            operaciones += nuevopadre->opers;
            operaciones += 2;
            if(existia)
                actual->setExiste(true);
            else
                actual->setExiste(false);

            operaciones += 2;
            ejeActual->puntero = nuevopadre;
            actual = nuevopadre;
        }

        //finalmente, agrego la parte final del string s
        actual->agregar(cadena);
        operaciones += actual->opers;
        operaciones += 1;
        cantElem++;
    }
}

void PATRICIA :: sacar(const string& s){
    operaciones = 1;
    nodo::eje* ejeActual;
    nodo::eje* ejeAnterior;
    string palabraArmada;
    nodo* actual = raiz;

    //primero bajo por las ramas hasta no econtrar mas prefijo
    operaciones += 1;   // uno mas lo del bajar
    ejeAnterior = bajar(actual, ejeActual, s, palabraArmada);

    //me aseguro de haber encontrado la clave a borrar
    operaciones += 5;
    if(!s.empty() && s == palabraArmada && actual->getExiste()) {
        operaciones += 2;
        nodo* anterior = raiz;
        if (ejeAnterior != NULL){
            operaciones += 1;
            anterior = ejeAnterior->puntero;
        }

        //si el actual es hoja, lo borro y luego verifico si tengo que mergear
        if(actual->esHoja()) {
            operaciones += actual->opers;
            anterior->sacar(ejeActual->cadena);
            operaciones += anterior->opers;
            operaciones += 1;
            delete actual;

            //hago merge del anterior con el actual en caso de haber borrado una hoja
            operaciones += 6;
            if ((anterior != NULL) && (anterior->cantHijos() == 1) && (!anterior->getExiste())) {
                operaciones += 1;
                nodo::eje* aux = anterior->primerEje();
                operaciones += anterior->opers;

                operaciones += 4;
                ejeAnterior->cadena = ejeAnterior->cadena + aux->cadena;

                ejeAnterior->puntero = aux->puntero;
                delete anterior;
            }
        }
        else {
            operaciones += actual->opers;
            //si el actual a sacar tiene 1 solo hijo
            operaciones += 1;
            if (actual->cantHijos() == 1) {
                operaciones += actual->opers;
                //hago merge del actual con el siguiente
                operaciones += 1;
                nodo::eje* ejeSiguiente = actual->primerEje();
                operaciones += actual->opers;
                operaciones += 4;
                ejeActual->cadena = ejeActual->cadena + ejeSiguiente->cadena;

                ejeActual->puntero = ejeSiguiente->puntero;
                delete actual;
            }
            else{
                operaciones += actual->opers;
                operaciones += 1;
                actual->setExiste(false);
            }
        }
        operaciones += 1;
        cantElem--;
    }
}

bool PATRICIA :: pertenece(const string& s){
    operaciones = 1;
    nodo* actual = raiz;
    nodo::eje* ejeActual;
    string palabraArmada;

    bajar(actual, ejeActual, s, palabraArmada);
    operaciones += 3;
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

bool PATRICIA :: quitarPrefijoEnComun(string& s1, const string& s2){
    operaciones += 1;
    string::const_iterator it1, it2;
    unsigned int cantLetras = 0;

    operaciones += 2;
    it1 = s1.begin();
    it2 = s2.begin();

    operaciones += 5;
    while(it1 != s1.end() && it2 != s2.end() && *it1 == *it2) {
        operaciones += 8;
        it1++;
        it2++;
        cantLetras++;
    }

    s1.erase(0, cantLetras);
    operaciones += 2;
    return cantLetras == s2.length();
}

nodo::eje* PATRICIA :: bajar(nodo*& actual, nodo::eje*& ejeActual, const string& s, string& palabraArmada){
    operaciones += 4;
    actual = raiz;
    nodo::eje* ejeAnterior = NULL;
    ejeActual = NULL;
    palabraArmada.clear();
    string recortada = s;
    //recortada es el string s sacandole los prefijos encontrados cada vez que bajamos por una rama

    //verifico solo la primer letra pues con solo eso me alcanza
    operaciones += 2;
    nodo::eje* aux = actual->ejeQueEmpiezaCon(recortada.substr(0,1));
    operaciones += actual->opers;
    bool puedoBajar = (aux != NULL);

    operaciones += 2;
    while(aux != NULL && puedoBajar) {
        operaciones += 5;
        ejeAnterior = ejeActual;
        ejeActual = aux;
        actual = aux->puntero;
        palabraArmada += aux->cadena;
        puedoBajar = quitarPrefijoEnComun(recortada, aux->cadena);

        operaciones += 1;
        aux = actual->ejeQueEmpiezaCon(recortada.substr(0,1));
        operaciones += actual->opers;
        operaciones += 2;     //guardas del if
    }
    operaciones += 1;
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
