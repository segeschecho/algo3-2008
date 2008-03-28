#include <stdio.h>
#include <list.h>
#include <math.h>

using namespace std;

void primoMaxPotencia(unsigned long long int n, unsigned long long int &primo, int &potencia);
int calcularPotencia(int n, unsigned long long int primo);
bool esPrimo(int n, list<unsigned long long int> &l);

int main(){
    unsigned long long int a = 12312346223569LL;
    unsigned long long int primo = 0;
    int pot = 0;

    primoMaxPotencia(a, primo, pot);

    cout << "resultado, primo: " << primo << "  potencia " << pot << endl;
    return 0;
}

void primoMaxPotencia(unsigned long long int n, unsigned long long int &primo, int &potencia){
    list<unsigned long long int> l;
    unsigned long long int  maxPrimo = 0;
    int maxPotencia = 0;

    unsigned long long int  primoActual = 2;
    int potenciaActual = 0;

    unsigned long long int limite = (unsigned long long int)sqrt(n);

    int temp = 0;
    int i = 1;

    //pruebo a mano los primeros 3 primos: 2, 3 y 5
    if(n%2 == 0){
        potenciaActual = calcularPotencia(n, 2);
        if(potenciaActual > 0){
            primoActual = 2;
            maxPrimo = 2;
            maxPotencia = potenciaActual;

            n = (unsigned long long int)(n/pow(2, potenciaActual));
            limite = (unsigned long long int)sqrt(n);
        }
    }
    l.push_back(2);     //agrego el primo a la lista de primos

    if(n%3 == 0){
        temp = calcularPotencia(n, 3);
        if(temp >= potenciaActual){
            primoActual = 3;
            potenciaActual = temp;
            maxPrimo = 3;
            maxPotencia = temp;

            n = (unsigned long long int)(n/pow(3, potenciaActual));
            limite = (unsigned long long int)sqrt(n);
        }
    }
    l.push_back(3);     //agrego el primo a la lista de primos


    if(n%5 == 0){
        temp = calcularPotencia(n, 5);
        if(temp >= potenciaActual){
            primoActual = 5;
            potenciaActual = temp;
            maxPrimo = 5;
            maxPotencia = temp;

            n = (unsigned long long int)(n/pow(5, potenciaActual));
            limite = (unsigned long long int)sqrt(n);
        }
    }
    l.push_back(5);    //agrego el primo a la lista de primos

    while(primoActual <= limite){
        primoActual = 6*i + 1;

        bool es = esPrimo(primoActual, l);
        if(es)
            l.push_back(primoActual);

        if( (n % primoActual == 0) && es){
            potenciaActual = calcularPotencia(n, primoActual);

            if(potenciaActual > maxPotencia || ((potenciaActual == maxPotencia) &&  (primoActual > maxPrimo))){
                 maxPotencia = potenciaActual;
                 maxPrimo = primoActual;

                 cout << maxPrimo << "  potencia   " << maxPotencia << endl;
            }

            n = (unsigned long long int)(n / pow(primoActual, potenciaActual));
            limite = (unsigned long long int)sqrt(n);
        }

        primoActual = 6*i + 5;

        es = esPrimo(primoActual, l);
        if(es)
            l.push_back(primoActual);

        if( (n % primoActual == 0) && es){
            potenciaActual = calcularPotencia(n, primoActual);

            if(potenciaActual > maxPotencia || ((potenciaActual == maxPotencia) &&  (primoActual > maxPrimo))){
                 maxPotencia = potenciaActual;
                 maxPrimo = primoActual;

                 cout << maxPrimo << "  potencia   " << maxPotencia << endl;

            }

            n = n / (unsigned long long int)(pow(primoActual, potenciaActual));
            limite = (unsigned long long int)sqrt(n);
        }

        i++;
    }
cout << "n :" << n << endl;
    if(l.size() == 0){
        primo = n;
        potencia = 1;
    }
    else
    {
        if(esPrimo(n, l) && (n > maxPrimo)){
            primo = n;
            potencia = 1;
        }
        else
        {
            primo = maxPrimo;
            potencia = maxPotencia;
        }
    }

/*    list<unsigned long long int>::iterator it;
    cout << "primos: " << endl;
    for (it = l.begin(); it != l.end(); it++){
        cout << (*it) << endl;
    }*/
}

int calcularPotencia(int n, unsigned long long int primo){
    int res = 0;

    while(n%primo == 0){
        res = res + 1;
        n = n/primo;
    }

    return res;
}

bool esPrimo(int n, list<unsigned long long int> &l){
    list<unsigned long long int>::iterator it;
    int limite = (int)sqrt(n);

    for (it = l.begin(); it != l.end(); it++){
        if((*it) > limite)
            return true;
        if(n % (*it) == 0)
            return false;
    }

    return true;
}
