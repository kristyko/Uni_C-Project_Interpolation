//
//  DMatrix.h
//  Interpolation_TrotskoKristina
//
//  Created by mac on 5/25/19.
//  Copyright © 2019 mac. All rights reserved.
//

#ifndef DMatrix_h
#define DMatrix_h

#include <stdio.h>
#include "DVector.h"

typedef struct DMatrix
{
    DVector ** column;
    UTYPE size;
}DMatrix;

DMatrix* createDMatrix(UTYPE size);
DTYPE getDMatrix( DMatrix* matrix, UTYPE n, UTYPE m);
void setDMatrixEl( DMatrix* matrix, UTYPE n, UTYPE m, DTYPE x);
void setDMatrix( DMatrix* matrix);
void clearDMatrix( DMatrix* matrix);
void freeDMatrix( DMatrix** matrix);
DMatrix* cutMatrix( DMatrix* matrix, ITYPE i1, ITYPE i2);
DTYPE det( DMatrix* matrix);
void printDMatrix( DMatrix* matrix);

#endif /* DMatrix_h */
