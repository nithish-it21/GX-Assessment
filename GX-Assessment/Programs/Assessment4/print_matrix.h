#ifndef File_c5
#define File_c5
#include<stdio.h>

void print_matrix(int** res,int row,int col){
	
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d ", res[i][j]);
        }
        printf("\n");
    }
	
}

#endif
