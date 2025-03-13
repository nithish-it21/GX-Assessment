#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <mysql/mysql.h>
#include "base.c"
#define max_limit 255


void disable_echo(){
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ ECHO;
	tcsetattr(STDIN_FILENO,TCSANOW,&term);
}

void enable_echo(){
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO,TCSANOW,&term);
}

void login_in(){
	USER* info;
	printf("Username: ");
	fgets(info->NAME,max_limit,stdin);
	printf("Password: ");
	disable_echo();
	fgets(info->PASSWORD,max_limit,stdin);
	enable_echo();
	printf("\n");
	info->NAME[strcspn(info->NAME,"\n")] = '\0';
	info->PASSWORD[strcspn(info->PASSWORD,"\n")] = '\0';
	int SUCCESS = login_user(info);
	if(SUCCESS==1){
		//Successfull login here
		printf("Success\n\n");
	}
	else if(SUCCESS==2){
		printf("Incorrect Username or Password.\n");
	}
	else{
		printf("Unable to Find the User.\n");
	}
}

void register_in(){
	USER* register_info = (USER*)malloc(sizeof(USER));
	printf("Enter the Username: ");
	fgets(register_info->NAME,max_limit,stdin);
	printf("Enter the Password: ");
	fgets(register_info->PASSWORD,max_limit,stdin);
	printf("Enter the Email: ");
	fgets(register_info->EMAIL,max_limit,stdin);
	printf("\n");
	register_info->NAME[strcspn(register_info->NAME,"\n")] = '\0';
	register_info->PASSWORD[strcspn(register_info->PASSWORD,"\n")] = '\0';
	register_info->EMAIL[strcspn(register_info->EMAIL,"\n")] = '\0';
	register_user(register_info);
}

int main(){
	int opt = 0;
	printf("\n");
	while (1)
	{	
		printf("Application\n");
		printf("1. Login\n");
		printf("2. Register\n");
		printf("3. Exit\n");
		printf("\nEnter the operation: ");
		if(scanf("%d",&opt)!=1){
			while (getchar()!='\n');
			printf("Invalid entry, enter only valid Integers");
			continue;
		}
		getchar();
		if(opt==1){
			login_in();
		}
		else if(opt==2){
			register_in();
		}
		else if(opt==3){
			printf("Exiting....\n");
			return 0;
		}
		else{
			printf("Invalid syntax, Enter Between [1-3]");
		}
	}
}

	
// #include <termios.h>

// void disable_echo() {
//     struct termios term;
//     tcgetattr(STDIN_FILENO, &term);   // Get terminal settings
//     term.c_lflag &= ~ECHO;             // Disable echoing of characters
//     tcsetattr(STDIN_FILENO, TCSANOW, &term); // Apply the new settings
// }

// void enable_echo() {
//     struct termios term;
//     tcgetattr(STDIN_FILENO, &term);   // Get terminal settings
//     term.c_lflag |= ECHO;              // Enable echoing of characters
//     tcsetattr(STDIN_FILENO, TCSANOW, &term); // Apply the new settings
// }
