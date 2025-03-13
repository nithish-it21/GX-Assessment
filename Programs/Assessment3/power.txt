#include<stdio.h>

int power(int x,int n){
	if(n==0) return 1;
	if(x==0) return 0;
	return x * power(x,n-1);
}

void main(){
	int base;
	int exponent;
	printf("Enter the base: ");
	scanf("%d",&base);
	printf("Enter the exponent: ");
	scanf("%d",&exponent);
	int res = power(base,exponent);
	printf("\n");
	printf("OUTPUT\n");
	printf("----------------------------------\n");
	printf("The result is %d\n",res);
	printf("----------------------------------\n");
}
