#include "CmergeSort.h"

CMergeSort::CMergeSort(Cosa* cos, int cantEle, int* inds){
    opers = opers + 3;
	cosas = cos;
	cantElem = cantEle;
    for(int i = 0; i < cantEle; i++){
        inds[i] = i;
    }
    indices = inds;
    mergeSort(0,cantElem-1);
}

void CMergeSort::mergeSort(int pri, int ult) {
    if(pri < ult) {
        int pmedio = (pri + ult)/2;

        mergeSort(pri, pmedio);
        mergeSort(pmedio+1, ult);
        merge(pri,ult);
    }
}

void CMergeSort::merge(int pri, int ult) {
    int i,j, cont = 0;
    int tamano = ult - pri + 1;
    int pmedio = (pri + ult)/2;

    Cosa *tmp=new Cosa[tamano];
    int * indicesAux = new int[tamano];
    for(i = pri; i <= pmedio; i++)
    {
        tmp[cont] = cosas[i];
        indicesAux[cont] = indices[i];
        cont++;
    }

    for(i = ult; i > pmedio; i--)
    {
        tmp[cont] = cosas[i];
    	indicesAux[cont] = indices[i];
        cont++;
    }

    cont = pri;
    for(i = 0, j = tamano - 1; i <= j;)
    {
        if(tmp[i].peso <= tmp[j].peso)
        {
            cosas[cont]=tmp[i];
            indices[cont] = indicesAux[i];
            i++;
        }
        else
        {
            cosas[cont] = tmp[j];
            indices[cont] = indicesAux[j];
            j--;
        }
        cont++;
    }
    delete[] indicesAux;
    delete[] tmp;
}


