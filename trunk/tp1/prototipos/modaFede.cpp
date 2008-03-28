#include <iostream>
using namespace std;

int kesimo(int* a, int prim, int ult, int k);
/*
PROCEDURE PosMinimo(VAR a:vector;i,j:CARDINAL):CARDINAL;
(* devuelve la posicion del minimo elemento de a[i..j] *)
   VAR pmin,k:CARDINAL;
BEGIN
   pmin:=i;
   FOR k:=i+1 TO j DO
      IF a[k]<a[pmin] THEN
         pmin:=k
      END
   END;
   RETURN pmin;
END PosMinimo;
*/
int posMinimo(int*b,int i,int n){
    int pos = i;
    for(int j= i+1; j < n; j++){
        if(b[j] < b[pos])
            pos = j;
    }
    return pos;
}
/*
(* permuta los elementos de a[prim..ult] y devuelve dos
   posiciones k,l tales que prim-1<=k<l<=ult+1, a[i]<p si
   prim<=i<=k, a[i]=p si k<i<l, y a[i]>p si l<=i<=ult, donde p es
   el pivote y aparece como argumento *)
PROCEDURE Pivote2(VAR a:vector; p:INTEGER; prim,ult:CARDINAL;
                   VAR k,l:CARDINAL);

   VAR m:CARDINAL;
BEGIN
   k:=prim; l:=ult+1;
   (* primero buscamos l *)
   REPEAT INC(k) UNTIL (a[k]>p) OR (k>=ult);
   REPEAT DEC(l) UNTIL (a[l]<=p);
   WHILE k<l DO
      Intercambia(a,k,l);
      REPEAT INC(k) UNTIL (a[k]>p);
      REPEAT DEC(l) UNTIL (a[l]<=p)
   END;



   Intercambia(a,prim,l);
      INC(l); (* ya tenemos l *)
   (* ahora buscamos el valor de k *)
   k:=prim-1;
   m:=l;
   REPEAT INC(k) UNTIL (a[k]=p) OR (k>=l);
   REPEAT DEC(m) UNTIL (a[m]<>p) OR (m<prim);
   WHILE k<m DO
      Intercambia(a,k,m);medianaDe5(a,5*i+prim,5*i+prim+4);
      REPEAT INC(k) UNTIL (a[k]=p);
      REPEAT DEC(m) UNTIL (a[m]<>p);
   END;
END Pivote2;
*/
void pivote(int*a,int p,int prim,int ult,int& k,int& l){
    k = prim+1;
    l=ult;
    while(!(a[k]>p || k >=ult )){
        k=k+1;
    }
    while(!(a[l] <= p)){
        l=l-1;
    }
    int aux=a[prim];
    a[prim] = a[l];
    a[l] = aux;
    l=l+1;
    k = prim;
    int m = l-1;
    while (!(a[k] == p or k >= 1)){
        k=k+1;
    }
    while (!(a[m] != p or m<prim)){
        m=m-1;
    }
    while (k< m){
        aux = a[k];
        a[k] = a[m];
        a[m] = aux;
        k=k+1;
        m=m-1;
        while (!(a[k] == p)){
            k=k+1;
        }
        while (!(a[m] != p)){
            m=m-1;
        }
    }
}

/*
PROCEDURE Medianade5(VAR a:vector; prim,ult:CARDINAL):INTEGER;
(* calcula la mediana de un vector de hasta 5 elementos (es
   decir, ult<prim+5) *)
   VAR i,n:CARDINAL; b:vector; (* para no modificar el vector *)
BEGIN
   n:=ult-prim+1; (* numero de elementos *)
   FOR i:=1 TO n DO
      b[i]:=a[prim+i-1]
   END;
   FOR i:=1 TO (n+1) DIV 2 DO
      Intercambia(b,i,PosMinimo(b,i,n))
   END;
   RETURN b[(n+1) DIV 2];
END Medianade5;

*/
int medianaDe5(int* a,int prim,int ult){
    int n = ult - prim+1;
    int *b= new int[n];
    for(int i=0; i< n; i++){
        b[i] = a[prim + i];
    }
    for(int i= 0; i < (n+1)/2; i++){
        int aux = b[i];
        int pos = posMinimo(b,i,n-1);
        b[i]=b[pos];
        b[pos]=aux;
    }
    int x = b[(n+1)/2];
    delete b;
    return x;
}
/*
PROCEDURE CasiMediana(VAR a:vector; prim,ult:CARDINAL):INTEGER;
(* calcula una mediana aproximada del vector a[prim..ult] *)
   VAR n,i:CARDINAL; b:vector;
BEGIN
   n:=ult-prim+1;
   IF n<=5 THEN
      RETURN Medianade5(a,prim,ult)
   END;
   n:=n DIV 5;
   FOR i:=1 TO n DO
      b[i]:=Medianade5(a,5*i-4+prim-1,5*i+prim-1)
   END;
   RETURN Kesimo3(b,1,n,(n+1)DIV 2)
END CasiMediana;
*/
int casiMediana(int* a,int prim,int ult){
    int n = ult - prim;
    if(n <= 5)
        return medianaDe5(a,prim,ult);
    n = n / 5;
    int * b=new int[n];
    for(int i=0; i < n; i++){
        b[i] = medianaDe5(a,5*i+prim,5*i+prim+4);
    }
    int x = kesimo(b,0,n-1,(n+1)/2);
    delete b;
    return x;
}




/*
PROCEDURE Kesimo3(VAR a:vector;prim,ult,k:CARDINAL):INTEGER;
   VAR i,d:CARDINAL; pm:INTEGER; (* pseudo_mediana *)
BEGIN
   IF prim<ult THEN
      pm:=CasiMediana(a,prim,ult);
      Pivote2(a,pm,prim,ult,i,d);
      IF (prim+k-1)<i THEN RETURN Kesimo3(a,prim,i-1,k) END;
      IF d<=(prim+k-1) THEN RETURN Kesimo3(a,d,ult,k-d+prim) END;
      RETURN a[i]
   ELSE
      RETURNreturn a[ult]
   END
END Kesimo3;
*/

int kesimo(int*a,int prim,int ult,int k){
        if(prim < ult){
            int pm = casiMediana(a,prim,ult);
            int i=0;
            int d=0;
            pivote(a,pm,prim,ult,i,d);
            if(prim+k < i){
                return kesimo(a,prim,i-1,k);
            }
            if(d <=prim+k){
                return kesimo(a,d,ult,k-d+prim);
            }
            return a[i];
        }
        else
            return a[ult];
}

int main(){
	int* a =new int[10];
        a[0]=0;
	a[1]=1;
	a[2]=2;
	a[3]=0;
	for(int i = 4; i < 10; i++){
		a[i] = 4;
	}
	cout<<kesimo(a,0,9,5);
	//cout<<casiMediana(a,0,10);
	//cout<<medianaDe5(a,5,10);
	delete a;
	return 0;
}
