#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<regex.h>
#define null NULL
#define max_limit 100
#define capacity 300
#define num_len 13

static int track = 1;
int size = 0;
regex_t regex;
char* name_pattern = "^[a-zA-Z ]+$";
char* phone_pattern = "^\\+91[6-9][0-9]{9}$";
char* email_pattern = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";

typedef struct ticket_info{
    	int ticket_number;
    	char* name;
    	char* phone_number;
    	char* email_id;
    	struct ticket_info* next;
}ticket_info;

ticket_info* head = null;
ticket_info* temp = null;

char* string_input(){
    	char* emp = (char*)malloc(sizeof(char)*max_limit);
    	fgets(emp,max_limit,stdin);
    	int len = strlen(emp);
    	if(len>0 && emp[len-1]=='\n'){
        	emp[len-1] = '\0';
    	}
    	return emp;
}

ticket_info* create_ticket(char* name, char* phone, char* email_id){
    	ticket_info* new_entry = (ticket_info*)malloc(sizeof(ticket_info));
    	new_entry->name = (char*)malloc(sizeof(char)*max_limit);
    	new_entry->phone_number = (char*)malloc(sizeof(char)*num_len);
    	new_entry->email_id = (char*)malloc(sizeof(char)*max_limit);
    	new_entry->ticket_number = track++;
    	strcpy(new_entry->name,name);
    	strcpy(new_entry->phone_number,phone);
    	strcpy(new_entry->email_id,email_id);
    	new_entry->next = null;
    	return new_entry;
}

int pattern_matching(char* string_temp, char* pattern_temp){
    	regcomp(&regex, pattern_temp, REG_EXTENDED);
    	int boolean = regexec(&regex, string_temp, 0, null, 0);
    	regfree(&regex);
    	return boolean == 0 ? 1 : 0;
}

void print_list(){
    if (head == null) {
        printf("\n\nThe queue is empty, nothing to print\n\n");
        return;
    }

    ticket_info* temp = head;
    printf("\n%-15s %-30s %-15s %-30s\n", "Ticket_number", "Name", "Mobile no", "Email id");
    printf("-----------------------------------------------------------------------------------------\n");

    while (temp != null) {
        printf("%-15d %-30s %-15s %-30s\n", temp->ticket_number, temp->name, temp->phone_number, temp->email_id);
        temp = temp->next;
    }
    printf("\n");
}

void book_ticket(){
    	int ticket;
    	printf("Enter number of tickets: ");
    	if(scanf("%d", &ticket) != 1){
        	while(getchar() != '\n');
       	printf("Invalid entry, enter only integer\n");
        	return;
    	}
    	if(ticket + size > capacity){
        	printf("Sorry, the seats are full\n");
        	return;
    	}	
    	for(int i = 1; i <= ticket; i++){
        	printf("Enter the information for %d ticket \n", i);
        	printf("Enter the name: ");
        	if(i==1)getchar();
        	char* name = string_input();
        	if(!pattern_matching(name, name_pattern)){
         	    printf("\nInvalid entry, name must only contains characters\n");
         	    printf("Re-enter the details\n\n");
         	    free(name);
         	    i--;
            	    continue;
        	}
        	printf("Enter the number(+91XXXXXXXXXX): ");
        	char* phone_number = string_input();
        	if(!pattern_matching(phone_number, phone_pattern)){
           		printf("\nInvalid entry, number must be in +91XXXXXXXXXX format\n");
            		printf("Re-enter the details\n\n");
            		free(name); 
            		free(phone_number);
            		i--;
            		continue;
        	}
        	printf("Enter the email id: ");
        	char* email_id = string_input();
        	if(!pattern_matching(email_id, email_pattern)){
            		printf("\nInvalid entry, enter correct email format, ex:- abc@gmail.com.\n");
            		printf("Re-enter the details\n\n");
            		free(name); 
            		free(phone_number); 
            		free(email_id);
            		i--;
        	    	continue;
        	}
        	if(head == null){
            		head = temp = create_ticket(name, phone_number, email_id);
        	} else {
            		temp->next = create_ticket(name, phone_number, email_id);
        		temp = temp->next;
        	}
        	size++;
        	printf("\n.......Booking successfull.......\n");
        	printf("\n");	
    }
    		
}

int main(){
    while(1){
        printf("\nTicket Booking: \n");
        printf("------------------------------------\n");
        printf("1. Book Tickets\n");
        printf("2. Cancel Tickets\n");
        printf("3. Next Ticket\n");
        printf("4. View Ticket info's\n");
        printf("5. Clear Ticket\n");
        printf("6. Exit\n");
        printf("------------------------------------\n\n");
        printf("Enter: ");
        int choice;
        if(scanf("%d", &choice) != 1){
            while(getchar() != '\n');
            printf("Invalid entry, enter only integer\n\n");
            continue;
        }
        if(choice == 1){
            book_ticket();
        }
        else if(choice == 2){
            if(size==0){
            	printf("\nQueue is empty\n");
            	continue;
            }
            head = head->next;
            printf("Deleted Successfully\n\n");
            size--;
        }
        else if(choice == 3){
        	if(size==0){
        		printf("The queue is empty\n");
        		continue;

        	}
        	printf("\n\nThe next ticket number is %d, Name of the person is %s.\n\n",head->ticket_number,head->name);
        }
        else if(choice == 4){
        	print_list();
        }
        else if(choice == 5){
        	if(size==0){
        		printf("\nThe queue is already empty\n");
        		continue;
        	}
        	head = null;
        	temp = null;
        	printf("\nQueue has been cleared successfully\n");
        }
        else if(choice == 6){
            printf("Exiting...\n");
            break;
        }
        else{
            printf("Invalid option, please choose again.\n");
        }
    }
    return 0;
}

