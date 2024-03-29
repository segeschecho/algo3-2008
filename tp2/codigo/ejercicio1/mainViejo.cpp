#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <assert.h>
#define print cout<<
#include "Grafo.h"
using namespace std;
bool* ejercicio1(Grafo* grafo,unsigned rels, unsigned& cantGanadores);

/* parseo de la entrada, grabacion de la salida */
int main(int argc, char* argv[])
{    // leo los datos de entrada
    string ruta;
    if(argc >= 2) {
        ruta = argv[1];
    } else {
        ruta="Tp2Ej1.in";
    }
    fstream f (ruta.c_str());
    // FIXME: hay que poner un chequeo no-abortante aca
    // y poner un mensaje de error.
    assert(f.is_open());

    // preparo el archivo de salida
    string salida;
    if(argc > 2) {
        salida = argv[2];
    } else {
        salida = "Tp2Ej1.out";
    }
    ofstream o (salida.c_str());
    unsigned buffer, nodos, relaciones;

    while (true) {
	f >> buffer;
        nodos = buffer;
	f >> buffer;
	relaciones = buffer;
	if(nodos == relaciones && nodos == 0){
	    break;
        }
    unsigned rels = relaciones;
	list<pair<unsigned,unsigned> > l;
        while(relaciones > 0){
	    unsigned x, y;
	    f >> x;
	    f >> y;
	    l.push_back(pair<unsigned,unsigned>(x-1,y-1));
	    relaciones --;
	}
	Grafo* g = new Grafo(nodos,l);
	unsigned cantGanadores = 0;
    	bool* sol =ejercicio1(g,rels,cantGanadores);
    	o<<cantGanadores;
    	if( sol != NULL){

            for(unsigned i = 0; i < g->nodos; i++){
                if(sol[i]){
                o<<" "<<i+1;
                }

            }
    	}
        o<<endl;
    	delete g;
    	delete[] sol;
        }
	return 0;
    }
	
/* dfs que ademas numera los nodos por fin de llamada */
/* en valor[num] dejamos al nodo con el valor num */
/*  	parametros:
*   	grafo a recorrer
* 	nodo donde estoy parado
*	numero a poner en el nodo 
*	marcador de visitados
*	marcador de valores asignados
*/  
void dfs(Grafo* grafo, unsigned nodo, unsigned& num, bool* visitado, unsigned* valor){
    visitado[nodo] = true;
    list<unsigned> :: iterator principio = grafo->verticesOut[nodo].begin();
    list<unsigned> :: iterator final = grafo->verticesOut[nodo].end();
    for(list<unsigned> :: iterator each = principio; each != final; each++){
        if (! visitado[*each])
            dfs(grafo,*each,num,visitado,valor);
    }
	// guardamos a que nodo le toco el valor num
    valor[num] = nodo;
	// incrementamos num para que el padre de este nodo, tenga numero mas alto
    num += 1;
}

/*  se encarga de llamar dfs para numerar, de modo de que se visiten todos los nodos */
void auxdfs(Grafo* grafo, bool* visitado, unsigned* valor){

    for(unsigned i = 0; i < grafo->nodos; i++){
        visitado[i] = false;
        valor[i] = 0;
    }
    unsigned num = 0;
        for(unsigned i = 0;  i < grafo->nodos; i++){
            if(! visitado[i]){
                dfs(grafo,i,num,visitado,valor);
            }
	}
}

/* simil a dfs, pero en vez de numerar, guarda los nodos visitados */
/* la llamamos luego de invertir el grafo, para armar las componentes fuertemente conexas */
void dfs2(Grafo* grafo, unsigned nodo,bool* visitado, list<unsigned>* fuerte){
    visitado[nodo] = true;
    list<unsigned> :: iterator principio = grafo->verticesOut[nodo].begin();
    list<unsigned> :: iterator final = grafo->verticesOut[nodo].end();
    for(list<unsigned> :: iterator each = principio; each != final; each++){
        if (! visitado[*each])
            dfs2(grafo,*each,visitado,fuerte);
    }
    fuerte->push_back(nodo);
}

/* invierte un grafo, de modo que si a -> b en G, devolvemos un G' tal que b->a */
Grafo* invertirGrafo(Grafo* grafo){
    list<pair<unsigned, unsigned> > x;

	// miramos cada nodo y sus relaciones , y ponemos el par inverso
    for(unsigned i = 0; i < grafo->nodos; i++){
        list<unsigned> :: iterator principio = grafo->verticesOut[i].begin();
        list<unsigned> :: iterator final = grafo->verticesOut[i].end();
        for(list<unsigned> :: iterator each = principio; each != final; each++){
            x.push_back(pair<unsigned,unsigned>(*each,i));
        }
    }
	//creamo el grafo a devolver
    Grafo* g = new Grafo(grafo->nodos,x);

    return g;
}

