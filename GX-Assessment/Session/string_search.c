#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_limit 50

typedef struct{
	char* student_name;
	int age;
	char* Dob;
}student_info;


void swap(student_info* a,student_info* b){
	student_info temp = *a;
       	*a = *b;
	*b = temp;	
}


int compare(const void* a, const void* b){
	char* key = (char*)a;
        student_info* s2 = (student_info*)b;

	return strcmp(key, s2->student_name);	
}


int partition(student_info arr[], int low, int high) {
    student_info pivot_element = arr[high];
    int i = low;
    int j = high;

    while (i < j) {

        while (i < high && strcmp(arr[i].student_name, pivot_element.student_name) <= 0) {
            i++;
        }


        while (j > low && strcmp(arr[j].student_name, pivot_element.student_name) > 0) {
            j--;
        }


        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }


    swap(&arr[high], &arr[i]);
    return i;
}

void quick_sort(student_info arr[], int low, int high){
	if(low<high){
		
		int pi = partition(arr,low,high);

		quick_sort(arr,low,pi-1);
		quick_sort(arr,pi+1,high);
	}
}

void main(){

	int size;
	printf("\nEnter number of students: ");
	if(scanf("%d",&size)!=1){
		printf("Invalid Entry, Enter Only Integer\n");
		while(getchar()!='\n');
		return;
	}
	if(size<=0){
		printf("Invalid size, Need atleast one\n");
		return;
	}
	student_info arr[size];
	
	
	int len = (int)sizeof(arr)/sizeof(student_info);

	for(int i=0; i<len; i++){
		arr[i].student_name = (char*)malloc(sizeof(char) * max_limit);
	        arr[i].Dob = (char*)malloc(sizeof(char) * max_limit);
	}

	


	for(int i=0; i<size; i++){
			getchar();
		char* buff = (char*)malloc(sizeof(char) * max_limit);
		if(arr[i].student_name == NULL || arr[i].Dob==NULL || buff==NULL){
			printf("Memory Allocation failed");
			return;
		}
		printf("Enter the name of the %d student: ",i+1);
		scanf("%[^\n]",buff);
		int day = 0,month = 0,year = 0;

again:		
		printf("Enter the Dob [Format: dd mm yyyy]: ");		
		if(scanf("%d %d %d",&day ,&month, &year)!=3){
			printf("Invalid Entry, Enter in correct format\n");
			while(getchar() != '\n');
			goto again;
		}	
		if(day<=0 || day>31 || month<=0 || month>12){
			printf("Invalid data found\n");
			goto again;
		}
		int t_age = 2025 - year;
		if(t_age>18){
			printf("Not an student\n");
			i--;
			continue;
		}
		strcpy(arr[i].student_name,buff);
		snprintf(arr[i].Dob,max_limit,"%d-%d-%d",day,month,year);
		arr[i].age = t_age;
	}
	printf("\n");
	

        quick_sort(arr,0,size-1);


	for(int i=0; i<len; i++){
		printf("Name of the student is %s and age is %d\n",arr[i].student_name,arr[i].age);
	}
	


	//Addon
	getchar();
	
//	quick_sort(arr,0,size-1);


	char* buff = (char*)malloc(sizeof(char) * max_limit);
	printf("Enter the name to Search: ");
	scanf("%[^\n]",buff);
	printf("\n");
	student_info* res = bsearch(buff,arr,size,sizeof(student_info),compare);
	if(res == NULL){
		printf("Student Not Found.\n"); 
	}
	else{
		printf("Name: %s\n",res->student_name);
		printf("Age: %d\n",res->age);
		printf("Dob: %s\n",res->Dob);
	}
}
