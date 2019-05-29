//
//  DPoly.h
//  Interpolation_TrotskoKristina
//
//  Created by mac on 5/25/19.
//  Copyright © 2019 mac. All rights reserved.
//

#ifndef DPoly_h
#define DPoly_h

#include <stdio.h>
#include "DVector.h"

typedef struct DPoly
{
    DTYPE *coeff;
    UTYPE size;
}DPoly;

DPoly* createDPoly(UTYPE size);
DTYPE getDPoly( DPoly* poly, UTYPE index);
void setDPolyEl( DPoly* poly, UTYPE index, DTYPE value);
void setDPoly( DPoly* poly);
void clearDPoly( DPoly* poly);
void freeDPoly( DPoly **poly);
void resizeDPoly( DPoly* poly, UTYPE newSize);
void printDPoly( DPoly* poly);
DTYPE valuePolyEl( DPoly* poly, DTYPE x);
DVector* valuePoly( DPoly* poly, DVector* x);

#endif /* DPoly_h */
