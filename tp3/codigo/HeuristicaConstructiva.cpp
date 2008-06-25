#include "HeuristicaConstructiva.h"


class AdaptadorTabla { 
public:
    AdaptadorTabla(vector<unsigned>& t) : tabla(t) {
    };
    bool operator() (nodo a, nodo b) {
        return tabla[a] > tabla[b];
    };
private:
    vector<unsigned>& tabla; 
};


HeuristicaConstructiva :: HeuristicaConstructiva(Dibujo& original) {
    d = &original;
}

Dibujo HeuristicaConstructiva :: construirSolucion(float a, bool randPos) {
    alfa = a;
    randomPos = randPos;

    inicializar();

    // Ejecuto la heurística constructiva greedy
    nodo sig;
    while (!movil1.empty() || !movil2.empty()) {
        if (!movil1.empty()) {
            sig = tomarSiguiente1();
            insertarEn1(sig);

        }
        if (!movil2.empty()) {
            sig = tomarSiguiente2();
            insertarEn2(sig);
        }
    }

    Dibujo dtmp = Dibujo(d->grafo(), fijo1, fijo2);
    // FIXME: eliminar esto cuando haya una confianza decente
    assert(dtmp.contarCruces() == cruces);
    return dtmp;
}


void HeuristicaConstructiva :: inicializar() {
    // Obtengo las listas de nodos fijos y moviles con las que voy a operar
    fijo1.assign(d->nodosEnP1().begin(), d->nodosEnP1().end());
    fijo2.assign(d->nodosEnP2().begin(), d->nodosEnP2().end());

    vector<nodo>::const_iterator itv;

    movil1 = list<nodo>();
    movil2 = list<nodo>();

    itv = d->grafo()->nodosEnP1().begin();
    while (itv != d->grafo()->nodosEnP1().end()) {
        if (!d->perteneceAP1(*itv)) {
            movil1.push_back(*itv);
        }
        itv++;
    }
    itv = d->grafo()->nodosEnP2().begin();
    while (itv != d->grafo()->nodosEnP2().end()) {
        if (!d->perteneceAP2(*itv)) {
            movil2.push_back(*itv);
        }
        itv++;
    }


    // Guardo en un diccionario quien es movil y quien no
    // (este diccionario se ira modificando a medida que voy "fijando" nodos)
    esMovil = vector<bool>(d->grafo()->cantNodos());
    list<nodo>::const_iterator it;

    it = fijo1.begin();
    while (it != fijo1.end()) {
        esMovil[*it] = false;
        it++;
    }
    it = fijo2.begin();
    while (it != fijo2.end()) {
        esMovil[*it] = false;
        it++;
    }
    it = movil1.begin();
    while (it != movil1.end()) {
        esMovil[*it] = true;
        it++;
    }
    it = movil2.begin();
    while (it != movil2.end()) {
        esMovil[*it] = true;
        it++;
    }

    // Construyo 2 diccionarios que voy a necesitar:
    // - listas de adyacencia del subgrafo ya fijado
    adyParcial = vector< list<nodo> >(d->grafo()->cantNodos());

    // - grados de los nodos (moviles) contando solo los ejes
    //   que van a los nodos ya fijados
    gradoParcial = vector< unsigned >(d->grafo()->cantNodos());

    itv = d->nodosEnP1().begin();
    while (itv != d->nodosEnP1().end()) {
        gradoParcial[*itv] = 0;
        if (!esMovil[*itv]) {
            adyParcial[*itv] = list<nodo>();
        }
        itv++;
    }

    itv = d->nodosEnP2().begin();
    while (itv != d->nodosEnP2().end()) {
        gradoParcial[*itv] = 0;
        if (!esMovil[*itv]) {
            adyParcial[*itv] = list<nodo>();
        }
        itv++;
    }

    list<eje>::const_iterator ite = d->grafo()->listaEjes().begin();
    while (ite != d->grafo()->listaEjes().end()) {
        if (!esMovil[ite->primero] && !esMovil[ite->segundo]) {
            adyParcial[ite->primero].push_back(ite->segundo);
            adyParcial[ite->segundo].push_back(ite->primero);
        }

        if (!esMovil[ite->primero] || !esMovil[ite->segundo]) {
            gradoParcial[ite->primero]++;
            gradoParcial[ite->segundo]++;
        }
        ite++;
    }

    // Almaceno para los nodos fijos su posicion en la particion
    // que les corresponde - esto permite agilizar los conteos de cruces.
    unsigned i;
    posiciones = vector< unsigned > (esMovil.size());

    i = 0;
    it = fijo1.begin();
    while (it != fijo1.end()) {
        posiciones[*it] = i;
        it++;
        i++;
    }
    i = 0;
    it = fijo2.begin();
    while (it != fijo2.end()) {
        posiciones[*it] = i;
        it++;
        i++;
    }

    // Guardo los cruces del dibujo fijo como punto de partida
    // para ir incrementando sobre este valor a medida que agrego nodos.
    cruces = d->contarCruces();
}


