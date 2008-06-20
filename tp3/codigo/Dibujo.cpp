#include "Dibujo.h"

Dibujo :: Dibujo() {
	desdeArchivo = false;
    contado = false;
}

Dibujo :: Dibujo(GrafoBipartito* grafo, const vector<nodo>& l1, const vector<nodo>& l2) {
    desdeArchivo = false;
    g = grafo;
    assert(l1.size() + l2.size() <= g->n);

    nodosL1 = l1;
    nodosL2 = l2;
    contado = false;
}


Dibujo :: Dibujo(GrafoBipartito* grafo, const list<nodo>& l1, const list<nodo>& l2) {
    desdeArchivo = false;
    g = grafo;
    assert(l1.size() + l2.size() <= g->n);

    nodosL1.assign(l1.begin(), l1.end());
    nodosL2.assign(l2.begin(), l2.end());
    contado = false;
}

Dibujo :: Dibujo(GrafoBipartito* grafo, const list<nodo>& l1, const list<nodo>& l2, unsigned c) {
    desdeArchivo = false;
    g = grafo;
    assert(l1.size() + l2.size() <= g->n);

    nodosL1.assign(l1.begin(), l1.end());
    nodosL2.assign(l2.begin(), l2.end());
    cruces = c;
    contado = true;
}

Dibujo :: Dibujo(ifstream & entrada) {

    desdeArchivo = true;

    assert(entrada.is_open());

    vector<nodo> nodosV1, nodosV2;
    list<eje> ejes;
    unsigned int cantLineas;

    entrada >> cantLineas;
    while (cantLineas > 0) {
        nodo v;
        entrada >> v;
        v--;
        nodosL1.push_back(v);
        nodosV1.push_back(v);
        cantLineas--;
    }

    entrada >> cantLineas;
    while (cantLineas > 0) {
        nodo v;
        entrada >> v;
        v--;
        nodosL2.push_back(v);
        nodosV2.push_back(v);
        cantLineas--;
    }

    entrada >> cantLineas;
    while (cantLineas > 0) {
        nodo v;
        eje e;

        entrada >> v;
        v--;
        e.primero = v;
        entrada >> v;
        v--;
        e.segundo = v;

        ejes.push_back(e);
        cantLineas--;
    }

    entrada >> cantLineas;
    while (cantLineas > 0) {
        nodo v;
        entrada >> v;
        v--;
        nodosV1.push_back(v);
        cantLineas--;
    }

    entrada >> cantLineas;
    while (cantLineas > 0) {
        nodo v;
        entrada >> v;
        v--;
        nodosV2.push_back(v);
        cantLineas--;
    }

    entrada >> cantLineas;
    while (cantLineas > 0) {
        nodo v;
        eje e;

        entrada >> v;
        v--;
        e.primero = v;
        entrada >> v;
        v--;
        e.segundo = v;

        ejes.push_back(e);
        cantLineas--;
    }
    g = new GrafoBipartito(nodosV1, nodosV2, ejes);
    contado = false;
}

Dibujo :: Dibujo(const Dibujo& d) {
    *this = d;
}

Dibujo :: ~Dibujo() {
    // FIXME: arreglar este destructor, por ahora lo comento
    // porque sino provoca segfaults.
    if (desdeArchivo) {
        delete g;
    }
}

bool Dibujo :: perteneceAP1(nodo v) const {
    return v < nodosL1.size();
}

bool Dibujo :: perteneceAP2(nodo v) const {
    return v >= nodosL1.size() && v < nodosL1.size() + nodosL2.size();
}

unsigned int Dibujo :: grado(nodo v) const {
    return g->grado(v);
}

const vector<nodo>& Dibujo :: nodosEnP1(void) const {
    return nodosL1;
}

const vector<nodo>& Dibujo :: nodosEnP2(void) const {
    return nodosL2;
}

GrafoBipartito* Dibujo :: grafo(void) {
    return g;
}
bool estaEn(nodo each, vector<nodo> &li){
    vector<nodo> :: iterator it = li.begin();
    while(it != li.end()){
        if(*it == each){
            return true;
        }
        it++;
    
    }
    return false;
}
unsigned Dibujo :: contarCruces() {
    if(contado == false) {
    	vector<nodo> indice(g->cantNodos());
    	unsigned i;
        
        i = 0;
    	for(vector<nodo> :: const_iterator it =nodosL1.begin(); it != nodosL1.end(); it++) {
    		indice[*it] = i;
    		i++;
    	}
    	i = 0;
    	for(vector<nodo> :: const_iterator it =nodosL2.begin(); it != nodosL2.end(); it++) {
    		indice[*it] = i;
    		i++;
    	}

    	vector< list<nodo> > ejesAux(g->cantNodos());
    	for(vector<nodo> :: const_iterator it = nodosL1.begin(); it != nodosL1.end(); it++) {
    		for(list<nodo> ::const_iterator it2 = ((g->ejes())[*it]).begin(); it2 != ((g->ejes())[*it]).end();it2++) {
    		    if (estaEn(*it2,nodosL2)){
        			ejesAux[*it].push_back(*it2);
        			ejesAux[*it2].push_back(*it);
        		}
    		}
    	}
        cruces = contadorDeCruces(nodosL1,nodosL2,ejesAux,indice,indice);
        contado = true;
    }
    return cruces;
}

std::ostream& operator<< (ostream& o, Dibujo& d) {
    vector<nodo>::const_iterator it;
    o << "------------------------" << endl;
    o << "Dibujo de GrafoBipartito" << endl;
    o << "------------------------" << endl;
    o << "L1: [";
    it = d.nodosEnP1().begin();
    while (it != d.nodosEnP1().end()) {
        o << *it << ",";
        it++;
    }
    o << "]" << endl;
    o << "L2: [";
    it = d.nodosEnP2().begin();
    while (it != d.nodosEnP2().end()) {
        o << *it << ",";
        it++;
    }
    o << "]" << endl;
    o << "Cruces: " << d.contarCruces() << endl;
    o << "------------------------" << endl;

    return o;
}

void Dibujo :: guardar(ofstream& salida) {
    assert(salida.is_open());
    assert(nodosL1.size() == g->V1.size() && nodosL2.size() == g->V2.size());
    
    vector<nodo>::const_iterator it;

    salida << nodosL1.size() << endl;
    it = nodosL1.begin();
    
    while (it != nodosL1.end()) {
        salida << *it + 1 << endl;
        it++;
    }

    salida << nodosL2.size() << endl;
    it = nodosL2.begin();

    while (it != nodosL2.end()) {
        salida << *it + 1 << endl;
        it++;
    }

    // FIXME: borrar las siguientes 6 lineas antes de entregar el TP
    salida << g->listaEjes().size() << endl;
    list<eje>::const_iterator itEjes (g->listaEjes().begin());
    while (itEjes != g->listaEjes().end()) {
        salida << itEjes->primero + 1 << " " << itEjes->segundo + 1 << endl;
        itEjes++;
    }
}

void Dibujo :: operator= (const Dibujo& d) {
    nodosL1 = d.nodosL1;
    nodosL2 = d.nodosL2;
    g = d.g;
    desdeArchivo = false;
    contado = d.contado;
    cruces = d.cruces;
}
