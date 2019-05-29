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

void readDataFromFile( Input_Data* men, char filename[30] )
{
    FILE* f = fopen(filename, "r");
    if ( f == NULL )
    {
        printf("Couldn't open file\n");
        exit(1);
    }
    else
    {
        CHARACTER* input = (CHARACTER*) malloc(sizeof(CHARACTER) * 150 * 3 + 1);
        fgets(input, sizeof(CHARACTER) * 150 * 3 + 1, f);
        CHARACTER* end;
        DTYPE N;
        ITYPE i = 0;
        // считка вектора men->y
        while ( *input != '\n' )
        {
            N = strtof(input, &end);
            setDVectorEl(men->x, i, N);
            input = end;
            i++;
        }
        men->x->size = i;
        
        // считка вектора men->y
        fgets(input, sizeof(CHARACTER) * 150 * 3 + 1, f);
        i = 0;
        while ( *input != '\n' )
        {
            N = strtof(input, &end);
            setDVectorEl(men->y, i, N);
            input = end;
            i++;
        }
        men->y->size = i;
    }
}

void putDataToFile( Input_Data* men, CHARACTER filename[30] )
{
    FILE* f = fopen(filename, "w");
    if ( f == NULL )
    {
        printf("Couldn't open file\n");
        exit(1);
    }
    else
    {
        for ( UTYPE i=0; i < men->x->size; ++i )
        {
            fprintf(f, "%.1f ", men->x->data[i]);
        }
        fprintf(f, "\n");
        for ( UTYPE i=0; i < men->x->size; ++i )
        {
            fprintf(f, "%.1f ", men->y->data[i]);
        }
    }
}

// вывод на экран
void printInputData( Input_Data* men )
{
    printDVector(men->x);
    printDVector(men->y);
}

//Удаление элементов вектора
void clearInput_Data(Input_Data* data)
{
    freeDVector(&data->x);
    freeDVector(&data->y);
    data->x = NULL;
    data->y = NULL;
}

// удаление самого вектора
void deleteInput_Data(Input_Data **data)
{
    clearInput_Data(*data);
    free(*data);
    data = NULL;
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

// решение системы уравнений методом Крамера
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