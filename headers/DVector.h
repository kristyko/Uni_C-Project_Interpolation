//
//  DVector.h
//  Interpolation_TrotskoKristina
//
//  Created by mac on 5/25/19.
//  Copyright © 2019 mac. All rights reserved.
//

#ifndef DVector_h
#define DVector_h

#include "common.h"

typedef struct DVector
{
    double *data;
    size_t size;
} DVector;

DVector* createDVector(UTYPE size);
double getDVectorEl(DVector* vector, UTYPE index);
void setDVectorEl(DVector* vector, UTYPE index, DTYPE value);
void setDVector(DVector* vector);
void clearDVector( DVector* vector);
void freeDVector( DVector **vector);
void resizeDVector( DVector* vector, UTYPE newSize);
void printDVector( DVector* vector);
void readVectorFromFile( DVector* vector, CHARACTER filename[30] );
void putVectorToFile( DVector* vector, CHARACTER filename[30] );

DVector* dot( DVector* left, DVector* right);
DVector* dot_pow( DVector* _this, UTYPE power);
DTYPE get_sum( DVector* _this);
DVector* add( DVector* left, DVector* right);
DVector* mul( DVector* _this, DTYPE val);

#endif /* DVector_h */
