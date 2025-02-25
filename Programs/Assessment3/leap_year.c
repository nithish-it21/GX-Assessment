#include<stdio.h>

int leapyear(int n){
	if((n%4==0 && n%100!=0) || n%400==0){
		return 1;
	}
	return 0;
}

void main(){
	unsigned int num;
	printf("Enter the year: ");
        scanf("%d",&num);
	int res = leapyear(num);

	printf("\n");
	printf("OUTPUT\n");
	printf("-----------------------------------\n");
	if(res){
		printf("%d is a leap year\n",num);
	} else{
		printf("%d is not a leap year\n",num);
	}
	printf("-------------------------------------\n");
}
