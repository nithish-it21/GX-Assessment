#ifndef File_c3
#define File_c3

#include<stdlib.h>

void free_memory(int** store, int size){

	for(int i=0; i<size; i++){
		free(store[i]);
	}
	free(store);
}




#endif
