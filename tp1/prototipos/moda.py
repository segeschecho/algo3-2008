#PROCEDURE KESIMO3(VAR A:VECTOR;PRIM,ULT,K:CARDINAL):INTEGER;
#VAR I,D:CARDINAL; PM:INTEGER; (* PSEUDO_MEDIANA *)
#BEGIN
#IF PRIM<ULT THEN
#PM:=CASIMEDIANA(A,PRIM,ULT);
#PIVOTE2(A,PM,PRIM,ULT,I,D);
#IF (PRIM+K-1)<I THEN RETURN KESIMO3(A,PRIM,I-1,K) END;
#IF D<=(PRIM+K-1) THEN RETURN KESIMO3(A,D,ULT,K-D+PRIM) END;
#RETURN A[I]
#ELSE
#RETURN A[ULT]
#END
#END KESIMO3;

#ult es la ultima valida
def kesimo(a,prim,ult,k):
        if prim < ult:
            pm = casiMediana(a,prim,ult)
            i=0
            d=0
            (i,d)=pivote(a,pm,prim,ult,i,d)
            if prim+k < i:
                return kesimo(a,prim,i-1,k)
            if d <=prim+k:
                return kesimo(a,d,ult,k-d+prim)
            return a[i]
        else:
            return a[ult]
        


#PROCEDURE CasiMediana(VAR a:vector; prim,ult:CARDINAL):INTEGER;
#(* calcula una mediana aproximada del vector a[prim..ult] *)
#VAR n,i:CARDINAL; b:vector;
#BEGIN
#n:=ult-prim+1;
#IF n<=5 THEN
#RETURN Medianade5(a,prim,ult)
#END;
#n:=n DIV 5;
#FOR i:=1 TO n DO
#b[i]:=Medianade5(a,5*i-4+prim-1,5*i+prim-1)
#END;
#RETURN Kesimo3(b,1,n,(n+1)DIV 2)
#END CasiMediana

def casiMediana(a,prim,ult):
    n = ult - prim
    if n <= 5:
        return medianaDe5(a,prim,ult)
    n = n / 5
    b=[0]*n
    for i in range(n):
        b[i] = medianaDe5(a,5*i+prim,5*i+prim+4)
    return kesimo(b,0,n-1,(n+1)/2)

#PROCEDURE Medianade5(VAR a:vector; prim,ult:CARDINAL):INTEGER;
#(* calcula la mediana de un vector de hasta 5 elementos (es
#decir, ult<prim+5) *)
#VAR i,n:CARDINAL; b:vector; (* para no modificar el vector *)
#BEGIN
#n:=ult-prim+1; (* numero de elementos *)
#FOR i:=1 TO n DO
#b[i]:=a[prim+i-1]
#END;
#FOR i:=1 TO (n+1) DIV 2 DO
#Intercambia(b,i,PosMinimo(b,i,n))
#END;
#RETURN b[(n+1) DIV 2];
#END Medianade5;

def medianaDe5(a,prim,ult):
    n = ult - prim + 1
    b= [0] * n
    for i in range(n):
        b[i] = a[prim + i]
    for i in range((n+1)/2):
        aux = b[i]
        pos = posMinimo(b,i,n-1)
        b[i]=b[pos]
        b[pos]=aux
    return b[(n+1)/2]

def posMinimo(b,i,n):
    pos = i
    for j in range(i,n):
        if b[j] < b[pos]:
            pos = j
    return pos
            
            
#PROCEDURE Pivote2(VAR a:vector; p:INTEGER; prim,ult:CARDINAL;
#VAR k,l:CARDINAL);
#(* permuta los elementos de a[prim..ult] y devuelve dos
#posiciones k,l tales que prim-1<=k<l<=ult+1, a[i]<p si
#prim<=i<=k, a[i]=p si k<i<l, y a[i]>p si l<=i<=ult, donde p es
#el pivote y aparece como argumento *)
#VAR m:CARDINAL;
#BEGIN
#k:=prim; l:=ult+1;
#(* primero buscamos l *)
#REPEAT INC(k) UNTIL (a[k]>p) OR (k>=ult);
#REPEAT DEC(l) UNTIL (a[l]<=p);
#WHILE k<l DO
#Intercambia(a,k,l);
#REPEAT INC(k) UNTIL (a[k]>p);
#REPEAT DEC(l) UNTIL (a[l]<=p)
#END;
#Intercambia(a,prim,l);
#INC(l); (* ya tenemos l *)
#(* ahora buscamos el valor de k *)
#k:=prim-1;
#m:=l;
#REPEAT INC(k) UNTIL (a[k]=p) OR (k>=l);
#REPEAT DEC(m) UNTIL (a[m]<>p) OR (m<prim);
#WHILE k<m DO
#Intercambia(a,k,m);
#REPEAT INC(k) UNTIL (a[k]=p);
#REPEAT DEC(m) UNTIL (a[m]<>p);
#END;
#END Pivote2;

def pivote(a,p,prim,ult,k,l):
    k = prim+1
    l=ult
    while not(a[k]>p or k >=ult ):
        k=k+1
    while not(a[l] <= p):
        l=l-1
    aux=a[prim]
    a[prim] = a[l]
    a[l] = aux
    l=l+1
    k = prim
    m = l-1
    while not(a[k] == p or k >= 1):
        k=k+1
    while not(a[m] != p or m<prim):
        m=m-1
    while k< m:
        aux = a[k]
        a[k] = a[m]
        a[m] = aux
        k=k+1
        m=m-1
        while not(a[k] == p):
            k=k+1
        while not(a[m] != p):
            m=m-1
    return (k,l)
 
a=[9]*44+[999]*100+[7,6]+[4]*15+[999]*10000+[500]*40+[200]*30+[1,2]*2800
print kesimo(a,0,len(a)-1,len(a)/2)