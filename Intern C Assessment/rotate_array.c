#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define max_limit 1000

void main(){
	int len;
	printf("Enter the Array Size: ");
	if(scanf("%d",&len)!=1){
		printf("Invalid entry, Enter Only Integer\n");
	        while(getchar()!='\n');
		return;	
	}
	int* arr = (int*)malloc(len * sizeof(int));
	
	for(int i=0; i<len; i++){
		printf("Enter the %d Element: ", i+1);
		scanf("%d",&arr[i]);
	}

	getchar();

	int k = 2;
	int* temp = (int*)malloc(len * sizeof(int));

	for(int i=k; i<len; i++){
		temp[i-k] = arr[i];
	}

	for(int i=0; i<k; i++){
		temp[i + (len-k)] = arr[i];
	}
		
	
	printf("\n");

	int largest_num = -1;
	printf("Rotated Array: ");
	for(int i=0; i<len; i++){
		printf("%d ",temp[i]);
		if(largest_num<temp[i]){
			largest_num = temp[i];
		}
	}
	printf("\n");
	//printf("largest number: %d",largest_num);
	int found = 0;
	int sum = -1;
	for(int i=0; i<len; i++){
		for(int j=0; j<len; j++){
			if(i!=j && temp[i]!=largest_num && temp[j]!=largest_num){
				int curr_sum = temp[i] + temp[j];
				if(curr_sum>sum){
					sum = curr_sum;	
				}
			}	
		}
	}

	for(int i=0; i<len; i++){
		if(temp[i] == largest_num){
			found++;
		}
	}

	printf("\nSecond Largest Sum: %d\n",sum);
	printf("\n");
	int res_size = 0;
	if(sum>largest_num){

		printf("Performing Operation 1\n");
		for(int i=0; i<len; i++){
			if(temp[i]==largest_num){
				temp[i] = sum;	
			}
			printf("%d ",temp[i]);
		}
	}
	else if(found>=1){
		printf("Performing Operation 2\n");
		char* buff = (char*)malloc(max_limit);
		snprintf(buff,max_limit,"%d",sum);
		int int_arr[strlen(buff)];
		for(int i=0; i<strlen(buff); i++){
			int_arr[i] = buff[i] - '0';	
		}

		int n_len = len + (found * strlen(buff)) - found;
		int res[n_len];
		int idx = 0;
		for(int i=0; i<len; i++){
			if(temp[i]==largest_num){
				for(int i=0; i<strlen(buff); i++){
					res[idx++] = int_arr[i];
				}
				continue;
			}
			res[idx++] = temp[i];
		}	
		
	        for(int i=0; i<n_len; i++){
        	        printf("%d ",res[i]);
	        }
	}
	printf("\n");
}
