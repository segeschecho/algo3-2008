#include "CmergeSort.h"

CMergeSort::CMergeSort(Cosa* cos, int cantEle, int* inds){
    opers = opers + 3;
	cosas = cos;
	cantElem=cantEle;
	indices = inds;
}

unsigned long long int
CMergeSort::sort() {
    opers = 0;
    mergeSort(0,cantElem-1);
    return opers;
}

void 
CMergeSort::mergeSort(int pri, int ult) {
    opers++;
    if(pri<ult) {
        opers = opers + 3;
        int pmedio=(pri + ult)/2;

        mergeSort(pri, pmedio);
        opers++;
        mergeSort(pmedio+1, ult);
        merge(pri,ult);
    }
}

void 
CMergeSort::merge(int pri, int ult) {
    opers = opers + 7;
    int i,j, cont=0;
    int tamano=ult-pri+1;
    int pmedio=(pri+ult)/2;

    opers = opers + tamano + tamano;
    Cosa *tmp=new Cosa[tamano];
    int * indicesAux = new int[tamano];
    opers = opers + 4;  
    for(i=pri;i<=pmedio;i++,cont++)
    {
        opers = opers + 5;
        tmp[cont]=cosas[i];
        indicesAux[cont] = indices[i];
    }

    opers = opers + 5;
    for(i=ult;i>=pmedio+1;i--,cont++)
    {
        opers = opers + 6;
        tmp[cont]=cosas[i];
    	indicesAux[cont] = indices[i];
    }

    opers = opers + 6;
    for(i=0,j=tamano-1,cont=pri;i<=j;cont++)    
    {
        opers++;
        if(tmp[i].peso<=tmp[j].peso)
        {
            opers = opers + 3;
            cosas[cont]=tmp[i];
            indices[cont] = indicesAux[i];
            i++;
        }
        else
        {
            opers = opers + 3;
            cosas[cont]=tmp[j];
            indices[cont] = indicesAux[j];
            j--;
        }
    }
    opers++;
    delete[] indicesAux;
    delete[] tmp;
    
}


