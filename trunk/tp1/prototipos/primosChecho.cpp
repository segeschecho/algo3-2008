#include <stdio.h>
#include <list.h>
#include <math.h>

void primoMaxPotencia(unsigned long long int n, unsigned long long int &primo, int &potencia);
int calcularPotencia(int n, unsigned long long int primo);
bool esPrimo(int n, list<int> l);

int main(){
    unsigned long long int a = 12312349223569LL;
    unsigned long long int primo = 0;
    int pot = 0;
    primoMaxPotencia(a, primo, pot);

    cout << "resultado, primo: " << primo << "  potencia " << pot << endl;
    return 0;
}

void primoMaxPotencia(unsigned long long int n, unsigned long long int &primo, int &potencia){
    //unsigned long long int a = 12312349223569LL;
    list<int> l;
    unsigned long long int  maxPrimo = 0;
    int maxPotencia = 0;

    unsigned long long int  primoActual = 2;
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
        if(temp >= potenciaActual){
            primoActual = 3;
            potenciaActual = temp;
        }
    }


    if(n%5 == 0){
        temp = calcularPotencia(n, 5);
        if(temp >= potenciaActual){
             primoActual = 5;
             potenciaActual = temp;
        }
      }


    while(primoActual <= (unsigned long long int)sqrt(n)){
         if( (n % primoActual == 0) && esPrimo(primoActual, l)){
              l.push_back(primoActual);
              potenciaActual = calcularPotencia(n, primoActual);

              if(potenciaActual > maxPotencia || ((potenciaActual == maxPotencia) &&  (primoActual > maxPrimo))){
                   maxPotencia = potenciaActual;
                   maxPrimo = primoActual;
              }

              //n = n / (primoActual^potenciaActual);
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
        if(esPrimo(n, l) && (n > maxPrimo)){
            cout << "holaa" << maxPrimo << endl;
            primo = n;
            potencia = 1;
        }
        else
        {
            primo = maxPrimo;
            potencia = maxPotencia;
        }
    }
}

int calcularPotencia(int n, unsigned long long int primo){
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
