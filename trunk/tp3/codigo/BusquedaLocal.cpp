#include "BusquedaLocal.h"
#define print(a) cout<<a<<endl;

//crea una instancia de busqueda local a partir de un dibujo original
//que despues se va a limpiar
//se asuma que el dibujo original fue limpiado
//y que el incremntal que debe mejorar se construyo a partir
//de este
BusquedaLocal :: BusquedaLocal(Dibujo& original){
    minimoP2 = original.nodosEnP1().size();
    maximoP2 = minimoP2 + original.nodosEnP2().size() - 1;
    orig = &original;
}

//decide si x es de los nodos cuyo orden relativo debe respetarse
bool BusquedaLocal ::esFijo(nodo x){
    return orig->perteneceAP1(x) || orig->perteneceAP2(x);
}

//decide si x es fijo en la particion 1
bool BusquedaLocal :: perteneceAP1(nodo x){
      return orig->perteneceAP1(x);
}

//decide si x es fijo en la particion 2
bool BusquedaLocal :: perteneceAP2(nodo x){
    return orig->perteneceAP2(x);
}

//determina el rango en el q x puede moverse

pair<unsigned,unsigned> BusquedaLocal :: rango(nodo x, list<nodo>& pi,vector<nodo>& indice){
    unsigned tam = pi.size();
    //si x no es fijo, lo muevo por toda la particion
    if (! esFijo(x)){

        return pair<unsigned,unsigned>(0,tam+1);
    }
    else{
            unsigned posxMarcado;
            unsigned anterior = 0;
            unsigned siguiente = tam+1;
            //si esta en la primer particion y es marcado
            if(perteneceAP1(x)){
                posxMarcado = x;
                //si hay un marcado anterior, si o si tengo q ponerlo adelante de ese
                if (posxMarcado != 0){
                     anterior = indice[posxMarcado-1]+1;
               }
               //si hay un marcado posterior lo muevo hasta ese y no mas (marcado == fijo)
               if (posxMarcado !=minimoP2-1){
				   siguiente = indice[posxMarcado+1]+1;
               }
            }
            //hago lo mismo si estaba fijo en la otra particion
            else{
                posxMarcado = x;
                if (posxMarcado != minimoP2){
					anterior=indice[posxMarcado-1]+1;
                }
               if (posxMarcado != maximoP2){
					 siguiente = indice[posxMarcado+1]+1;
               }
            }

    return pair<unsigned, unsigned> (anterior, siguiente);
    }
}

list<nodo> :: iterator iteradorAvanzado(list<nodo> :: iterator it, unsigned offset){
	list<nodo> :: iterator it2 = it;
	while(offset > 0){
		it2++;
		offset--;
	}
	return it2;
}
//saca un elemento de un vector (no actualiza indice)
//pero devuelve de que posicion lo saco para poder actualizar el indice
unsigned sacar(list<nodo>& li,nodo x,vector<nodo>& indice){
    unsigned pos = indice[x];
	li.erase(iteradorAvanzado(li.begin(),pos));
	return pos;
	/*unsigned i = 0;
    for(vector<nodo> :: iterator it = li.begin(); it != li.end(); it++){
        if(*it == x){
            li.erase(it);
            return i;
        }
        i++;
    }
    //FIXME:
    cout<<"me fui de mambo en sacar"<<endl;
    abort();*/
}

//actualiza el indice por insertar un nodo en li en la pos inic
void actualizarIndice(list<nodo>& li,unsigned inic,vector<nodo>& indice){
    //primer pos que tengo q cambiar
     list<nodo>::iterator tipito = iteradorAvanzado(li.begin(),inic);
     unsigned pos = inic;
     //del nuevo en adelante todos cambian su pos
     while( tipito != li.end()){
         indice[*tipito] = pos;
         pos++;
         tipito++;
     }
}

//actualiza los indices cuando saco a un nodo de li, y el nodo estaba en donde
void actualizarIndicePorSacar(list<nodo>& li,unsigned donde,vector<nodo>& indice){
    list<nodo>::iterator tipito = iteradorAvanzado(li.begin(),donde);
    while(tipito != li.end()){
        indice[*tipito]--;
        tipito++;
    }

}

