//
//  main.c
//  Interpolation_TrotskoKristina
//
//  Created by mac on 5/25/19.
//  Copyright © 2019 mac. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "headers//common.h"
#include "headers//Input_Data.h"

int main(int argc, const char * argv[])
{
    CHARACTER mode;
    printf("Please, choose how you would like to read data\n\
    f - from file / c - from console:\n");
    scanf("%c", &mode);
    switch ( mode )
    {
        case 'f':
        {
            Input_Data* initial_data = createInputData(MIN_LEN);
            CHARACTER filename[30];
            printf("Please, give the name of the file you want to read from:\n");  // "Input.txt"
            scanf("%s", filename);
            readDataFromFile(initial_data, filename);
            DPoly* ipoly1 = Interpolate(initial_data, 1);
            DPoly* ipoly3 = Interpolate( initial_data, 3);
            printDPoly(ipoly1);
            printDPoly(ipoly3);
            
            
            DVector* x = createDVector(MIN_LEN);
            printf("Please, give the name of the file you want to read new data from:\n");
            scanf("%s", filename);   // "Test_data.txt"
            
            readVectorFromFile(x, filename);
            DVector* y = valuePoly(ipoly1, x);
            
            printf("Please, give the name of the file you want to write new data to:\n");
            scanf("%s", filename);   // "result.txt"
            putVectorToFile(y, filename);
            
            deleteInput_Data(&initial_data);
            freeDVector(&x);
            freeDPoly(&ipoly1);
            freeDPoly(&ipoly3);
            freeDVector(&y);
            break;
        }
        case 'c':
        {
            // достаточно неудобно считывать данные с консоли поэтому эту часть я пропустила
            // но по сути тут все то же самое 
            break;
        }
        default:
        {
            printf("Ok, exiting :)\n");
            return 0;
        }
        
    }
    return 0;
}