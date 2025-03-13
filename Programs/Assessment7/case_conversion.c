#include<stdio.h>
#include<stdlib.h>
#define null NULL
#define max_limit 1000

FILE* file;
int using_current = 0;

void createfile(){
	if(using_current != 0){
		printf("\n\033[31mClear the file before creating a new one\033[0m\n\n");
		return;
	}
	using_current = 1;
	file = fopen("caseazAZ.txt", "w+"); 
	if (file == NULL) {
		perror("Unable to open the file");
		return;
	}

	char* buff = (char*)malloc(max_limit * sizeof(char));
	if (buff == NULL) {
		perror("Unable to allocate memory");
		fclose(file);
		return;
	}

	printf("\nEnter a string: ");
	fgets(buff, max_limit, stdin);

	if (fputs(buff, file) != EOF) {
		printf("\n....File created and appended successfully...\n\n");
	} else {
		perror("Unable to write to the file");
	}

	free(buff);
	fclose(file);
}

void appendfile(){
	if(using_current == 0){
		printf("\n\033[31mCreate a file to append\033[0m\n\n");
		return;
	}

	file = fopen("caseazAZ.txt", "a+");
	if (file == NULL) {
		perror("Unable to open the file for appending");
		return;
	}

	printf("Enter the string to append: ");
	char* buff = (char*)malloc(max_limit * sizeof(char));
	if (buff == NULL) {
		perror("Unable to allocate memory");
		fclose(file);
		return;
	}

	fgets(buff, max_limit, stdin);

	if (fputs(buff, file) != EOF) {
		printf("\n...String has been inserted successfully\n\n");
	} else {
		perror("Unable to append to the file");
	}

	free(buff);
	fclose(file);
}


void print_file(){
	if(using_current==0){
		printf("\n\33[031mNo file exist\33[0m\n\n");
		return;
	}
	printf("\nFile content\n\n");
	char* buffer = (char*)malloc(max_limit*sizeof(char));
	FILE* fp = fopen("caseazAZ.txt","r");
	while(fgets(buffer,max_limit,fp)!=null){
		printf("%s",buffer);
	}
}

void change_case(){
        if(using_current==0){
                printf("\n\33[031mNo file exist\33[0m\n\n");
                return;
        }
	FILE* ftemp = fopen("caseazAZ.txt","r");
	char* buffer = (char*)malloc(max_limit*sizeof(char));
	char ch;
	int idx = 0;
	while((ch = fgetc(ftemp))!=EOF){
		if(ch>='a' && ch<='z'){
			ch = ch - 32;
		}
		else if(ch>='A' && ch<='Z'){
			ch = ch + 32;
		}
		buffer[idx++] = ch;
	}
	buffer[idx] = '\0';
	fclose(ftemp);
	FILE* ftemp_2 = fopen("caseazAZ.txt","w");
	fputs(buffer,ftemp_2);
	fclose(ftemp_2);
	free(buffer);
	printf("\nCases changed in the File successfully\n\n");
}

int main(){
	while(1){
		printf("File Handling\n");
		printf("------------------------------\n");
		printf("1. Create and write\n");
		printf("2. Append in File\n");
		printf("3. Print file\n");
		printf("4. Change Case\n");
		printf("5. Clear file\n");
		printf("6. Exit\n");
		printf("------------------------------\n\n");

		int choice;
		printf("Enter: ");
		if(scanf("%d", &choice) != 1){
			while(getchar() != '\n');
			printf("Invalid entry, enter only integer\n\n");
			continue;
		}

		while(getchar() != '\n'); 

		if(choice == 1){
			createfile();
		}
		else if(choice == 2){
			appendfile();
		}
		else if(choice == 3){
			print_file();
			printf("\n");
		}
		else if(choice == 4){
			change_case();
		}
		else if (choice == 5) {
    			if (remove("caseazAZ.txt") == 0) {
        			using_current = 0;
        			printf("\nThe file has been deleted successfully.\n\n");
    			} else {
        			perror("\nError deleting file: ");
			       	printf("\n\n");
    			}
		}

		else if(choice == 6){
			printf("Exiting.......\n\n");
			return 0;
		}
		else{
			printf("Invalid entry, enter only integer\n\n");
		}
	}

	return 0;
}