// funcion que engloba cada paso de la busqueda local
void BusquedaLocal :: mejorar(list<nodo>& l1, list<nodo>& l2, const  vector< list<nodo> >& diccEjes,vector<nodo>& indice){

    unsigned i = 0;
/*
    for(vector<nodo> :: iterator it = l1.begin(); it != l1.end(); it++){
        print(*it);
        print("indice");
        print(indice[*it]) ;
        i+=1;
    }
    i=0;*/
    //l1Aux me sirve para iterar por los elementos de l1
    list<nodo> l1Aux = list<nodo>(l1);
    //bucle que recorre a todos los elementos de l1
    for(list<nodo>::iterator each = l1Aux.begin(); each != l1Aux.end(); each++){
        //saco al nodo candidato
        unsigned pos = sacar(l1,*each,indice);
        //como lo saque, actualizo los indice
        actualizarIndicePorSacar(l1,pos,indice);
        //determino en que posiciones lo puedo poner
        pair<unsigned,unsigned> rangoi = rango(*each,l1,indice);
        //lo coloco en la primera posible
        l1.insert(iteradorAvanzado(l1.begin(),rangoi.first),*each);
        //actualizo cada indice
        actualizarIndice(l1,rangoi.first,indice);
        //cuanto la cantidad de cruces (a priori no hay algo mucho mas eficiente porq el tipo pudo cambiar mucho de pos)
        unsigned crucesInicial = contadorDeCruces(l1,l2,orig->grafo()->ejes(),indice,indice);
        //posMinima es la mejor posicion hasta el momento
        unsigned posMinima = rangoi.first;
        // la cantidad de cruces en este momento es la inicial
        unsigned crucesAhora = crucesInicial;
        // y tb es la menor cantidad de cruces
        unsigned crucesMin = crucesInicial;
        //recorro las posiciones donde puedo poner al nodo
        i=rangoi.first;
		list<nodo> :: iterator elem = iteradorAvanzado(l1.begin(),i);
        while( i < rangoi.second-1){
			list<nodo> :: iterator elemMasUno = iteradorAvanzado(elem,1);
                //cruces entre el nodo i, y el siguiente antes de un intercambio
                unsigned crucesPreSwap = crucesEntre(*elem,*elemMasUno,l2,orig->grafo()->ejes(),indice);
                //cruces luego de q los invierto
                unsigned crucesPostSwap = crucesEntre(*elemMasUno,*elem,l2,orig->grafo()->ejes(),indice);
                //solo cambian los cruces entre ellos 2
                crucesAhora = crucesAhora - crucesPreSwap + crucesPostSwap;
                //cout<<"crucesAhora "<<crucesAhora<<endl;
                //realizo elswap
                nodo aux = *elem;
                *elem = *elemMasUno;
                *elemMasUno = aux;
                //restauro los indices
                unsigned aux2 = indice[*elem];
                indice[*elem] = indice[*elemMasUno];
                indice[*elemMasUno] = aux2;
                //cout<<"posta hay "<<contadorDeCruces(l1,l2,orig->grafo()->ejes(),indice,indice)<<endl;
                //si baje los cruces, me guardo la nueva pos
                if (crucesAhora < crucesMin){
                   // cout<<"mejor"<<endl;
                    crucesMin = crucesAhora;
                    posMinima = i+1;

                }
			elem++;
            i++;
        }
        //ya recorri todo el rango, entonces lo saco
        pos=sacar(l1,*each,indice);
        //actualizo indices
        actualizarIndicePorSacar(l1,pos,indice);
        //lo vuelvo a insertar, esta vez en su mejor posicion
        l1.insert(iteradorAvanzado(l1.begin(),posMinima),*each);
        actualizarIndice(l1,posMinima,indice);
       // cout<<"lo puse en su mejor pos y me quedo con "<<contadorDeCruces(l1,l2,orig->grafo()->ejes(),indice,indice)<<endl;

    }
    i=0;
    //ahora hacemos el mismo procedimiento para la otra particion
    list<nodo> l2Aux(l2);
    for(list<nodo>::iterator each = l2Aux.begin(); each != l2Aux.end(); each++){

        unsigned pos = sacar(l2,*each,indice);

        actualizarIndicePorSacar(l2,pos,indice);

        pair<unsigned,unsigned> rangoi = rango(*each,l2,indice);

        l2.insert(iteradorAvanzado(l2.begin(), rangoi.first),*each);

        actualizarIndice(l2,rangoi.first,indice);

        unsigned crucesInicial = contadorDeCruces(l1,l2,orig->grafo()->ejes(),indice,indice);

        unsigned posMinima = rangoi.first;

        unsigned crucesAhora = crucesInicial;

        unsigned crucesMin = crucesInicial;

        i = rangoi.first;

		list<nodo> :: iterator elem = iteradorAvanzado(l2.begin(),i);

        while( i < rangoi.second-1){
                list<nodo> :: iterator elemMasUno = iteradorAvanzado(elem,1);

                unsigned crucesPreSwap = crucesEntre(*(elem),*elemMasUno,l1,orig->grafo()->ejes(),indice);

                unsigned crucesPostSwap = crucesEntre(*elemMasUno,*(elem),l1,orig->grafo()->ejes(),indice);

                crucesAhora = crucesAhora - crucesPreSwap + crucesPostSwap;
                
				nodo aux = *(elem);

                *(elem) = *elemMasUno;

                *elemMasUno = aux;

                unsigned aux2 = indice[*elem];

                indice[*elem] = indice[*elemMasUno];

                indice[*elemMasUno] = aux2;

                if (crucesAhora < crucesMin){

                    crucesMin = crucesAhora;

                    posMinima = i+1;

                }
            i++;
			elem++;

        }

        pos=sacar(l2,*each,indice);

        actualizarIndicePorSacar(l2,pos,indice);

        l2.insert(iteradorAvanzado(l2.begin(),posMinima),*each);

        actualizarIndice(l2,posMinima,indice);
    }


}

