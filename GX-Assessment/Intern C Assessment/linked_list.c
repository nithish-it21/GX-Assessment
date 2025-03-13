#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>


int size = 0;

typedef struct linked_list{
	int data;
	struct linked_list* next;
}linked_list;

linked_list* head = NULL;

linked_list* createnode(int val){
	linked_list* node = (linked_list*)malloc(sizeof(linked_list));
	node->data = val;
	node->next = NULL;
	size++;
	return node;
}


void create_list(){
	if(size!=0){
		printf("Exisiting List found\n");
		return;
	}
	int list_size = 0;
	printf("Enter the size of List: ");
	scanf("%d",&list_size);
	if(list_size<6){
		printf("Sorry the List must have Atleast 6 nodes.\n");
		return;
	}
	linked_list* temp = head;
	for(int i=0; i<list_size; i++){
		int val;
		printf("Enter the %d value: ", i+1);
		scanf("%d",&val);
		if(head==NULL){
			head = createnode(val);
			temp = head;
			continue;
		}
		temp->next = createnode(val);
		temp = temp->next;
	}
	printf("List has Been Created Successfully.\n");
}

void view_list(){
	if(size==0){
		printf("List is not created.\n");
		return;
	}
	printf("The size of the List is %d\n",size);
	linked_list* temp = head;
	while(temp!=NULL){
		printf("%d ",temp->data);
		temp = temp->next;
	}
}

void reverse_list(){
        if(size==0){
                printf("List is not created.\n");
                return;
        }
	linked_list* prev = NULL;
	linked_list* curr = head;
	for(int i=0; i<size; i++){
		linked_list* temp = curr;
		curr = curr->next;
		temp->next = prev;
		prev = temp;
	}
	head = prev;
	printf("\nAfter Reversing: ");
	view_list();
}

void clear_list(){
	if(size==0){
		printf("The List is already Empty\n");
		return;
	}
	size = 0;
	head=NULL;
	printf("The list Has Been Cleared Successfully.\n");
}

void main(){
	int opt;

	while(1){

	printf("\nLinked List operations\n");
	printf("1. Create List\n");
	printf("2. View List\n");
	printf("3. Reverse List\n");
	printf("4. Clear List\n");
	printf("5. Exit\n\n");
	
	printf("Enter the choice: ");
	if(scanf("%d",&opt)!=1){
		printf("Invalid Entry, enter only Integer.\n");
		while(getchar() != '\n');
		continue;
	}
	getchar();	
	if(opt==1){
		create_list();
	}
	else if(opt==2){
		view_list();
	}
	else if(opt==3){
		reverse_list();
	}
	else if(opt==4){
		clear_list();
	}
	else if(opt==5){
		printf("Exiting...\n");
		return;
	}
	else{
		printf("Invalid Input, Enter Option Between [1-5].\n");
	}
	}

}
