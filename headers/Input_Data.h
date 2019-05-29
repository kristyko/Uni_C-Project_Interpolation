//
//  Input_Data.h
//  Interpolation_TrotskoKristina
//
//  Created by mac on 5/25/19.
//  Copyright © 2019 mac. All rights reserved.
//

#ifndef Input_Data_h
#define Input_Data_h

#include <stdio.h>
#include "DVector.h"
#include "DPoly.h"
#include "DMatrix.h"

typedef struct Input_Data
{
    DVector* x;
    DVector* y;
}Input_Data;

Input_Data* createInputData( UTYPE size );
void clearInput_Data( Input_Data* data);
void deleteInput_Data( Input_Data **data);
void setInputData( Input_Data* men );
void printInputData( Input_Data* men );
void readDataFromFile( Input_Data* men, CHARACTER filename[30] );
void putDataToFile( Input_Data* men, CHARACTER filename[30] );
DMatrix* replaceCol( DMatrix* A, DVector* b, UTYPE col);
DPoly* Kramer( DMatrix* A, DVector* b);
DPoly* Interpolate( Input_Data* men, UTYPE deg);

#endif /* Input_Data_h */
