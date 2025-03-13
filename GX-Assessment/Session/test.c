#include <stdio.h>
#include <stdlib.h>


/*
void swap(int* a, int * b){
	int temp = *a;
	*a = *b;
	*b = temp;
}



int partition(int* arr, int low, int high){
	int pivot_element = arr[high];
	int i = low;
	int j = high;

	while(i<j){
		
		while(arr[i]<pivot_element && i<high){
			i++;
		}

		while(arr[j]>=pivot_element && j>=low){
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

*/

/*
void merge(int* arr, int left, int mid , int right){
	
	int i=0, j=0, k=left;
	int n1 = mid - left + 1;
	int n2 = right - mid;
	int l_arr[n1], r_arr[n2];

	for(int idx = 0; idx<n1; idx++){
		l_arr[idx] = arr[left + idx];
	}

	for(int idx = 0; idx<n2; idx++){
		r_arr[idx] = arr[mid + 1 + idx];
	}

	while(i<n1 && j<n2){
		if(l_arr[i]<=r_arr[j]){
			arr[k++] = l_arr[i++];
		}
		else{
			arr[k++] = r_arr[j++];
		}
	}

	while(i<n1){
		arr[k++] = l_arr[i++];
	}

	while(j<n2){
		arr[k++] = r_arr[j++];
	}

}


void merge_sort(int* arr, int left, int right){
	if(left<right){
		
		int mid = left + (right-left) / 2;

		merge_sort(arr,left,mid);
		merge_sort(arr,mid+1,right);


		merge(arr, left, mid, right);
	}
}

*/

int compare(const void* p1, const void* p2){

	return (*(int*)p1 - *(int*)p2);
	/* if(*(const int*)p1 < *(const int*)p2){
		return *(const int*)p1;
	 }
	 return *(const int*)p2;*/
}

int main() {
    	int *arr;
    	int size;
    	int element;

again:
    	printf("Enter the size of an array: ");
    	if (scanf("%d", &size) != 1) {
       		printf("Invalid entry, Enter only Integer\n");
        	while (getchar() != '\n');
        	printf("\n");
        	goto again;
    	}

    	arr = (int*)malloc(sizeof(int) * size);
    	if (arr == NULL) {
        	printf("Memory Allocation Failed\n");
        	return 1;
    	}

    	printf("\n");
    	printf("Enter the Elements for the array\n");
    	for (int i = 0; i < size; i++) {
        	printf("Enter the %d Element: ", i + 1);
        	if (scanf("%d", &element) != 1) {
            		printf("Invalid entry, Enter only Integer.\n");
            		while (getchar() != '\n');
            		printf("\n");
            		i--;
            		continue;
        	}
        	arr[i] = element;
    	}

	//  quick_sort(arr, 0, size - 1);	
	//  merge_sort(arr,0,size-1);
	qsort(arr, size, sizeof(arr[0]), compare);

    	printf("\nResultant Array\n");
    	for (int i = 0; i < size; i++) {
        	printf("%d ", arr[i]);
    	}
    	printf("\n");

    	//free(arr);
    	return 0;
}
