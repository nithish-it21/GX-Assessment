#include<stdio.h>
#include<stdlib.h>
#define null NULL

static int size = 0;
static int isEmpty = 0;


int scan(){

	int num;
	if(scanf("%d",&num)!=1){
		while(getchar()!='\n');
		printf("Invalid Entry, enter only integers");
	}
	return num;

}

typedef struct Node{
	int data;
	struct Node* next;
}Node;

	Node* head = NULL;
	Node* temp = null;

Node* newNode(int data){
	Node* temp2 = (Node*)malloc(sizeof(Node));
	temp2->data = data;
	temp2->next = NULL;
	size++;
	return temp2;
}


void print_list(){
	Node* print_temp = head;
	if(isEmpty==0){
		printf("\nThe list is empty\n");
		return;
	}
	printf("[ ");
	while(print_temp!=null){
		printf("%d ",print_temp->data);
		print_temp = print_temp->next;
	}
	getchar();
	printf("]\n\n");
}


void insert_into_list(){

	if(isEmpty==0){
		printf("\nCreate the List to insert\n");
		return;
	}
	printf("Current list elements: ");
	print_list();
	int index;
	printf("Enter the index to insert: ");
	scanf("%d",&index);
	if(index-1>size || index<=0){
		printf("Invalid index, Size of List is %d\n",size);
		return;
	}
	int num;
	printf("\nEnter the element: ");
	if(scanf("%d",&num)!=1){
		while(getchar()!='\n');
		printf("Invalid entry enter only integer\n");
		return;
	}
	Node* temp2 = newNode(num);
	if(index==1){
		temp2->next = head;
		head = temp2;
		size++;		
	}
	Node* prev = null;
	Node* temp1 = head;

	 for (int i = 1; i < index - 1; i++) {
            temp1 = temp1->next;
        }
	
	prev = temp1;
	temp1 = temp1->next;
	
	prev->next = temp2;
	temp2->next = temp1;
	
	size++;
	printf("\nUpdated list elements: ");
	print_list();
	printf("\nInserted successfully\n");

}

void delete_in_list(){
	
	if(isEmpty==0){
		printf("\nList is empty\n");
		return;
	}
	printf("Current list elements: ");
	print_list();
	int index;
	printf("Enter the index to delete: ");
	scanf("%d",&index);
	Node* res = head;
	if(index>=size || index<=0){
		printf("Invalid index, Size of List is %d\n",size);
		return;
	}
	if(index==1 && head->next!=null){
		head = head->next;
		size--;
		printf("\nDeleted Successfully\n");
		return;
	}
	Node* prev = null;
	while(index--!=1){
		prev = res;
		res = res->next;	
	}
	if(res->next!=null){
		prev->next = res->next;
	}
	else{
		prev->next = null;
	}
	size--;
	printf("\nUpdated list elements: ");
	print_list();
	printf("\nDeleted Successfully\n");
}

void replace_list(){
	if(isEmpty==0){
		printf("\nList is empty\n");
		return;
	}
	printf("Current list elements: ");
	print_list();
	
	printf("\n\t1. Replace by value");
	printf("\n\t2. Replace by index");
	printf("\n\t3. Return to main menu");
	printf("\n\n\tEnter: ");
	int s_choice;
	scanf("%d",&s_choice);
	if(s_choice==1){
		int choice1_val,check;
		printf("\n\nEnter the value: ");
		if(scanf("%d",&choice1_val)!=1){
			while(getchar()!='\n');
			printf("Invalid entry enter only integer\n");
			return;
		}
		printf("\nEnter the value to replace: ");
		if(scanf("%d",&check)!=1){
			while(getchar()!='\n');
			printf("Invalid entry enter only integer\n");
			return;
		}
		int find = 0;
		Node* curr = head;
		while(curr!=null){
			if(curr->data == check){
				curr->data = choice1_val;
				find = 1;
			}
			curr = curr->next;
		}
		if(find==0){
			printf("\n\nNo value found in list");
			return;
		}
	}
	else if(s_choice==2){
		int index, val;
		printf("\nEnter the index to replace: ");
		scanf("%d",&index);
		if(index>=size || index<=0){
			printf("Invalid index, Size of List is %d\n",size);
			return;
		}
		printf("\nEnter the value: ");
		if(scanf("%d",&val)!=1){
			while(getchar()!='\n');
			printf("Invalid entry enter only integer\n");
			return;
		}
		int temp_index = 1;
		Node* curr = head;
		while(index!=temp_index){
			curr = curr->next;
			temp_index++;
		}
		curr->data = val;
	}
	else{
		printf("Invalid Entry\n");
		return;
	}
		printf("\nUpdated list elements: ");
		print_list();
}


void temp10(){
	if(isEmpty==1){
		printf("\nEmpty the current list to add a new List\n"); 
		return;
	}
	int nodes;
	printf("Enter the nodes: ");
	scanf("%d",&nodes);

	while(nodes--){
		int dt;
		printf("Enter the data: ");
		if(scanf("%d",&dt)!=1){
		while(getchar()=='\n');
			isEmpty = 0;
			head = null;
			printf("\nEnter only Integer\n");
			return;
		}
		if(head==NULL){
			isEmpty=1;
			head = newNode(dt);
			temp = head;
		}	
		else{
			temp->next = newNode(dt);
			temp = temp->next;
		}
	}
	printf("\nCreated successfully\n");
}

void main(){
	while(1){
		int choice;
		printf("\nMenu\n");
		printf("---------------------------------------------\n");
		printf("1. Create a Linked List\n");
		printf("2. Insert into Linked List\n");
		printf("3. Delete Node in Linked List\n");
		printf("4. View Linked List\n");
		printf("5. Clear the Linked List\n");
		printf("6. Replace in List\n");
		printf("7. Exit\n");
		printf("---------------------------------------------\n\n");
		
		printf("Enter: "); 
		if(scanf("%d",&choice)!=1){
			printf("\nInvalid Entry, enter only Integer\n");
			while(getchar() != '\n'); 			
			continue;
		}
		if(choice==1){
			temp10();
		}
		else if(choice==2){
			insert_into_list();
		}
		else if(choice==3){
			delete_in_list();
		}
		else if(choice==4){
			print_list();

		}
		else if(choice==5){
			if(isEmpty==0){
			printf("\nThe list is already empty\n");
			continue;
		}
			head = null;
			isEmpty = 0;
			printf("\nList has been deleted successfully\n");
		}
		else if(choice==6){
			replace_list();
		}
		else if(choice==7){
			printf("Exited successfully\n");
			break;
		}
		else{
			printf("Please Enter only valid inputs\n");
		}				
	}
}
