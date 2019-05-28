//
//  main.c
//  Interpolation_TrotskoKristina
//
//  Created by mac on 5/28/19.
//  Copyright © 2019 mac. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "headers//common.h"
#include "headers//Input_Data.h"

int main(int argc, const char * argv[])
{
    FILE* f = fopen("Input.txt", "r");
    if ( f == NULL )
    {
        printf("Couldn't open file\n");
        exit(1);
    }
    else
    {
        printf("open\n");
        //        Input_Data* initial_data = createInputData(MIN_LEN);
        //        Input_Data* unknown_data = createInputData(MIN_LEN);
        //        char * input = (char*) malloc(sizeof(char) * 150 * 3 + 1);
        //        fgets(input, sizeof(char) * 150 * 3 + 1, f);
        //        ITYPE i = 0;
        //        while (input[i] != '\n') {
        //
        //            ++i;
        //        }
        
    }
    return 0;
}