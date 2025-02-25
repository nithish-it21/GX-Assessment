#ifndef File_c4
#define File_c4


void multiplication(int** mat1, int** mat2, int** res, int row1, int col1,
	       int row2,int col2){

	for(int i=0; i<row1; i++){
		for(int j=0; j<col2; j++){
			res[i][j] = 0;
			for(int k=0; k<col1; k++){
				res[i][j] += mat1[i][k]*mat2[k][j];
			}
		}
	}
}



#endif
