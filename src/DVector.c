//
//  DVector.c
//  Interpolation_TrotskoKristina
//
//  Created by mac on 5/25/19.
//  Copyright © 2019 mac. All rights reserved.
//

#include "DVector.h"

// выделение памяти под вектор
DVector* createDVector(UTYPE size)
{
    DVector *tmp = NULL;
    if (!(tmp = (DVector*) malloc(sizeof(DVector)))) {
        exit(OUT_OF_MEMORY_EXCEPTION);
    }
    if (!(tmp->data = (DTYPE*) malloc(size * sizeof(DTYPE)))) {
        exit(OUT_OF_MEMORY_EXCEPTION);
    }
    tmp->size = size;
    return tmp;
}

// изменение размера вектора
void resizeDVector(DVector* vector, UTYPE newSize)
{
    if (!(vector->data = (DTYPE*) realloc(vector->data, newSize * sizeof(DTYPE)))) {
        exit(OUT_OF_MEMORY_EXCEPTION);
    }
    vector->size = newSize;
}

// взятие элемента вектора
DTYPE getDVectorEl(DVector* vector, UTYPE index)
{
    if (index < vector->size) { return vector->data[index]; }
    else { exit(INDEX_OUT_OF_BOUNDS_EXCEPTION); }
}

// задание элемента вектора
void setDVectorEl(DVector* vector, UTYPE index, DTYPE value)
{
    if (index < vector->size) { vector->data[index] = value; }
    else { exit(INDEX_OUT_OF_BOUNDS_EXCEPTION); }
}

// задание полностью вектора с консоли
void setDVector(DVector* vector)
{
    for ( size_t i=0; i < vector->size; ++i)
    {
        DTYPE el;
        scanf("%lf", &el);
        setDVectorEl(vector, i, el);
    }
}

//Удаление элементов вектора
void clearDVector(DVector* vector)
{
    free(vector->data);
    vector->data = NULL;
}

// удаление самого вектора
void freeDVector(DVector **vector)
{
    clearDVector(*vector);
    free(*vector);
    vector = NULL;
}

// вывод вектор на экран
void printDVector(DVector* vector)
{
    UTYPE i;
    printf("Vector:\n");
    for (i = 0; i < vector->size; i++) {
        printf("%f ", getDVectorEl(vector, i));
    }
    printf("\n");
}

void readVectorFromFile( DVector* vector, CHARACTER filename[30] )
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
            setDVectorEl(vector, i, N);
            input = end;
            i++;
        }
        vector->size = i;
    }
}

void putVectorToFile( DVector* vector, CHARACTER filename[30] )
{
    FILE* f = fopen(filename, "w");
    if ( f == NULL )
    {
        printf("Couldn't open file\n");
        exit(1);
    }
    else
    {
        for ( UTYPE i=0; i < vector->size; ++i )
        {
            fprintf(f, "%.1f ", vector->data[i]);
        }
        fprintf(f, "\n");
    }
}

// скалярное произведение двух векторов
DVector* dot(DVector* left, DVector* right)
{
    if ( ! (left->size == right->size) )
    {
        exit(INCORRECT_DATA_SIZES_EXCEPTION);
    }
    DVector* result = createDVector(left->size);
    
    for ( UTYPE i=0; i < left->size; ++i)
    {
        setDVectorEl(result, i, left->data[i] * right->data[i]);
    }
    return result;
}

// скалярное поднесение вектора в степень
DVector* dot_pow(DVector* _this, UTYPE power)
{
    DVector* result = createDVector(_this->size);
    for ( size_t i=0; i < _this->size; ++i)
    {
        setDVectorEl(result, i, pow(_this->data[i], power));
    }
    return result;
}

// сумма координат вектора
DTYPE get_sum(DVector* _this)
{
    DTYPE sum = 0;
    
    for ( size_t i=0; i < _this->size; ++i)
    {
        sum += _this->data[i];
    }
    return sum;
}

// сумма двух векторов
DVector* add(DVector* left, DVector* right)
{
    if ( ! (left->size == right->size) )
    {
        exit(INCORRECT_DATA_SIZES_EXCEPTION);
    }
    DVector* result = createDVector(left->size);
    
    for ( size_t i=0; i < left->size; ++i)
    {
        setDVectorEl(result, i, left->data[i] + right->data[i]);
    }
    return result;
}

// умножение вектора на скаляр
DVector* mul(DVector* _this, DTYPE val)
{
    DVector* result = createDVector(_this->size);
    for ( size_t i=0; i < _this->size; ++i)
    {
        setDVectorEl(result, i, _this->data[i] * val);
    }
    return result;
}