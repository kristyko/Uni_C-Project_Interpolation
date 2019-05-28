//
//  Input_Data.c
//  Interpolation_Trotsko
//
//  Created by mac on 5/25/19.
//  Copyright © 2019 mac. All rights reserved.
//

#include "Input_Data.h"

// выделение памяти под входные данные
Input_Data* createInputData( UTYPE size )
{
    Input_Data* men = (Input_Data*) malloc(sizeof(Input_Data));
    if ( men == NULL )
    {
        exit(OUT_OF_MEMORY_EXCEPTION);
    }
    
    men->x = createDVector(size);
    men->y = createDVector(size);
    return men;
}

// задать входные данные с консоли
void setInputData( Input_Data* men )
{
    for ( UTYPE i=0; i < men->x->size; ++i )
    {
        setDVector( men->x);
    }
    for ( UTYPE i=0; i < men->y->size; ++i)
    {
        setDVector(men->y);
    }
}

//void setInputDataFromFile_x(char* filename[20])
//{
//
//}


// вывод на экран
void printInputData( Input_Data* men )
{
    printDVector(men->x);
    printDVector(men->y);
}

// вспомогательнач функция для алгоритма Крамера
DMatrix* replaceCol(DMatrix* A, DVector* b, UTYPE col)
{
    DMatrix* result = createDMatrix(A->size);
    for ( UTYPE i=0; i < A->size; ++i)
    {
        if ( i != col )
        {
            result->column[i] = A->column[i];
        }
        else
        {
            result->column[i] = b;
        }
    }
    return result;
}

// решение систумы уравнениу методом Крамера
// нужна для нахождения коэффициентов итерполяционного многочлена
DPoly* Kramer( DMatrix* A, DVector* b)
{
    DPoly* result = createDPoly(b->size);
    DTYPE det_A = det(A);
    for ( UTYPE i=0; i < A->size; ++i)
    {
        setDPolyEl(result, i, det(replaceCol(A, b, i)) / det_A);
    }
    
    return result;
}

// нахождение интерполяционного многочлена
DPoly* Interpolate(Input_Data* men, UTYPE deg)
{
    DMatrix* A = createDMatrix( deg + 1 );
    for (UTYPE i=0; i < deg + 1; i++)
    {
        for ( UTYPE j=0; j < deg + 1; j++)
        {
            setDMatrixEl(A, i, j, get_sum( dot_pow( men->x, 2 * deg - i - j)));
        }
    }
    DVector* b = createDVector( deg + 1);
    for ( UTYPE i=0; i < deg + 1; i++)
    {
        setDVectorEl(b, i, get_sum( dot(men->y, dot_pow( men->x, deg - i))));
    }
    return Kramer(A, b);
}