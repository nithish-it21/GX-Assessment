#include<stdio.h>
#include<stdlib.h>

void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}


int partition(int* arr, int low, int high){

	int pivot_element = arr[high];
	int i = low;
	int j = high;

	while(i<j){
		
		while(arr[i]<=pivot_element && i<high){
			i++;
		}

		while(arr[j]>pivot_element && j>=low){
			j--;
	
		}
		
		if(i<j){
			swap(&arr[i],&arr[j]);
		}
	}
	swap(&arr[high],&arr[i]);
	return i;
}

void quick_sort(int* arr, int low, int high){
	if(low<high){

		int pi = partition(arr,low,high);

		quick_sort(arr,low,pi-1);
		quick_sort(arr,pi+1,high);
	}
}



int main(){
	int *arr;
	int size;
	int element;
again:
	printf("Enter the size of an array: ");
	if(scanf("%d",&size)!=1){
		printf("Invalid entry, Enter only Integer\n");
		while(getchar()!='\n');
		printf("\n");
		goto again;
	}

	arr = (int*)malloc(sizeof(int) * size);
	if(arr==NULL){
		printf("Memory Allocation Failed\n");
		return 1;
	}
	printf("\n");
	printf("Enter the Elements for the array\n");
	for(int i=0; i<size; i++){
		printf("Enter the %d Element: ",i+1);
		if(scanf("%d",&element)!=1){
			printf("Invalid entry, Enter only Integer.\n");
			while(getchar() != '\n');\
			printf("\n");
			i--;
			continue;
		}
		arr[i] = element;
	}
	
	quick_sort(arr,0,size-1);	

	printf("\nResultant Array\n");
	for(int i=0; i<size; i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}

