#include<stdio.h>
#include<stdlib.h>


void merge(int* arr, int left, int mid, int right){
	
	int i = 0, j = 0;
	int n1 = mid - left + 1;
        int n2 = right - mid;
	int l_arr[n1];
	int r_arr[n2];
	int k = left;

	for(int idx = 0; idx < n1; idx++){
		l_arr[idx] = arr[left+idx];
	}

	for(int idx = 0; idx < n2; idx++){
		r_arr[idx] = arr[mid+1+idx];
	}	
	
	while(i<n1 && j<n2){
		if(l_arr[i] <= r_arr[j]){
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

void mergersort(int *arr, int left, int right){
	if(left < right){
		
		int mid = left + (right - left) / 2;

		mergersort(arr,left,mid);
		mergersort(arr,mid+1,right);


		merge(arr,left,mid,right);
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
	
	mergersort(arr, 0, size-1);

	printf("\nResultant Array\n");
	for(int i=0; i<size; i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}	
