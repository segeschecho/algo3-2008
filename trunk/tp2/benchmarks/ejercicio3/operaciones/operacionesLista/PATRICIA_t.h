#ifndef _PATRICIA_H_
#define _PATRICIA_H_

#include "nodo_listas_PATRICIA.h"
#include <iostream>
#include <fstream>
using namespace std;

class PATRICIA {
    friend ostream& operator<<(ostream&, const PATRICIA&);
public:
    //variable para contar operaciones.
    unsigned long long int operaciones;
    // Constructor
    // Parametros:      void
	// Proposito:       Inicializa la estructura de datos.
    PATRICIA();

    // Destructor
    // Parametros:      void
	// Proposito:       Destruye la estructura de datos.
    ~PATRICIA();

    // Parametros:      cadena a agregar al PATRICIA
	// Proposito:       le da significado a la cadena s en el PATRICIA
    void agregar (const string& s);

    // Parametros:      cadena a eliminar del PATRICIA
	// Proposito:       le quita significado a la cadena s en el PATRICIA
    void sacar (const string& s);

    // Parametros:      cadena a verificar si pertenece al PATRICIA
	// Proposito:       verifica si s pertenece al PATRICIA
    bool pertenece (const string& s);

    // Parametros:      void
	// Proposito:       devuelve la cantidad de elementos definidos en el PATRICIA
    unsigned int cardinal(void) const;

    // Parametros:      void
	// Proposito:       levanta los datos del archivo Tp2Ej3.in y devuelve el resultado en Tp2Ej3.out
    void parser(void);

private:

    nodo* raiz;
    unsigned int cantElem;
    bool quitarPrefijoEnComun(string& s1, const string& s2);
    nodo::eje* bajar(nodo*&, nodo::eje*&, const string&, string&);
    void destruirPatricia (nodo*);
    void verPatricia (nodo*, const string&, ostream&) const;
};

#endif
