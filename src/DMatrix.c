//
//  DMatrix.c
//  Interpolation_Trotsko
//
//  Created by mac on 5/25/19.
//  Copyright © 2019 mac. All rights reserved.
//

#include "DMatrix.h"

// виделение памяти под матрицу
DMatrix* createDMatrix(UTYPE size)
{
    DMatrix *matrix = (DMatrix*) malloc(sizeof(DMatrix));
    if (matrix == NULL)
    {
        exit(OUT_OF_MEMORY_EXCEPTION);
    }
    
    matrix->column = (DVector**) malloc(size * sizeof(DVector*));
    
    for (UTYPE i = 0; i<size; ++i) {
        matrix->column[i] = createDVector(size);
        
    }
    matrix->size = size;
    return matrix;
}

// взятие элемента матрицы
double getDMatrix(DMatrix* matrix, UTYPE n, UTYPE m)
{
    if ( n < matrix->size ) { return getDVectorEl(matrix->column[n], m); }
    else { exit(INDEX_OUT_OF_BOUNDS_EXCEPTION); }
}

// задание элемента матрицы
void setDMatrixEl(DMatrix* matrix, UTYPE n, UTYPE m, DTYPE x)
{
    if (n < matrix->size ) { setDVectorEl(matrix->column[n], m, x); }
    else { exit(INDEX_OUT_OF_BOUNDS_EXCEPTION); }
}

// задание матрицы через консоль
void setDMatrix(DMatrix* matrix)
{
    for ( UTYPE i=0; i < matrix->size; ++i )
    {
        setDVector(matrix->column[i]);
    }
}

//Удаление элементов матрицы
void clearDMatrix(DMatrix* matrix)
{
    for ( UTYPE i=0; i < matrix->size; ++i )
    {
        free(matrix->column[i]);
    }
    matrix->column = NULL;
}

// удвалене матрицы
void freeDMatrix(DMatrix** matrix)
{
    clearDMatrix( *matrix );
    free( *matrix );
    matrix = NULL;
}

// дополнение матрицы
DMatrix* cutMatrix(DMatrix* matrix, ITYPE i1, ITYPE i2)
{
    DMatrix* minor_i = createDMatrix(matrix->size - 1);
    ITYPE x = 0;
    for ( UTYPE j=0; j < matrix->size; ++j )
    {
        if ( j != i1 )
        {
            ITYPE y = 0;
            for (UTYPE k=0; k < matrix->size; ++k )
            {
                if ( k != i2 ) { setDMatrixEl(minor_i, x, y, matrix->column[j]->data[k]); y += 1;}
            }
            x += 1;
        }
    }
    return minor_i;
}

// определитель матрицы максимального размера 4
DTYPE det(DMatrix* matrix)
{
    if ( matrix->size == 1 )
    {
        return *matrix->column[0]->data;
    }
    else if (matrix->size == 2)
    {
        return matrix->column[0]->data[0] * matrix->column[1]->data[1] -
        matrix->column[0]->data[1] * matrix->column[1]->data[0];
    }
    else if ( matrix->size == 3 )
    {
        return matrix->column[0]->data[0] * matrix->column[1]->data[1] * matrix->column[2]->data[2] +
        matrix->column[0]->data[2] * matrix->column[1]->data[0] * matrix->column[2]->data[1] +
        matrix->column[0]->data[1] * matrix->column[1]->data[2] * matrix->column[2]->data[0] -
        matrix->column[2]->data[0] * matrix->column[1]->data[1] * matrix->column[0]->data[2] -
        matrix->column[2]->data[2] * matrix->column[1]->data[0] * matrix->column[0]->data[1] -
        matrix->column[2]->data[1] * matrix->column[1]->data[2] * matrix->column[0]->data[0];
    }
    else if ( matrix->size == 4)
    {
        DTYPE result = 0;
        for ( int i=0; i < 4; ++i)
        {
            result += pow(-1, i) * matrix->column[0]->data[i] * det(cutMatrix(matrix, 0, i));
        }
        return result;
    }
    else { exit(INCORRECT_DATA_SIZES_EXCEPTION); }
}

// вывод матрицы на экран
void printDMatrix(DMatrix* matrix)
{
    UTYPE i;
    printf("Matrix:\n");
    for (i = 0; i < matrix->size; i++)
    {
        printDVector(matrix->column[i]);
        printf("\n");
    }
}