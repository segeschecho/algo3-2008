#ifndef _CmergeSort_H
#define _CmergeSort_H

#include <iostream>
#include "Cosa.h"
static unsigned long long int opers = 0LL;

class CMergeSort{
public:
    CMergeSort(Cosa* cos, int cantElem, int* inds);
private:
    Cosa* cosas;
    int * indices;
    int cantElem;
    void mergeSort(int desde, int hasta);
    void merge(int desde, int hasta);
};

#endif /*_CmergeSort_h*/

