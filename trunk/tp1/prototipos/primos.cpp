#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;

void maxFactorPrim(unsigned long long n, unsigned& primo, unsigned& potencia){
    int pot = 0;
    int num = 0;
    int cand;
    int maxPot = 0;
    int maxPrim = 0;
    //Casos especiales
    // primo = 2
    while(n % 2 == 0){
        pot++;
        n=n/2;
    }
    if(pot != 0){
        maxPot = pot;
        pot = 0;
        maxPrim = 2;
    }
    //primo = 3
    while(n % 3 == 0){
        pot++;
        n=n/3;
    }
    if(pot >= maxPot && pot != 0){
        maxPot = pot;
        pot = 0;
        maxPrim = 3;
    }
    //primo = 5
    while(n % 5 == 0){
        pot++;
        n=n/5;
    }
    if(pot >= maxPot && pot!= 0){
        maxPot = pot;
        pot = 0;
        maxPrim = 5;
    }

    int k = 1;
    int j = 1;
    double s = sqrt(n*1.0);
    //arrancamos en 7 e iteramos por todos los numeros de la forma 6*k+1 o 6*k+5
    cand = 7;
    while(cand <= s){
        //dividimos para obtener la potencia
        while(n % cand == 0){
            pot++;
            n = n / cand;
       }
    //actualizamos el maximo
    if (pot >= maxPot && pot != 0){
            maxPot = pot;

            maxPrim = cand;
    }
    pot = 0;
    //actualizamos el limite hasta donde iterar
    s = sqrt(n)+1;
    //armamos el proximo candidato segun la formula
    if(j == 1){
        cand = 6*k + 5;
        k++;
        j=0;
    }
    else{
        cand = 6*k+1;
        j=1;
    }
    }
    //si cand se paso es porq me quedo un n primo, solo podra ser el maximo si no hay otro con exponenete mayor q 1
    if(cand > s && maxPot <= 1){
        maxPrim = n;
        maxPot = 1;
    }
    // creo q se puede sacar, se fija el caso en q el numero de entrada sea primo
    if(maxPot == 0){
        maxPrim = n;
        maxPot = 1;
    }

    primo = maxPrim;
    potencia =maxPot;
}

 int main(int argc, char* argv[]){
     unsigned  primo;
     unsigned potencia;
     unsigned long long n = 32949815ULL;
     n=n*n;
     cout<<n<<endl;
     maxFactorPrim(n,primo,potencia);
     cout<<primo<<endl;
     cout<<potencia<<endl;
     return 0;
 }