/* arma las componentes fuertemente conexas segun el algoritmo de Kosaraju */
list<list<unsigned>* > * armarFuertes(Grafo* grafo,bool*visitado,unsigned* valor){
    // primero numeramos los nodos
    auxdfs(grafo,visitado,valor);
    // reiniciamos el marcador de visitado
     for(unsigned i = 0; i < grafo->nodos; i++){
        visitado[i] = false;
    }
    // invertimos el grafo
    Grafo* g = invertirGrafo(grafo);

    list<unsigned> * fuerte = new list<unsigned>();
    list<list<unsigned>* > * fuertes = new list<list<unsigned>* >();

    // hacemos dfs desde cada nodo
    // agarramos siempre a los que tienen mayor valor
    // no recorre todo el arbol, sino solo una componente fuertemente conexa por vez
    for(int i = grafo->nodos-1; i >= 0; i--){

        if (! visitado[valor[i]]){

            dfs2(g,valor[i],visitado,fuerte);

            fuertes->push_back(fuerte);

            fuerte = new list<unsigned>();
        }
    }
    delete fuerte;
    delete g;
    return fuertes;
}

/* resuelve el ejercicio 1 */
bool* ejercicio1(Grafo* grafo,unsigned rels, unsigned & cantGanadores){
	// con menos de n-1 aristas el grafo subyacente no es conexo, sabemos que no se puede arreglar
    if(rels < grafo->nodos - 1){
        cantGanadores = 0;
        return NULL;
    }
    bool* visitado = new bool[grafo->nodos];
    unsigned* valor= new unsigned[grafo->nodos];
    //construimos las componentes fuertemente conexas
    list<list<unsigned>* > *fuertes = armarFuertes(grafo,visitado,valor);
    delete[] visitado;
    delete[] valor;

    // guardamos ahora en que componente quedo cada nodo;
    unsigned *dondeQuedo = new unsigned[grafo->nodos];
    unsigned i = 0;
    list<list<unsigned>* > :: iterator principio = fuertes->begin();
    list<list<unsigned>* > :: iterator final = fuertes->end();
    for(list<list<unsigned>* > :: iterator each = principio; each != final; each++){
        for(list<unsigned> ::iterator each1 =(*each)->begin(); each1 != (*each)->end(); each1++){
            dondeQuedo[*each1] = i;
        }
        i++;
    }

    // construimos el grafo reducido donde cada nodo es una componente fuertemente conexa
    i = 0;
    list<pair<unsigned, unsigned> > x;
    for(i = 0; i < grafo->nodos; i ++){

        for(list<unsigned> :: iterator each = grafo->verticesOut[i].begin(); each != grafo->verticesOut[i].end(); each++){
	    // filtramos las flechas que van dentro de la componente conexas
	    // pueden quedar flechas intercomponentes repetidas, pero no afectan al algoritmo,
	    // ni al orden, ya que a lo sumo hay m flechas
		// ademas si tomo la flecha a -> b, cuando la vuelva a tomar, ya visite a b y no entro
            if(dondeQuedo[i] != dondeQuedo[*each])
                x.push_back(pair<unsigned,unsigned>(dondeQuedo[i], dondeQuedo[*each]));
        }
    }
    Grafo g1 = Grafo(fuertes->size(), x);

    delete[] dondeQuedo;
    bool yaHayUno = false;
    unsigned* quien = NULL;
    // El nuevo grafo no tiene ciclos, entonces podemos afirmar que alguien gana si y solo si hay un unico nodo
    // con grado de entrada = 0
    for(unsigned each = 0 ; each < g1.nodos; each++){
		// encontramos uno que podria ser ganador
        if(g1.verticesIn[each].empty() && not yaHayUno){
            quien = new unsigned(each);
            yaHayUno = true;
        }
		// ya teniamos un candidato, entonces no puede haber ganador
        else if(g1.verticesIn[each].empty() && yaHayUno){
        delete quien;
	    quien = NULL;
	    cantGanadores = 0;
	    return NULL;
        }
    }
    //buscamos a la componente ganadora (si hay)
    list<unsigned> * l = new list<unsigned>();
    if(quien != NULL){
		int aux = *quien;;
		list<list<unsigned>* > :: iterator it = fuertes->begin();
		for(list<list<unsigned>* > :: iterator it = fuertes->begin(); aux > 0; aux --){
			it++;
		}
		l->assign((*it)->begin(),(*it)->end());
		delete quien;
    }

    for(list<list<unsigned>* > :: iterator each = principio; each != final;){
		list<list<unsigned>* > :: iterator it = each;
		each++;
		delete *it;
    }
    // como hay que devolverlas en orden hacemos bucketsort en O(n)
    bool* ganadores = new bool[grafo->nodos];
    for(int i = 0; i < grafo-> nodos; i++){
	ganadores[i] = false;
    }
    for(list<unsigned> :: iterator it = l->begin(); it != l->end(); it++){
	ganadores[*it] = true;
    }
    delete fuertes;
    cantGanadores = l->size();
    delete l;
    return ganadores;
}


