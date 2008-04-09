#include "CmergeSort.h"

CMergeSort::CMergeSort(Cosa* cos, int cantEle, int* inds){
    opers = 0L;
    opers = opers + 2;
	cosas = cos;
	cantElem = cantEle;
	opers = opers + 3;
    for(int i = 0; i < cantEle; i++){
        opers = opers + 3;
        inds[i] = i;
    }
    opers++;
    indices = inds;
    mergeSort(0,cantElem-1);
}

void CMergeSort::mergeSort(int pri, int ult) {
    opers++;
    if(pri < ult) {
        opers = opers + 3;
        int pmedio = (pri + ult)/2;

        mergeSort(pri, pmedio);
        opers++;
        mergeSort(pmedio+1, ult);
        merge(pri,ult);
    }
}

void CMergeSort::merge(int pri, int ult) {
    opers = opers + 7;
    int i,j, cont = 0;
    int tamano = ult - pri + 1;
    int pmedio = (pri + ult)/2;

    opers = opers + tamano;
    Cosa *tmp=new Cosa[tamano];
    int * indicesAux = new int[tamano];

    opers = opers + 3;
    for(i = pri; i <= pmedio; i++)
    {
        opers = opers + 4;
        tmp[cont] = cosas[i];
        indicesAux[cont] = indices[i];
        cont++;
    }

    for(i = ult; i > pmedio; i--)
    {
        opers = opers + 4;
        tmp[cont] = cosas[i];
    	indicesAux[cont] = indices[i];
        cont++;
    }

    opers = opers + 5;
    cont = pri;
    for(i = 0, j = tamano - 1; i <= j;)
    {
        opers++;
        if(tmp[i].peso <= tmp[j].peso)
        {
            opers = opers + 2;
            cosas[cont]=tmp[i];
            indices[cont] = indicesAux[i];
            i++;
        }
        else
        {
            opers = opers + 2;
            cosas[cont] = tmp[j];
            indices[cont] = indicesAux[j];
            j--;
        }
        opers = opers + 2;
        cont++;
    }
    opers = opers + 2;
    delete[] indicesAux;
    delete[] tmp;
}


