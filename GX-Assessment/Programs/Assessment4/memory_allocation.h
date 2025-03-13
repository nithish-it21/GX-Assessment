#ifndef File_c1
#define File_c1

#include <stdlib.h> 
#include<stdio.h>

int** memory_allocation(int row, int col) {
    int** mat = (int **)malloc(sizeof(int *) * row); 
    if (mat == NULL) {

        printf("Memory allocation failed!\n");
        exit(1); 
    }

    for (int i = 0; i < row; i++) {
        mat[i] = (int *)malloc(sizeof(int) * col); 

        if (mat[i] == NULL) {

            printf("Memory allocation for row %d failed!\n", i);
            exit(1);
        }
    }
    
    return mat;
}

#endif

