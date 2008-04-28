#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <assert.h>
#define no !
#define print cout<<
#include "Grafo.h"
using namespace std;

static unsigned long long int contador;
bool* ejercicio1(Grafo* grafo,unsigned rels, unsigned& cantGanadores);


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
	unsigned valor = 400;
	cout<<"opers=[";
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
	contador= 0;
	contador = contador+2*nodos+2*(l.size());
	Grafo* g = new Grafo(nodos,l);
	unsigned cantGanadores = 0;
		
		valor--;
    	bool* sol =ejercicio1(g,rels,cantGanadores);
		cout<<contador<<" ";
		/*if(valor == 1){
			cout<<"; ";
			valor=400;
		}*/
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
	cout<<"];";
	return 0;
    }

void dfs(Grafo* grafo, unsigned nodo, unsigned& num, bool* visitado, unsigned* valor){
	contador++;
    visitado[nodo] = true;
	contador++;
    list<unsigned> :: iterator principio = grafo->verticesOut[nodo].begin();
	contador++;
    list<unsigned> :: iterator final = grafo->verticesOut[nodo].end();
    contador=contador+3;
	for(list<unsigned> :: iterator each = principio; each != final; each++){
		contador++;
        if (no visitado[*each])
            dfs(grafo,*each,num,visitado,valor);
		contador++;
		contador++;
    }
	contador++;
    valor[num] = nodo;
	contador++;
    num += 1;
}

void auxdfs(Grafo* grafo, bool* visitado, unsigned* valor){
    //visitado = new bool[grafo.nodos];
    //valor = new unsigned[grafo.nodos];
	contador=contador+3;
    for(unsigned i = 0; i < grafo->nodos; i++){
		contador++;
		contador++;
        visitado[i] = false;
        valor[i] = 0;
		contador++;
		contador++;
    }
	contador++;
    unsigned num = 0;
		contador++;
		contador++;
		contador++;
        for(unsigned i = 0;  i < grafo->nodos; i++){
			contador++;
            if(no visitado[i]){
                dfs(grafo,i,num,visitado,valor);
            }
			contador++;
			contador++;
	}
}

void dfs2(Grafo* grafo, unsigned nodo,bool* visitado, list<unsigned>* fuerte){
	contador++;
    visitado[nodo] = true;
    contador++;
	list<unsigned> :: iterator principio = grafo->verticesOut[nodo].begin();
    contador++;
	list<unsigned> :: iterator final = grafo->verticesOut[nodo].end();
    contador++;
	contador++;
	contador++;
	for(list<unsigned> :: iterator each = principio; each != final; each++){
		contador++;
        if (no visitado[*each])
            dfs2(grafo,*each,visitado,fuerte);
		contador++;
		contador++;
    }
	contador++;
    fuerte->push_back(nodo);
}

Grafo* invertirGrafo(Grafo* grafo){
	contador++;
    list<pair<unsigned, unsigned> > x;

	contador++;
	contador++;
	contador++;
    for(unsigned i = 0; i < grafo->nodos; i++){
		contador++;
		contador++;
        list<unsigned> :: iterator principio = grafo->verticesOut[i].begin();
        list<unsigned> :: iterator final = grafo->verticesOut[i].end();
		contador++;
		contador++;
		contador++;
        for(list<unsigned> :: iterator each = principio; each != final; each++){
			contador++;
            x.push_back(pair<unsigned,unsigned>(*each,i));
			contador++;
			contador++;
        }
		contador++;
		contador++;
    }
	contador++;
	contador=contador+grafo->nodos*2+x.size()*2;
    Grafo* g = new Grafo(grafo->nodos,x);

    return g;
}

list<list<unsigned>* > * armarFuertes(Grafo* grafo,bool*visitado,unsigned* valor){

    auxdfs(grafo,visitado,valor);
	contador++;
	contador++;
	contador++;
     for(unsigned i = 0; i < grafo->nodos; i++){
		contador++;
        visitado[i] = false;
		contador++;
		contador++;
    }
	contador++;
    Grafo* g = invertirGrafo(grafo);
	contador++;
    list<unsigned> * fuerte = new list<unsigned>();
	contador++;
    list<list<unsigned>* > * fuertes = new list<list<unsigned>* >();
	contador++;
	contador++;
	contador++;
	contador++;
    for(int i = grafo->nodos-1; i >= 0; i--){
		contador++;
        if (no visitado[valor[i]]){

            dfs2(g,valor[i],visitado,fuerte);
			contador++;
            fuertes->push_back(fuerte);
			contador++;
            fuerte = new list<unsigned>();
        }
    }
	contador++;
    delete fuerte;
	contador++;
    delete g;
	contador++;
    return fuertes;
}

