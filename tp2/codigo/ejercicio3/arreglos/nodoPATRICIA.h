#ifndef _NODO_PATRICIA_H_
#define _NODO_PATRICIA_H_

#include <string>
using namespace std;

class nodo{
    friend ostream& operator<<(ostream&, const nodo&);
protected:
    struct puntero{
        nodo* siguiente;
        string cadena;
    };

private:
    bool _existe;
    unsigned int cantElem;
    puntero* arregloHijos[26];

public:

    // Constructor
    // Parametros:      void
	// Proposito:       Inicializa la estructura de datos.
    nodo();

    // Destructor
    // Parametros:      void
	// Proposito:       Destruye la estructura de datos.
    ~nodo();

    // Parametros:      cadena del puntero que linkea this con nuevonodo, el nodo a ser linkeado
	// Proposito:       agregar un nuevo nodo relacionandolo con la cadena
    void agregar (const string& s, nodo*  nuevonodo = NULL);

    // Parametros:      cadena del puntero a eliminar
	// Proposito:       eliminar el puntero relacionado a la cadena s
    void sacar (const string& s);

    // Parametros:      cadena a verificar si tiene un puntero asignado
	// Proposito:       ver si una cadena tiene un puntero asignado en el nodo this
    bool pertenece (const string& s);

    // Parametros:      void
	// Proposito:       ver si el nodo existe
    bool getExiste(void);

    // Parametros:      void
	// Proposito:       asignar la existencia o no existencia del nodo
    void setExiste(bool);

    // Parametros:      cadena con un solo elemento que simboliza el
    //                  primer caracter de la cadena que se quiere ver
	// Proposito:       ver un elemento especifico
    nodo::puntero* elemento(string c);

    // Parametros:      posicion de la cadena que se quiere ver (0-n)
	// Proposito:       ver un elemento especifico
    nodo::puntero* elemento(unsigned int i);

    // Parametros:      posicion de la cadena que se quiere ver (0-n)
	// Proposito:       ver un elemento
    nodo::puntero* dameUno(void);

    // Parametros:      void
	// Proposito:       ver la cantidad de elementos que hay linkeados en el nodo
    unsigned int cardinal(void);

    // Parametros:      void
	// Proposito:       ver si el nodo no tiene ningun elemento linkeado
    bool esHoja(void);
};

#endif