//funcion que toma un dibujo candidato e intenta mejorarlo
//mediante la reinsercion de nodos hasta hallar un minimo local
Dibujo BusquedaLocal :: hallarMinimoLocal(Dibujo& candidato){
    //creo el arreglo donde voy a guardar los indices de los tipitos
    vector<nodo> indice(orig->grafo()->cantNodos());
    //copio las particiones del dib candidato porque gonza no me lo deja mutar
    //vector<nodo> l1 = vector<nodo>(candidato.nodosEnP1());
      list<nodo> l1(candidato.nodosEnP1().begin(),candidato.nodosEnP1().end()); 
    //vector<nodo> l2 = vector<nodo>(candidato.nodosEnP2());
      list<nodo> l2(candidato.nodosEnP2().begin(),candidato.nodosEnP2().end());
    unsigned i = 0;
    //asigno los indices a p1
    for(list<nodo> :: iterator it = l1.begin(); it != l1.end(); it++){
        indice[*it] = i;

        i+=1;
    }
    i = 0;
    //analogo para p2
    for(list<nodo> :: iterator it = l2.begin(); it != l2.end(); it++){

        indice[*it] = i;
        i+=1;
    }

    //me guardo cuantas cruces tiene este dibujo
    unsigned crucesInicial = contadorDeCruces(candidato.nodosEnP1(),candidato.nodosEnP2(),(candidato.grafo())->ejes(),indice,indice);
    cout<<"cruces inicial "<<crucesInicial<<endl;
    //flag de cambio para saber cuando me estanque
    bool cambio = true;
    //contador de cruces en cada iteracion
    unsigned crucesActual=0;

    //ciclo de mejora
    while(cambio){
        cambio = false;
        //intento mejorar
        mejorar(l1,l2,candidato.grafo()->ejes(),indice);
        //cuento el nuevo numero de cruces
        crucesActual = contadorDeCruces(l1,l2,candidato.grafo()->ejes(),indice,indice);
        //si mejoro hay q volver a iterar
        if(crucesActual < crucesInicial){
            crucesInicial = crucesActual;
            cout<<"mejore "<<crucesActual<<endl;
            cambio = true;
        }
    }
    //devolvemos lo mejor que pudimos hacer
    return Dibujo(candidato.grafo(),l1,l2);

}

