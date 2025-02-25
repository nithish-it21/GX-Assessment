#include <stdio.h>
#include <math.h>
#include <string.h>

int count(int temp) {
    int incr = 0;
    while(temp != 0) {
        incr++;
        temp /= 10;
    }
    return incr;
}

int isarmstrong(int num) {
    int x = count(num);
    int str_dup = num;
    int sum = 0;
    
    while (num != 0) {
        int rem = num % 10;
        sum += (int)pow(rem, x);
        num /= 10;
    }
    
    if (sum == str_dup)
        return 1;
    return 0;
}

int main() {
    int loop = 0;
    int process = 0;
    
    while(loop == 0) {
        printf("Enter the following number to perform task\n");
        printf("1. Check Armstrong Number\n");
        printf("2. Check Non-Armstrong Number\n");
        printf("3. Exit\n");
        printf("Process in number: ");
        
        scanf("%d", &process);
        getchar();
        if(process==3){
        	printf("Thanks for using this Service\n");
        	return 0;
        }
        printf("Enter an Integer: ");
        int number;
        char input[10000];
        int result;

        if(fgets(input, sizeof(input), stdin) != NULL) {
            result = sscanf(input, "%d", &number);

            if(result == 1) {
                if(strchr(input, '.') != NULL) {
                    printf("Error: Invalid input.\n");
                } else {
                    switch(process) {
                        case 1:
                            if (isarmstrong(number) == 1) {
                                printf("Yes, it is an Armstrong number.\n");
                            } else {
                                printf("No, it is not an Armstrong number.\n");
                            }
                            break;
                        case 2:
                            if(isarmstrong(number) != 1) {
                                printf("Yes, the given number is not an Armstrong number.\n");
                            } else {
                                printf("No, the given number is an Armstrong number.\n");
                            }
                            break;
                        default:
                            printf("Please enter a valid number between 1-3.\n");
                            break;
                    }
                }
            } else {
                printf("Error: Invalid input.\n");
            }
        }
    }
    return 0;
}

