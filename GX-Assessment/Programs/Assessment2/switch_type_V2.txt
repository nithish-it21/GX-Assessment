//------------------------------------------------------------
/*
 * TESTCASE NAME: Datatype Identification and ASCII Generation
 * AUTHOR       : NITHISH K P
 * EXECUTION CMD: gcc switch_type.c -o switch_type && ./switch_type
 * TEST DESC    : To identify the datatype based on the input[Integer, Float, Character, String, Hex].
 * 		  Also to get the ASCII value of the Character input and Generating the ASCII sequence.
 *
 */
//------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <regex.h>

#define MAX_LIMIT 100

void task1() {
    int dec = 0;
    while(1) {
        printf("\n");
        printf("MENU: DATATYPE CHECK\n");
        printf("---------------------\n");
        printf("\n1. To get the Data type");
        printf("\n2. Back to Main menu\n");
        printf("Enter the input: ");
        scanf("%d", &dec);
        getchar();

        if (dec == 1) {
            double val = 1e-12;
            char value[MAX_LIMIT] = "";

            regex_t hex_regex, int_regex, float_regex, alnum_regex;
            const char *hex_pattern = "^0[x][0-9a-fA-F]+$";
            const char *int_pattern = "^-?[0-9]+$";
            const char *float_pattern = "^-?[0-9]*\\.[0-9]+$";
            const char *alnum_pattern = "^[a-zA-Z0-9\\ ]+$";

            printf("Enter a value: ");
            fgets(value, MAX_LIMIT, stdin);
            value[strcspn(value, "\n")] = 0;

            if (regcomp(&hex_regex, hex_pattern, REG_EXTENDED) || regcomp(&int_regex, int_pattern, REG_EXTENDED) || 
                regcomp(&float_regex, float_pattern, REG_EXTENDED) || regcomp(&alnum_regex, alnum_pattern, REG_EXTENDED)) {
                printf("Error\n");
                return;
            }
	    printf("\nOutput");
	    printf("\n--------------------------------------------\n");
            if (regexec(&hex_regex, value, 0, NULL, 0) == 0) {
                printf("%s is a valid hex data type\n", value);
            } 
            else if (regexec(&int_regex, value, 0, NULL, 0) == 0) {
                printf("%s is an integer data type\n", value);
            }
            else if (regexec(&float_regex, value, 0, NULL, 0) == 0) {
                printf("%s is a float data type\n", value);
            }
            else if (strlen(value) == 1) {
                printf("%s is a character data type\n", value);
            }
            else if (strlen(value) > 1) {
                if (regexec(&alnum_regex, value, 0, NULL, 0) == 0) {
                    printf("%s is a string data type\n", value);
                } else {
                    printf("Invalid input expression: The string contains invalid characters.\n");
                }
            }
	    printf("---------------------------------------------\n");
            regfree(&hex_regex);
            regfree(&int_regex);
            regfree(&float_regex);
            regfree(&alnum_regex);
        }
        else if (dec == 2) {
            return;
        } else {
            	printf("\n-----------------------------------\n");
		printf("Invalid input, please enter 1 or 2\n");
		printf("-------------------------------------\n\n");
        }
    }
}

void task2() {
    int dec = 0;
    while(1) {
        printf("Press 1 to enter the character\n");
        printf("Press 2 to main menu\n");
        printf("Enter: ");
        scanf("%d", &dec);
        getchar();

        if (dec == 1) {
            char ch[MAX_LIMIT];
            printf("Enter character: ");
            fgets(ch,MAX_LIMIT,stdin);
	    int str_len = strlen(ch);
	    if(str_len>0 && ch[str_len-1]=='\n'){
	    	ch[str_len-1] = '\0';
		str_len--;
	    }
	    printf("\nOutput\n");
	    printf("-----------------------------------------\n");
	    if(str_len==1){
            	printf("The ASCII value of character '%c' is %d\n", ch[0], ch[0]);
            } else{
	    	printf("Invalid input, enter a single character\n");
	    }
	} else if (dec == 2) {
            return;
        } else {
	    printf("\n---------------------------------\n");
            printf("Invalid input, please enter 1 or 2\n");
        }
	printf("-----------------------------------------\n\n");
    }
}

void task3() {
    int dec = 0;
    while(1) {
        printf("Press 1 to start sequence\n");
        printf("Press 2 to main menu\n");
        printf("Enter: ");
        scanf("%d", &dec);
        getchar();

        if (dec == 1) {
            char ch = 'A';
	    printf("\noutput");
	    printf("\n-----------------------------------\n");
            for (; ch <= 'Z'; ch++) {
                printf("The ASCII value for character %c is %d\n", ch, ch);
            }
	    printf("------------------------------------\n\n");
        } else if (dec == 2) {
            return;
        } else {
	    printf("\n-------------------------------------\n");
            printf("Invalid input, please enter 1 or 2\n");
	    printf("---------------------------------------\n\n");
        }
    }
}

int main() {
    int num;
    while(1) {
        printf("---------------------------------------------\n");
        printf("MAIN MENU:\n");
        printf("\t1. Data type identification\n");
        printf("\t2. ASCII value conversion\n");
        printf("\t3. ASCII generation for A-Z\n");
        printf("\t4. Exit\n");
        printf("---------------------------------------------\n");
        printf("Enter: ");
        scanf("%d", &num);
        getchar();

        if (num == 1) {
	    /*The task1 function is used to datatype Identification */
            task1();
        } else if (num == 2) {
	    /*The task2 function is used to ASCII conversion */
            task2();
        } else if (num == 3) {
	    /*Then task3 function is used to generate Sequence of ASCII value ranges from A-Z */
            task3();
        } else {
            printf("The program has been exited\n");
            break;
        }
    }
    return 0;
}

