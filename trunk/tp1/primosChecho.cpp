#include <stdio.h>
#include <list.h>
#include <math.h>

void primoMaxPotencia(int n, int &primo, int &potencia);
int calcularPotencia(int n, int primo);
bool esPrimo(int n, list<int> l);

int main(){
    int primo = 0;
    int pot = 0;
    primoMaxPotencia(991, primo, pot);

    cout << "resultado, primo: " << primo << "  potencia " << pot << endl;
    return 0;
}

void primoMaxPotencia(int n, int &primo, int &potencia){
    list<int> l;
    int maxPrimo = 0;
    int maxPotencia = 0;

    int primoActual = 2;
    int potenciaActual = 0;

    int temp = 0;
    int i = 1;
    int k = 1;

    //pruebo a mano los primeros 3 primos: 2, 3 y 5
    if(n%2 == 0){
        potenciaActual = calcularPotencia(n, 2);
        if(potenciaActual > 0)
            primoActual = 2;
    }

    if(n%3 == 0){
        temp = calcularPotencia(n, 3);
        if(temp > potenciaActual){
            primoActual = 3;
            potenciaActual = temp;
        }
    }


    if(n%5 == 0){
        temp = calcularPotencia(n, 5);
        if(temp > potenciaActual){
             primoActual = 5;
             potenciaActual = temp;
        }
      }


    while(primoActual <= (int)sqrt(n)){
         if( (n % primoActual == 0) && esPrimo(primoActual, l)){
              l.push_back(primoActual);
              potenciaActual = calcularPotencia(n, primoActual);

              if(potenciaActual > maxPotencia || ((potenciaActual == maxPotencia) &&  (primoActual > maxPrimo))){
                   maxPotencia = potenciaActual;
                   maxPrimo = primoActual;
              }
         }
         
         primoActual = 6*i + k;
         
         if(k == 1)
             k = 5;
         else
             k = 1;

         i++;
    }

    if(l.size() == 0){
        primo = n;
        potencia = 1;
    }else{
        primo = maxPrimo;
        potencia = maxPotencia;
    }
}

int calcularPotencia(int n, int primo){
    int res = 0;

    while(n%primo == 0){
        res = res + 1;
        n = n/primo;
    }

    return res;
}

bool esPrimo(int n, list<int> l){
    bool res = true;
    list<int>::iterator it;

    for (it = l.begin(); it != l.end(); it++){
        if(n % (*it) == 0)
            return false;
    }
    
    return true;
}
