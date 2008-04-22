#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <assert.h>
#define no !
#include "Grafo.h"
using namespace std;
bool* ejercicio1(Grafo* grafo,unsigned& cantGanadores);

int main(int argc, char* argv[])
{    // leo los datos de entrada
    string ruta;
    if(argc >= 2) {
        ruta = argv[1];
    } else {
        ruta="Tp2Ej1.in";
    }
    fstream f (ruta.c_str());
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
	list<pair<unsigned,unsigned> > l;
        while(relaciones > 0){
	    unsigned x, y;
	    f >> x; 
	    f >> y;
	    l.push_back(pair<unsigned,unsigned>(x-1,y-1));
	    relaciones --;
	}
	Grafo* g = new Grafo(nodos,l);
	cout<<*g<<endl;
	unsigned cantGanadores = 0;
    	bool* sol =ejercicio1(g,cantGanadores);
	o<<cantGanadores;
	if(cantGanadores > 0){
	    o<<" ";
        }
    	for(unsigned i = 0; i < cantGanadores; i++){
		if(sol[i]){
		   o<<i+1;
		}
		if(i != cantGanadores -1){
			o<<" ";
		}
	}
    	delete g;
    	delete[] sol;
        }
	return 0;
    }

void bfs(Grafo* grafo, unsigned nodo, unsigned& num, bool* visitado, unsigned* valor){
    visitado[nodo] = true;
    list<unsigned> :: iterator principio = grafo->verticesOut[nodo].begin();
    list<unsigned> :: iterator final = grafo->verticesOut[nodo].end();
    for(list<unsigned> :: iterator each = principio; each != final; each++){
        if (no visitado[*each])
            bfs(grafo,*each,num,visitado,valor);
    }
    valor[num] = nodo;
    num += 1;
}

void auxbfs(Grafo* grafo, bool* visitado, unsigned* valor){
    //visitado = new bool[grafo.nodos];
    //valor = new unsigned[grafo.nodos];
    for(unsigned i = 0; i < grafo->nodos; i++){
        visitado[i] = false;
        valor[i] = 0;
    }
    unsigned num = 0;
        for(unsigned i = 0;  i < grafo->nodos; i++){
            if(no visitado[i]){
                bfs(grafo,i,num,visitado,valor);
            }
	}
}

void bfs2(Grafo* grafo, unsigned nodo,bool* visitado, list<unsigned>* fuerte){
    visitado[nodo] = true;
    list<unsigned> :: iterator principio = grafo->verticesOut[nodo].begin();
    list<unsigned> :: iterator final = grafo->verticesOut[nodo].end();
    for(list<unsigned> :: iterator each = principio; each != final; each++){
        if (no visitado[*each])
            bfs2(grafo,*each,visitado,fuerte);
    }
    fuerte->push_back(nodo);
}

Grafo* invertirGrafo(Grafo* grafo){
    list<pair<unsigned, unsigned> > x;


    for(unsigned i = 0; i < grafo->nodos; i++){
        list<unsigned> :: iterator principio = grafo->verticesOut[i].begin();
        list<unsigned> :: iterator final = grafo->verticesOut[i].end();
        for(list<unsigned> :: iterator each = principio; each != final; each++){
            x.push_back(pair<unsigned,unsigned>(*each,i));
        }
    }
    Grafo* g = new Grafo(grafo->nodos,x);

    return g;
}

list<list<unsigned>* > * armarFuertes(Grafo* grafo,bool*visitado,unsigned* valor){

    auxbfs(grafo,visitado,valor);

     for(unsigned i = 0; i < grafo->nodos; i++){
        visitado[i] = false;
    }

    Grafo* g = invertirGrafo(grafo);

    list<unsigned> * fuerte = new list<unsigned>();
    list<list<unsigned>* > * fuertes = new list<list<unsigned>* >();

    for(int i = grafo->nodos-1; i >= 0; i--){

        if (no visitado[valor[i]]){

            bfs2(g,valor[i],visitado,fuerte);

            fuertes->push_back(fuerte);

            fuerte = new list<unsigned>();
        }
    }
    delete fuerte;
    delete g;
    return fuertes;
}

bool* ejercicio1(Grafo* grafo,unsigned & cantGanadores){
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
        if(g1.verticesIn[each].empty() && not yaHayUno){
            quien = new unsigned(each);
            yaHayUno = true;
        }
        else if(g1.verticesIn[each].empty() && yaHayUno){
            delete quien;
	    quien = NULL;
	    break;
        }
    }
    //cosa que no debe pasar :P
    if(no yaHayUno){
        cout<<"cacacacacaca"<<endl;
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


