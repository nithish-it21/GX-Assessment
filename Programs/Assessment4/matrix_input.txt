#ifndef File_c2
#define File_c2
#include<stdio.h>

void input(int** mat, int row, int col, int idx){
	for(int i=0; i<row; i++){
		for(int j=0 ; j<col; j++){
			printf("Enter value for Matrix%d [%d][%d]: ",idx,i,j);
			scanf("%d",&mat[i][j]);
			printf("\n");
		}
	}

}







#endif
