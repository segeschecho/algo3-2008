#ifndef _NODO_ARREGLOS_PATRICIA_H_
#define _NODO_ARREGLOS_PATRICIA_H_

#include <string>
using namespace std;

class nodo{
    friend class PATRICIA;
    friend ostream& operator<<(ostream&, const nodo&);
public:

    // Constructor
    // Parametros:      void
	// Proposito:       Inicializa la estructura de datos.
    nodo();

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

    // Parametros:      void
	// Proposito:       ver la cantidad de elementos que hay linkeados en el nodo
    unsigned int cantHijos(void);

    // Parametros:      void
	// Proposito:       ver si el nodo no tiene ningun elemento linkeado
    bool esHoja(void);

    // Destructor
    // Parametros:      void
	// Proposito:       Destruye la estructura de datos.
    ~nodo();

private:
    struct eje{
        nodo* puntero;
        string cadena;
    };

    bool _existe;
    unsigned int cantElem;
    eje* arregloHijos[26];

    // Parametros:      primer caracter de la cadena que se quiere ver
	// Proposito:       ver un elemento especifico
    nodo::eje* ejeQueEmpiezaCon(char c);

    // Parametros:      posicion de la cadena que se quiere ver (0-n)
	// Proposito:       ver un elemento especifico
    nodo::eje* iesimoEje(unsigned int i);

    // Parametros:      posicion de la cadena que se quiere ver (0-n)
	// Proposito:       ver un elemento
    nodo::eje* primerEje(void);
};

#endif