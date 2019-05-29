//
//  DPoly.c
//  Interpolation_TrotskoKristina
//
//  Created by mac on 5/25/19.
//  Copyright © 2019 mac. All rights reserved.
//

#include "DPoly.h"

// выделение памяти под многочлен
DPoly* createDPoly(UTYPE size)
{
    DPoly *tmp = NULL;
    if (!(tmp = (DPoly*) malloc(sizeof(DPoly)))) {
        exit(OUT_OF_MEMORY_EXCEPTION);
    }
    if (!(tmp->coeff = (DTYPE*) malloc(size * sizeof(DTYPE)))) {
        exit(OUT_OF_MEMORY_EXCEPTION);
    }
    tmp->size = size;
    return tmp;
}

// взятие коэффициента многочлена
DTYPE getDPoly(DPoly* poly, UTYPE index)
{
    if (index < poly->size) { return poly->coeff[index]; }
    else { exit(INDEX_OUT_OF_BOUNDS_EXCEPTION); }
}

// задание коеффициента многочлена
void setDPolyEl(DPoly* poly, UTYPE index, DTYPE value)
{
    if (index < poly->size) { poly->coeff[index] = value; }
    else { exit(INDEX_OUT_OF_BOUNDS_EXCEPTION); }
}

// задание многочлена с консоли
void setDPoly(DPoly* poly)
{
    for (UTYPE i=0; i < poly->size; ++i)
    {
        DTYPE x;
        scanf("%lf", &x);
        setDPolyEl(poly, i, x);
    }
}

//Удаление элементов многочлена
void clearDPoly(DPoly* poly)
{
    free(poly->coeff);
    poly->coeff = NULL;
}

// удаление многочлена
void freeDPoly(DPoly **poly)
{
    clearDPoly(*poly);
    free(*poly);
    poly = NULL;
}

// изменение размера многочлена
void resizeDPoly(DPoly* poly, UTYPE newSize)
{
    if (!(poly->coeff = (DTYPE*) realloc(poly->coeff, newSize * sizeof(DTYPE)))) {
        exit(OUT_OF_MEMORY_EXCEPTION);
    }
    poly->size = newSize;
}

// вывод на экран
void printDPoly(DPoly* poly)
{
    UTYPE i;
    for (i = 0; i < poly->size - 1; i++) {
        printf("%fx^%lu + ", getDPoly(poly, i), poly->size - i - 1);
    }
    printf("%f\n", getDPoly(poly, i));
}

// значение многочлена в точке
DTYPE valuePolyEl(DPoly* poly, DTYPE x)
{
    DTYPE res = 0;
    for (int i=0; i < poly->size; ++i)
    {
        res = res * x + poly->coeff[i];
    }
    return res;
}

// значение многочлена в векторе (каждая координата подставляется отдельно)
DVector* valuePoly(DPoly* poly, DVector* x)
{
    DVector* y = createDVector(x->size);
    for (UTYPE i=0; i < x->size; ++i)
    {
        setDVectorEl(y, i, valuePolyEl(poly, x->data[i]));
    }
    return y;
}