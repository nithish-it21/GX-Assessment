#include<stdio.h>


int sum_of_square(int n){
	return (n*(n+1)*(2*n+1))/6;
}

int sum_of_square_loop(int n){
	int res = 0;
	for(int i = 1; i<=n; i++){
		res+=(i*i);
	}
	return res;
}

void main(){
	int num;
	printf("Enter the Num: ");
	scanf("%d",&num);
	int res = sum_of_square(num);
	int res2 = sum_of_square_loop(num);
	printf("\n");
	printf("OUTPUT\n");
	printf("----------------------------\n");
	printf("The result by using formula: %d\n",res);
	printf("The result by using loop: %d\n",res2);
	printf("----------------------------\n");


}
