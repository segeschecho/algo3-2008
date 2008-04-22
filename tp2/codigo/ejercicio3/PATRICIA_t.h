#ifndef _PATRICIA_H_
#define _PATRICIA_H_

#include <list>
#include <string>
using namespace std;

class PATRICIA {
public:
    PATRICIA();
    void agregar (const string&);
    void sacar (const string&);
    void pertenece (const string&);
    unsigned int cardinal();
    ~PATRICIA();
private:
    struct nodo;

    struct puntero{
        nodo* siguiente;
        string cadena;
    };

    struct nodo{
        bool existe;
        list<puntero> hijos;
    };

    nodo raiz;

    void quitarPrefijo(string& s1, string& prefijo, const string& s2);
    void bajar(void);
};

#endif