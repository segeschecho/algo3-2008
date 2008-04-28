#ifndef _PATRICIA_H_
#define _PATRICIA_H_

#include "nodoPATRICIA.h"
#include <iostream>
using namespace std;

class PATRICIA : private nodo {
    friend ostream& operator<<(ostream&, const PATRICIA&);
public:
    // Constructor
    // Parametros:      void
	// Proposito:       Inicializa la estructura de datos.
    PATRICIA();

    // Parametros:      cadena a agregar al PATRICIA
	// Proposito:       le da significado a la cadena s en el PATRICIA
    void agregar (const string& s);

    // Parametros:      cadena a eliminar del PATRICIA
	// Proposito:       le quita significado a la cadena s en el PATRICIA
    void sacar (const string& s);

    // Parametros:      cadena a verificar si pertenece al PATRICIA
	// Proposito:       verifica si s pertenece al PATRICIA
    bool pertenece (const string& s) const;

    // Parametros:      void
	// Proposito:       devuelve la cantidad de elementos definidos en el PATRICIA
    unsigned int cardinal(void) const;

    // Destructor
    // Parametros:      void
	// Proposito:       Destruye la estructura de datos.
    ~PATRICIA();

private:

    nodo* raiz;
    unsigned int cantElem;
    void quitarPrefijoEnComun(string& s1, const string& s2) const;
    nodo::puntero* bajar(nodo*&, nodo::puntero*&, const string&, string&) const;
    void destruirPatricia (nodo*);
    void verPatricia (nodo*, const string&, ostream&) const;
};

#endif