nodo HeuristicaConstructiva :: tomarSiguiente(list<nodo>& moviles) {
    // Ordeno los moviles por grado
    ordenarPorGradoParcial(moviles);
    int maximoGrado = gradoParcial[moviles.front()];
    float alfaMaximoGrado = maximoGrado * alfa;

    // Elijo al azar alguno de los que superan el grado alfa-maximo
    unsigned ultimoQueSupera = 0;
    list<nodo>::iterator it = moviles.begin();
    while (++it != moviles.end() &&
           gradoParcial[*it] >= alfaMaximoGrado) {
        ultimoQueSupera++;
    }

    unsigned elegido;
    if (alfa == 1) {
        elegido = 0;
    } else {
        elegido = rand() % (ultimoQueSupera + 1);
    }

    // Busco el elemento en la posición elegida, lo borro
    // de la lista y a lo devuelvo.
    it = moviles.begin();
    for (unsigned i = 0; i != elegido; i++) it++;
    nodo n = *it;
    moviles.erase(it);
    return n;
}

nodo HeuristicaConstructiva :: tomarSiguiente1() {
    return tomarSiguiente(movil1);
}

nodo HeuristicaConstructiva :: tomarSiguiente2() {
    return tomarSiguiente(movil2);
}

void HeuristicaConstructiva :: ordenarPorGradoParcial(list<nodo>& moviles) {
    AdaptadorTabla a(gradoParcial);
    moviles.sort(a);
}


void HeuristicaConstructiva :: insertar(nodo n, list<nodo>& fijos, list<nodo>& otrosFijos) {

    esMovil[n] = false;

    // Actualizo la lista de adyacencias parcial para incorporar las adyacencias
    // del nodo que voy a agregar - esto es necesario puesto que las funciones de conteo
    // de cruces se usan dentro del subgrafo fijo y por tanto para que tengan en cuenta
    // al nodo a agregar, es necesario completarlas con sus ejes.
    adyParcial[n] = list<nodo>();
    list<nodo>::const_iterator it = d->grafo()->ejes()[n].begin();

    while (it != d->grafo()->ejes()[n].end()) {
        if (!esMovil[*it]) {
            adyParcial[*it].push_back(n);
            adyParcial[n].push_back(*it);
        }
        it++;
    }

    // Busco las mejores posiciones en la particion para insertar este nodo,
    // comenzando por el final y swapeando hacia atrás hasta obtener las mejores.
    fijos.push_back(n);
    unsigned c = cruces + crucesPorAgregarAtras(fijos, otrosFijos, adyParcial, posiciones);
    unsigned pos = fijos.size() - 1;
    list<nodo>::iterator itc = fijos.end(); itc--;
    list<nodo>::iterator itcp1 = fijos.end();


    unsigned mejorCruces = c;
    list<unsigned> posValidas;
    posValidas.push_back(pos);

    while (itc != fijos.begin()) {
        pos--;
        itc--;
        itcp1--;

        c = c -
            crucesEntre(*itc, *itcp1, otrosFijos, adyParcial, posiciones) +
            crucesEntre(*itcp1, *itc, otrosFijos, adyParcial, posiciones);
        swap(*itc, *itcp1);

        if (c == mejorCruces) {
            posValidas.push_back(pos);
        }
        if (c < mejorCruces) {
            mejorCruces = c;
            posValidas.clear();
            posValidas.push_back(pos);
        }
    }

    // Inserto el nodo en alguna de las mejores posiciones
    unsigned mejorPos;
    if (randomPos) {
        unsigned randomIndex = rand() % posValidas.size();
        itc = posValidas.begin();
        for(unsigned i = 0; i != randomIndex; i++) itc++;
        mejorPos = *itc;
    } else {
        mejorPos = posValidas.front();
    }

    fijos.pop_front();
    itc = fijos.begin();
    for(unsigned i = 0; i != mejorPos; i++) itc++;
    fijos.insert(itc, n);
    cruces = mejorCruces;

    // FIXME: borrar esto cuando haya fe
    Dibujo dib(d->grafo(), list<nodo>(fijo1), list<nodo>(fijo2));
    assert(dib.contarCruces() == cruces);

    // Actualizo los grados parciales
    it = d->grafo()->ejes()[n].begin();
    while (it != d->grafo()->ejes()[n].end()) {
        if (esMovil[*it]) {
            gradoParcial[*it]++;
        }
        it++;
    }

    // Actualizo las posiciones
    unsigned i;
    i = 0;
    it = fijos.begin();
    while (it != fijos.end()) {
        posiciones[*it] = i;
        it++;
        i++;
    }

}
void HeuristicaConstructiva :: insertarEn1(nodo n) {
    insertar(n, fijo1, fijo2);
}
void HeuristicaConstructiva :: insertarEn2(nodo n) {
    insertar(n, fijo2, fijo1);
}

