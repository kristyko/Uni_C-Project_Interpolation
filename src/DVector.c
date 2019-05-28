//
//  DVector.c
//  Interpolation_TrotskoKristina
//
//  Created by mac on 5/25/19.
//  Copyright © 2019 mac. All rights reserved.
//

#include "DVector.h"

// выделение памяти под вектор
DVector* createDVector(size_t size)
{
    DVector *tmp = NULL;
    if (!(tmp = (DVector*) malloc(sizeof(DVector)))) {
        exit(OUT_OF_MEMORY_EXCEPTION);
    }
    if (!(tmp->data = (double*) malloc(size * sizeof(double)))) {
        exit(OUT_OF_MEMORY_EXCEPTION);
    }
    tmp->size = size;
    return tmp;
}

// взятие элемента вектора
double getDVectorEl(DVector* vector, size_t index)
{
    if (index < vector->size) { return vector->data[index]; }
    else { exit(INDEX_OUT_OF_BOUNDS_EXCEPTION); }
}

// задание элемента вектора
void setDVectorEl(DVector* vector, size_t index, double value)
{
    if (index < vector->size) { vector->data[index] = value; }
    else { exit(INDEX_OUT_OF_BOUNDS_EXCEPTION); }
}

// задание полностью вектора с консоли
void setDVector(DVector* vector)
{
    for ( size_t i=0; i < vector->size; ++i)
    {
        double el;
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

// изменение размера вектора
void resizeDVector(DVector* vector, size_t newSize)
{
    if (!(vector->data = (double*) realloc(vector->data, newSize * sizeof(double)))) {
        exit(OUT_OF_MEMORY_EXCEPTION);
    }
    vector->size = newSize;
}

// вывод вектор на экран
void printDVector(DVector* vector)
{
    size_t i;
    printf("Vector:\n");
    for (i = 0; i < vector->size; i++) {
        printf("%f ", getDVectorEl(vector, i));
    }
    printf("\n");
}

// скалярное произведение двух векторов
DVector* dot(DVector* left, DVector* right)
{
    if ( ! (left->size == right->size) )
    {
        exit(INCORRECT_DATA_SIZES_EXCEPTION);
    }
    DVector* result = createDVector(left->size);
    
    for ( size_t i=0; i < left->size; ++i)
    {
        setDVectorEl(result, i, left->data[i] * right->data[i]);
    }
    return result;
}

// скалярное поднесение вектора в степень
DVector* dot_pow(DVector* _this, size_t power)
{
    DVector* result = createDVector(_this->size);
    
    for ( size_t i=0; i < _this->size; ++i)
    {
        setDVectorEl(result, i, pow(_this->data[i], power));
    }
    return result;
}

// сумма координат вектора
double get_sum(DVector* _this)
{
    double sum = 0;
    
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
DVector* mul(DVector* _this, double val)
{
    DVector* result = createDVector(_this->size);
    for ( size_t i=0; i < _this->size; ++i)
    {
        setDVectorEl(result, i, _this->data[i] * val);
    }
    return result;
}