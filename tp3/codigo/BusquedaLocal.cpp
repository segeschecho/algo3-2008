#include "BusquedaLocal.h"
#define print(a) cout<<a<<endl;
nodo minElem(const vector<nodo>& p) {
    nodo minimo = p[0];
    for(unsigned int i = 1; i < p.size(); i++) {
        if ( p[i] < minimo) {
            minimo = p[i];
        }
    }
    return minimo;
}

BusquedaLocal :: BusquedaLocal(Dibujo& original){
	//obtengo valores que me van a permitir crear los arreglos con la info del dibujo original
	// si los arreglos no son vacios los calculo
	// sino pongo valores para determinar que son validos
	//if(original.nodosEnP1().size() > 0){

	     //maximoP1 = original.nodosEnP1.size()-1//maxElem(original.nodosEnP1());
	     //estaEnP1 = vector<bool>(maximoP1+1,false);
	     //indiceP1 = vector<unsigned>(maximoP1+1);
	     //p1 = vector<nodo>(original.nodosEnP1().size());
             /* todo esto es al pedo, porq puedo usar que los nodos tan ordenados
                y que ademas los elementos marcados van de 0 a cierto numerito */
	/*}
	else{
	    maximoP1 = 0;
	}*/
	/*if(original.nodosEnP2().size() > 0){
        maximoP2 = maxElem(original.nodosEnP2());
        minimoP2 = minElem(original.nodosEnP2());
        estaEnP2 = vector<bool>(maximoP2 - minimoP2 + 1,false);
        indiceP2 = vector<unsigned>(maximoP2+1);
        p2 = vector<unsigned>(original.nodosEnP2().size());
	}
	else{
	    maximoP2 = 0;
	    minimoP2 = 0;
	}
	unsigned i = 0;
	for(vector<unsigned> :: const_iterator it = original.nodosEnP1().begin();it != original.nodosEnP1().end(); it++){
	    indiceP1[*it] = i;
	    p1[i] = *it;
	    i++;
	    estaEnP1[*it] = true;

	}
	i = 0;
	for(vector<unsigned> :: const_iterator it = original.nodosEnP2().begin();it != original.nodosEnP2().end(); it++){
	    p2[i] = *it;
	    indiceP2[*it-minimoP2] = i;
	    i++;
	    estaEnP2[*it-minimoP2] = true;
	}
*/      minimoP2 = original.nodosEnP1().size();
        maximoP2 = minimoP2 + original.nodosEnP2().size() - 1;
        orig = &original;
}

bool BusquedaLocal ::esFijo(nodo x){
    return orig->perteneceAP1(x) || orig->perteneceAP2(x);
}

unsigned BusquedaLocal :: obtenerIndice(nodo x, const vector<nodo>& pi){
    unsigned i = 0;
    vector<nodo> :: const_iterator it = pi.begin();
    while(it != pi.end()){
        //print(pi[i]);
        if(pi[i] == x)
            return i;
        i++;
        it++;
    }

    cout<<"error en obtener indice"<<endl;
    abort();
}

bool BusquedaLocal :: perteneceAP1(nodo x){
    //return !p1.empty() && x <= maximoP1 && estaEnP1[x];
      return orig->perteneceAP1(x);
}

bool BusquedaLocal :: perteneceAP2(nodo x){
    return orig->perteneceAP2(x);
    //return !p2.empty() && minimoP2 <= x && x <= maximoP2 && estaEnP2[x-minimoP2];
}

pair<unsigned,unsigned> BusquedaLocal :: rango(nodo x, vector<nodo>& pi,vector<nodo>& indice){
    /*print("x");
    print(x);*/
    unsigned tam = pi.size();
    if (! esFijo(x)){
    //print("x no fijo");
    //print(x);
        return pair<unsigned,unsigned>(0,tam+1);
    }
    else{
            unsigned posxMarcado;
            unsigned anterior = 0;
            unsigned siguiente = tam+1;
            if(perteneceAP1(x)){
                posxMarcado = x;
                if (posxMarcado != 0){
                    //anterior = obtenerIndice(posxMarcado-1,pi)+1;
                     anterior = indice[posxMarcado-1]+1;
               }
               if (posxMarcado !=minimoP2-1){
                   //siguiente = obtenerIndice(posxMarcado+1,pi)+1;
				   siguiente = indice[posxMarcado+1]+1;
               }
            }
            else{

                posxMarcado = x;
    //            print("x:");
  //              print(x);
//                print(posxMarcado);
                /*print("posxmarcado");
                print(posxMarcado);
                print("indice de x");
                print(indiceP2[x]);*/
                if (posxMarcado != minimoP2){
                    //anterior = obtenerIndice(posxMarcado-1,pi)+1;
					anterior=indice[posxMarcado-1]+1;
               }
               if (posxMarcado != maximoP2){
					 siguiente = indice[posxMarcado+1]+1;
                   //siguiente = obtenerIndice(posxMarcado+1,pi)+1;
               }
            }

    return pair<unsigned, unsigned> (anterior, siguiente);
    }
}
unsigned sacar(vector<nodo>& li,nodo x){
    unsigned i = 0;
    for(vector<nodo> :: iterator it = li.begin(); it != li.end(); it++){
        if(*it == x){
            li.erase(it);
            return i;
        }
        i++;
    }
    cout<<"me fui de mambo en sacar"<<endl;
    abort();
}

