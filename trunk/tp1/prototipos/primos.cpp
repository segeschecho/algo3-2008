#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;

void maxFactorPrimTester(unsigned long long desde, unsigned long long hasta, char* archivo){
    ofstream output;
    output.open(archivo, ios_base::out);

    for (unsigned long long num = desde; num <= hasta; num++){
        unsigned long long reconstruido = 1, n = num;
        int pot = 0;
        int maxPot = 1;
        int maxPrim = 1;
        double raiz = sqrt((double)n);

        cout << "Numero: \t" << n << endl;
        output << "Numero: \t" << n << endl;
        output << "Factorizacion: \t";
        output << "1";
        //Casos especiales
        // primo = 2
        while(n % 2 == 0){
            pot++;
            n=n/2;
            reconstruido *= 2;
        }
        if(pot != 0){
            maxPot = pot;
            output << " * 2^" << pot;
            maxPrim = 2;
        }
        //primo = 3
        pot = 0;
        while(n % 3 == 0){
            pot++;
            n=n/3;
            reconstruido *= 3;
        }
        if(pot!= 0){
            output << " * 3^" << pot;
            if(pot >= maxPot){
                maxPot = pot;
                maxPrim = 3;
            }
        }
        //primo = 5
        pot = 0;
        while(n % 5 == 0){
            pot++;
            n=n/5;
            reconstruido *= 5;
        }
        if(pot!= 0){
            output << " * 5^" << pot;
            if(pot >= maxPot){
                maxPot = pot;
                maxPrim = 5;
            }
        }

        //arrancamos en 7 e iteramos por todos los numeros de la forma 6*k+1 o 6*k+5
        int cand = 7;
        int k = 1;
        pot = 0;
        bool sumocinco = true;
        while(cand <= raiz){

            //dividimos para obtener la potencia
            while(n % cand == 0){
                pot++;
                n = n / cand;
                reconstruido *= cand;
            }

            //actualizamos el maximo
            if (pot != 0){
                output << " * " << cand << "^" << pot;
                if (pot >= maxPot){
                    maxPot = pot;
                    maxPrim = cand;
                }
            }
            pot = 0;
            //actualizamos el limite hasta donde iterar
            raiz = sqrt((double)n)+1;
            //armamos el proximo candidato segun la formula
            if(sumocinco){
                cand = 6*k + 5;
                k++;
                sumocinco = false;
            }
            else{
                cand = 6*k+1;
                sumocinco = true;
            }
        }

        //si cand se paso es porq me quedo un n primo, solo podra ser el maximo si no hay otro con exponenete mayor q 1
        if(n > raiz){
            reconstruido *= n;
            output << " * " << n << "^1";

            if(maxPot <= 1){
                maxPrim = n;
                maxPot = 1;
            }
        }

        output << "\nReconstruido: \t" << reconstruido << endl;
        output << "Primo: \t\t" << maxPrim << endl;
        output << "Potencia: \t" << maxPot << endl;
        output << "\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n";
        cout << "Primo: \t\t" << maxPrim << endl;
        cout << "Potencia: \t" << maxPot << endl;
        cout << "\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n";
    }
    output.close();
}

void maxFactorPrim(unsigned long long n, unsigned& primo, unsigned& potencia){
    int pot = 0;
    int maxPot = 1;
    int maxPrim = 1;
    double raiz = sqrt((double)n);
    //Casos especiales
    // primo = 2
    while(n % 2 == 0){
        pot++;
        n=n/2;
    }
    if(pot != 0){
        maxPot = pot;
        maxPrim = 2;
    }

    //primo = 3
    pot = 0;
    while(n % 3 == 0){
        pot++;
        n=n/3;
    }
    if(pot >= maxPot && pot != 0){
        maxPot = pot;
        maxPrim = 3;
    }
    //primo = 5
    pot = 0;
    while(n % 5 == 0){
        pot++;
        n=n/5;
    }
    if(pot >= maxPot && pot!= 0){
        maxPot = pot;
        maxPrim = 5;
    }

    //arrancamos en 7 e iteramos por todos los numeros de la forma 6*k+1 o 6*k+5
    int cand = 7;
    int k = 1;
    pot = 0;
    bool sumocinco = true;
    while(cand <= raiz){

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
        raiz = sqrt((double)n)+1;
        //armamos el proximo candidato segun la formula
        if(sumocinco){
            cand = 6*k + 5;
            k++;
            sumocinco = false;
        }
        else{
            cand = 6*k+1;
            sumocinco = true;
        }
    }

    //si cand se paso es porq me quedo un n primo, solo podra ser el maximo si no hay otro con exponenete mayor q 1
    if(n > raiz && maxPot <= 1){
        maxPrim = n;
        maxPot = 1;
    }

    primo = maxPrim;
    potencia = maxPot;
}

 int main(int argc, char* argv[]){
     ifstream entrada;
     ofstream salida;

     entrada.open("Tp1Ej1.in", ios_base::in);
     salida.open("Tp1Ej1.out", ios_base::out);
     assert(entrada.is_open());
     int numero = 0;
     entrada >> numero;
     while(numero != 0){
         unsigned primo, pot;
         maxFactorPrim(numero, primo, pot);
         salida << numero << " " << primo << " " << pot << endl;
         entrada >> numero;
     }

     entrada.close();
     salida.close();
     system("PAUSE");
     return 0;
 }
