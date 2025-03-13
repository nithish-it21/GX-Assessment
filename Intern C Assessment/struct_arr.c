#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_limit 50

typedef struct{
	char* student_name;
	int age;
	char* Dob;
}student_info;

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
	
	for(int i=0; i<len; i++){
		printf("Name of the student is %s and age is %d\n",arr[i].student_name,arr[i].age);
	}
	


	//Addon
	getchar();
	int found = 0;
	char* buff = (char*)malloc(sizeof(char) * max_limit);
	printf("Enter the name to Search: ");
	scanf("%[^\n]",buff);
	for(int i=0; i<len; i++){
		if(strcmp(buff,arr[i].student_name)==0){
			printf("\nName: %s\n",arr[i].student_name);
			printf("Age: %d\n",arr[i].age);
			printf("DOB: %s\n",arr[i].Dob);
			found=1;
		}
	}

	if(found==0) printf("Student Not found\n");
}