void actualizarIndice(vector<nodo>& li,unsigned inic,unsigned fin,vector<nodo>& indice){
     vector<nodo> :: iterator tipito = (li.begin()+inic);
     unsigned pos = inic;
     while(pos <= fin){
       indice[*tipito] = pos;
       pos++;
       tipito++;
     }
}


void BusquedaLocal :: mejorar(vector<nodo>& l1, vector<nodo>& l2, const  vector< list<nodo> >& diccEjes,vector<nodo>& indice){
    //FIXME: la funcion de contarCruces no esta buena

    unsigned i = 0;

    /*for(vector<nodo> :: iterator it = l2.begin(); it != l2.end(); it++){
        print(*it);
        indice[*it] = i;
        i+=1;
    }*/
    i=0;
    vector<nodo> l1Aux = vector<nodo>(l1);
    for(vector<nodo>::iterator each = l1Aux.begin(); each != l1Aux.end(); each++){
        unsigned pos = sacar(l1,*each);
        pair<unsigned,unsigned> rangoi = rango(*each,l1,indice);

        l1.insert(l1.begin() + rangoi.first,*each);
        actualizarIndice(l1,rangoi.first,pos,indice);
        unsigned crucesInicial = contadorDeCruces(l1,l2,orig->grafo()->ejes(),indice,indice);//FIXME
        unsigned posMinima = rangoi.first;
        unsigned crucesAhora = crucesInicial;
        unsigned crucesMin = crucesInicial;
        i = rangoi.first;
        //print("rangoisecond");
        //print(rangoi.second);

        while( i < rangoi.second-1){
                //cout<< "i: "<<i<<endl;

                unsigned crucesPreSwap = crucesEntre(l1[i],l1[i+1],l2,orig->grafo()->ejes(),indice);
                unsigned crucesPostSwap = crucesEntre(l1[i+1],l1[i],l2,orig->grafo()->ejes(),indice);
                crucesAhora = crucesAhora - crucesPreSwap + crucesPostSwap;
                nodo aux = l1[i];
                l1[i] = l1[i+1];
                l1[i+1] = aux;
                if (crucesAhora < crucesMin){
                    crucesMin = crucesAhora;
                    posMinima = i+1;
                }
            i++;
        }
        //cout<<"hola"<<endl;
        pos=sacar(l1,*each);
        l1.insert(l1.begin()+posMinima,*each);
        actualizarIndice(l1,posMinima,pos,indice);

    }
    i = 0;
    print("p1");
    /*for(vector<nodo> :: iterator it = l1.begin(); it != l1.end(); it++){
        print(*it);
        indice[*it] = i;
        i+=1;
    }*/
    i=0;
    vector<nodo> l2Aux = vector<nodo>(l2);
     for(vector<nodo>::iterator each = l2Aux.begin(); each != l2Aux.end(); each++){
        unsigned pos = sacar(l2,*each);
        pair<unsigned,unsigned> rangoi = rango(*each,l2,indice);
        l2.insert(l2.begin() + rangoi.first,*each);
        actualizarIndice(l2,rangoi.first,pos,indice);
        unsigned crucesInicial = contadorDeCruces(l1,l2,orig->grafo()->ejes(),indice,indice);
        unsigned posMinima = rangoi.first;
        unsigned crucesAhora = crucesInicial;
        unsigned crucesMin = crucesInicial;
        i = rangoi.first;
        while( i < rangoi.second-1){
                    print("p2 se mueve");
               for(vector<nodo> :: iterator it = l2.begin(); it != l2.end(); it++){
        print(*it);

               }
                unsigned crucesPreSwap = crucesEntre(l2[i],l2[i+1],l1,orig->grafo()->ejes(),indice);
                unsigned crucesPostSwap = crucesEntre(l2[i+1],l2[i],l1,orig->grafo()->ejes(),indice);
                crucesAhora = crucesAhora - crucesPreSwap + crucesPostSwap;
                nodo aux = l2[i];
                l2[i] = l2[i+1];
                l2[i+1] = aux;
                if (crucesAhora < crucesMin){
                    crucesMin = crucesAhora;
                    posMinima = i+1;
                }
            i++;
        }
        pos=sacar(l2,*each);
        l2.insert(l2.begin()+posMinima,*each);
        actualizarIndice(l2,pos,posMinima,indice);
    }

}

Dibujo BusquedaLocal :: hallarMinimoLocal(Dibujo& candidato){
    vector<nodo> indice(orig->grafo()->cantNodos());
    vector<nodo> l1 = vector<nodo>(candidato.nodosEnP1());
    vector<nodo> l2 = vector<nodo>(candidato.nodosEnP2());
    unsigned i = 0;
    for(vector<nodo> :: iterator it = l1.begin(); it != l1.end(); it++){
        print(*it);
        indice[*it] = i;
        i+=1;
    }
    i = 0;
    for(vector<nodo> :: iterator it = l2.begin(); it != l2.end(); it++){
        print(*it);
        indice[*it] = i;
        i+=1;
    }
    unsigned crucesInicial = contadorDeCruces(candidato.nodosEnP1(),candidato.nodosEnP2(),(candidato.grafo())->ejes(),indice,indice);
    bool cambio = true;

    unsigned crucesActual=0;


    while(cambio){
        cambio = false;
        mejorar(l1,l2,candidato.grafo()->ejes(),indice);
        crucesActual = contadorDeCruces(l1,l2,candidato.grafo()->ejes(),indice,indice);
        if(crucesActual < crucesInicial){
            crucesInicial = crucesActual;
            cambio = true;
        }
    }
    return Dibujo(candidato.grafo(),l1,l2);
}

