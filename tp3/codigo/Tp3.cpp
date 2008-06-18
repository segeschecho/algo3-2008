#include "Tp3.h"

/*
 * saca de un grafo los nodos con grado 0
 * v1Inic = nodos viejos en la particion 1
 * v2Inic =   "     "     "  "     "     2
 * IV1 = nodos nuevos en particion 1
 * IV" = nodos viejos en particion 2
*/

#ifndef imprimirF
#define imprimirF
void imprimir(list<nodo>& l){
    for(list<nodo> :: const_iterator it = l.begin(); it != l.end(); it++){
        cout<<*it<<" ";
    }
    cout<<endl;
}
#endif

#define print(a) cout<<a<<endl;
Tp3::Tp3(Dibujo& entrada,unsigned v1Inic,unsigned v2Inic, unsigned IV1In, unsigned IV2In){
        marcados1 = entrada.nodosEnP1();
        marcados2 = entrada.nodosEnP2();
        v1 = v1Inic;
        v2 = v2Inic;
        IV1 = IV1In;
        IV2 = IV2In;
        GrafoBipartito* g = entrada.grafo();
        grafoOriginal = g;
        list<nodo> marcadosNoNulos1,marcadosNoNulos2,noNulos1,noNulos2;
        for(vector<nodo>:: const_iterator each = entrada.grafo()->nodosEnP1().begin();each != entrada.grafo()->nodosEnP1().end(); each ++){
             if(*each < v1Inic){

                if(!((g->ejes())[*each].empty())){
                   cout<<"each"<<endl;
                   cout<<*each<<endl;
                   cout<<*((g->ejes())[*each].begin())<<endl;
                   marcadosNoNulos1.push_back(*each);
                }
             }
             else if(*each < v2Inic + v1Inic + IV1){
               if(!(g->ejes())[*each].empty()){
                   noNulos1.push_back(*each);
                }
                else{
                    nulos1.push_back(*each);
                }
             }
             else{
                 cout<<"tiene q se menor q esto:"<<v2Inic + v1Inic + IV1<<endl;
                 cout<<*each<<endl;
                 abort();
             }
          }
          for(vector<nodo>:: const_iterator each = entrada.grafo()->nodosEnP2().begin();each != entrada.grafo()->nodosEnP2().end(); each ++){
            if(*each < v2Inic+v1Inic){
              if(!((g->ejes())[*each].empty())){
                marcadosNoNulos2.push_back(*each);
              }
            }
            else{
              if(!(g->ejes())[*each].empty()){
                noNulos2.push_back(*each);
              }
              else{
                nulos2.push_back(*each);
              }
            }
          }
          unsigned tamv1 = marcadosNoNulos1.size();
          unsigned tamv2 =marcadosNoNulos2.size();
          unsigned tamIV1 = noNulos1.size();
          unsigned tamIV2 = noNulos2.size();
          unsigned tam = tamv1+tamv2+tamIV1+tamIV2;
          traduccion = vector<unsigned>(tam);
          unsigned i = 0;
          //TODO: deberia ser list
          vector<list<unsigned> > ejesNuevos(tam);
          vector<nodo> indice(g->cantNodos());
          nuevoP1 = new vector<nodo>(tamv1+tamIV1);
          nuevoP2= new vector<nodo>(tamv2+tamIV2);
          nuevoV1 = new list<nodo>;
          nuevoV2 = new list<nodo>;
          losEjesNuevos = new list<eje>;
          unsigned j = 0;
          for(list<nodo>::iterator each = marcadosNoNulos1.begin(); each != marcadosNoNulos1.end(); each++){
            traduccion[i] = *each;
            indice[*each] = i;
            (*nuevoP1)[j] =  i;
            nuevoV1->push_back(i);
            i = i +1;
            j++;
          }
          j=0;
          for(list<nodo>::iterator each = marcadosNoNulos2.begin(); each != marcadosNoNulos2.end(); each++){
            traduccion[i] = *each;
            indice[*each] = i;
            (*nuevoP2)[j] =  i;
            nuevoV2->push_back(i);
            i = i +1;
            j++;
          }
          j=tamv1;
          for(list<nodo>::iterator each = noNulos1.begin(); each != noNulos1.end(); each++){
            traduccion[i] = *each;
            indice[*each] = i;
            (*nuevoP1)[j] =  i;
            i = i +1;
            j++;
          }
          j=tamv2;
          for(list<nodo>::iterator each = noNulos2.begin(); each != noNulos2.end(); each++){
            traduccion[i] = *each;
            indice[*each] = i;

            (*nuevoP2)[j] =  i;
            i = i +1;
            j++;
          }
          for(list<eje>::const_iterator x =g->listaEjes().begin(); x != g->listaEjes().end(); x++){
            eje e;
            e.primero = indice[x->primero];
            e.segundo = indice[x->segundo];
            losEjesNuevos->push_back(e);
          }

         grafoLimpio = new GrafoBipartito(*nuevoP1,*nuevoP2,*losEjesNuevos);
         cout<<"llegaste aca????"<<endl;
         dibujoLimpio = new Dibujo(grafoLimpio,*nuevoV1,*nuevoV2);
         cout<<"y aca????"<<endl;
}

Dibujo Tp3:: reconstruirDibujo(Dibujo& resuelto){
       unsigned i = 0;
       p1Posta = new list<nodo>();
       for(vector<nodo> :: const_iterator each =resuelto.nodosEnP1().begin(); each != resuelto.nodosEnP1().end();each++){
            if( !(traduccion[*each] < v1)){
               p1Posta->push_back(traduccion[*each]);
            }else{
               while(i < marcados1.size() && marcados1[i] != traduccion[*each]){
                   p1Posta->push_back(marcados1[i]);
                   i++;
               }
               i++;
               p1Posta->push_back(traduccion[*each]);
            }
       }
        print("p1Posta");
        imprimir(*p1Posta);
        print("nulos1");
        imprimir(nulos1);
        p1Posta->splice(p1Posta->end(),nulos1);

        while(i < marcados1.size()){
             p1Posta->push_back(marcados1[i]);
	     i++;
        }
       print("p1Posta");
    imprimir(*p1Posta);
    print((*p1Posta).size());
       p2Posta = new list<nodo>();
       for(vector<nodo> :: const_iterator each =resuelto.nodosEnP2().begin(); each != resuelto.nodosEnP2().end();each++){
            if( !(traduccion[*each] < v1)){
               p2Posta->push_back(traduccion[*each]);
            }else{
               while(i < marcados2.size() && marcados2[i] != traduccion[*each]){
                   p2Posta->push_back(marcados1[i]);
                   i++;
               }
               i++;
               p2Posta->push_back(traduccion[*each]);
            }
       }
        p2Posta->splice(p2Posta->end(),nulos2);
        while(i < marcados2.size()){
             p2Posta->push_back(marcados2[i]);
	     i++;
        }
        return Dibujo(grafoOriginal,*p1Posta,*p2Posta);
}