bool* ejercicio1(Grafo* grafo,unsigned rels, unsigned & cantGanadores){
	contador++;
	contador++;
	contador++;
    if(rels < grafo->nodos - 1){
		contador++;
        cantGanadores = 0;
		contador++;
        return NULL;
    }
	contador=contador+2*(grafo->nodos);
    bool* visitado = new bool[grafo->nodos];
    unsigned* valor= new unsigned[grafo->nodos];
    //construimos las componentes fuertemente conexas
	contador++;
    list<list<unsigned>* > *fuertes = armarFuertes(grafo,visitado,valor);
	contador++;
	contador++;
    delete[] visitado;
    delete[] valor;

    // guardamos ahora en que componente quedo cada nodo;
	contador=contador+(grafo->nodos);
    unsigned *dondeQuedo = new unsigned[grafo->nodos];
	contador++;
    unsigned i = 0;
	contador++;
    list<list<unsigned>* > :: iterator principio = fuertes->begin();
	contador++;
    list<list<unsigned>* > :: iterator final = fuertes->end();
	contador++;
	contador++;
	contador++;
    for(list<list<unsigned>* > :: iterator each = principio; each != final; each++){
		contador++;
		contador++;
		contador++;
        for(list<unsigned> ::iterator each1 =(*each)->begin(); each1 != (*each)->end(); each1++){
			contador++;
            dondeQuedo[*each1] = i;
			contador++;
			contador++;
        }
		contador++;
        i++;
		contador++;
		contador++;
    }
	

    // construimos el grafo reducido donde cada nodo es una componente fuertemente conexa
    contador++;
	i = 0;
	contador++;
    list<pair<unsigned, unsigned> > x;
	contador++;
	contador++;
	contador++;
    for(i = 0; i < grafo->nodos; i ++){
		contador++;
		contador++;
		contador++;
		contador++;
        for(list<unsigned> :: iterator each = grafo->verticesOut[i].begin(); each != grafo->verticesOut[i].end(); each++){
	    // filtramos las flechas que van dentro de la componente conexas
	    // pueden quedar flechas intercomponentes repetidas, pero no afectan al algoritmo,
	    // ni al orden, ya que a lo sumo hay m flechas
			contador++;
            if(dondeQuedo[i] != dondeQuedo[*each]){
				contador++;
				contador++;
				contador++;
                x.push_back(pair<unsigned,unsigned>(dondeQuedo[i], dondeQuedo[*each]));
			}
			contador++;
			contador++;
        }
		contador++;
		contador++;
    }
	contador=contador + 2*(x.size())+2*(fuertes->size());
    Grafo g1 = Grafo(fuertes->size(), x);
	contador++;
    delete[] dondeQuedo;
	contador++;
    bool yaHayUno = false;
	contador++;
    unsigned* quien = NULL;
    // El nuevo grafo no tiene ciclos, entonces podemos afirmar que alguien gana si y solo si hay un unico nodo
    // con grado de entrada = 0
	contador++;
	contador++;
	contador++;
    for(unsigned each = 0 ; each < g1.nodos; each++){
		contador++;
		contador++;
		contador++;
        if(g1.verticesIn[each].empty() && not yaHayUno){
			contador++;
			contador++;
            quien = new unsigned(each);
            yaHayUno = true;
        }
        else if(g1.verticesIn[each].empty() && yaHayUno){
		contador++;
		contador++;
        delete quien;
		contador++;
	    quien = NULL;
		contador++;
	    cantGanadores = 0;
		contador++;
	    return NULL;
        }
    }
    //cosa que no debe pasar :P
    if(no yaHayUno){
        cout<<"cacacacacaca"<<endl;
    }
    //buscamos a la componente ganadora (si hay)
	contador++;
	
    list<unsigned> * l = new list<unsigned>();
	contador++;
    if(quien != NULL){
	contador++;
	int aux = *quien;;
	contador++;
	list<list<unsigned>* > :: iterator it = fuertes->begin();
	contador++;
	contador++;
	for(list<list<unsigned>* > :: iterator it = fuertes->begin(); aux > 0; aux --){
		contador++;
		it++;
		contador++;
		contador++;
	}
	contador=contador+((*it)->size());
	l->assign((*it)->begin(),(*it)->end());
	contador++;
	delete quien;
    }
	contador++;
	contador++;
	contador++;
    for(list<list<unsigned>* > :: iterator each = principio; each != final;){
	contador++;
	list<list<unsigned>* > :: iterator it = each;
	contador++;
	each++;
	contador++;
	delete *it;
	contador++;
    }
    // como hay que devolverlas en orden hacemos bucketsort en O(n)
	contador=contador+grafo->nodos;
    bool* ganadores = new bool[grafo->nodos];
	contador++;
	contador++;
	contador++;
    for(int i = 0; i < grafo-> nodos; i++){
	contador++;
	ganadores[i] = false;
    contador++;
	contador++;
	}
	contador++;
	contador++;
	contador++;
	
    for(list<unsigned> :: iterator it = l->begin(); it != l->end(); it++){
	contador++;
	ganadores[*it] = true;
	contador++;
    }
	contador++;
    delete fuertes;
	contador++;
    cantGanadores = l->size();
	contador++;
    delete l;
	contador++;
    return ganadores;
}

