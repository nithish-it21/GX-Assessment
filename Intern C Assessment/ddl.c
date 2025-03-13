#include<stdio.h>
#include<stdlib.h>


typedef struct linkedlist{
	struct linkedlist* prev;
	int data;
	struct linkedlist* next;
}linkedlist;

linkedlist* head = NULL;
int size = 0;

linkedlist* createnode(int val){
	linkedlist* temp = (linkedlist*)malloc(sizeof(linkedlist));	
	temp->prev = NULL;
	temp->data = val;
	temp->next = NULL;
	size++;
	return temp;
}

void createlist(){
	if(size!=0){
		printf("Exisiting list found, Clear the list\n");
		return;
	}
	int lsize = 0;
	printf("Enter the list size: ");
	if(scanf("%d",&lsize)!=1){
		printf("Invalid entry, Enter only integer\n");
		while(getchar()!='\n');
		return;
	}
	if(lsize<=0){
		printf("List must have size above 0\n");
		return;
	}
	linkedlist* temp = heaWEd;
	for(int i=0; i<lsize; i++){
		int element;
		printf("Enter the %d element: ",i+1);
		if(scanf("%d",&element)!=1){
			printf("Enter only Integer");
			while(getchar()!='\n');
			i--;
			continue;
		}
		if(head==NULL){
			head = createnode(element);
			temp = head;
			continue;
		}
		temp->next = createnode(element);
		linkedlist* temp2 = temp;
		temp = temp->next;
		temp->prev = temp2;
	}
	printf("The list has been Inserted Successfully\n");
}


void insert(){
	if(size==0){
		printf("The list is Emprt, Create a list first\n");
		return;
	}
	int idx = 0;
	printf("Enter the index to insert: ");
	if(scanf("%d",&idx)!=1){
		printf("Enter only Integer\n");
		while(getchar()!='\n');
		return;
	}
	if(idx<=0 || idx>size+1){
		printf("Enter the valid index list range 1 - %d.\n",size+1);
		return;
	}
	int element;
	printf("Enter the element to insert: ");
	if(scanf("%d", &element)!=1){
		printf("Enter valid Integer\n");
		return;
	}

        linkedlist* preve = NULL;
        linkedlist* curr = head;

	if(idx==1){
		linkedlist* temp = createnode(element);
		temp->next = head;
		head->prev = temp;
		head = temp;
	}
	else if(idx==size+1){
		linkedlist* temp = head;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = createnode(element);
		linkedlist* temp2 = temp;
		temp = temp->next;
		temp->prev = temp2;
	}
	else{
		for(int i=1; i<idx; i++){
			preve = curr;
			curr = curr->next;
		}
		linkedlist* temp = createnode(element);
		preve->next = temp;
		temp->prev = preve;
		temp->next = curr;
		curr->prev = temp;
	}
	printf("The list has been created Successfully\n");
}

void delete(){
	if(size==0){
		printf("The list is Empty, Create a list first\n");
		return;
	}
	int idx = 0;
	printf("Enter the index to delete: ");
	if(scanf("%d",&idx)!=1){
		printf("Enter only Integer\n");
		while(getchar()!='\n');
		return;
	}
	if(idx<=0 || idx>size){
		printf("Enter the valid index list range 1 - %d.\n",size);
		return;
	}
	if(idx==1){
		head = head->next;
		head->prev = NULL;
		size--;
	}
	else if(idx==size){
		linkedlist* temp = head;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp = temp->prev;
		temp->next = NULL;
		size--;
	}
	else{
		linkedlist* temp = head;
		for(int i=1; i<idx; i++){
			temp = temp->next;
		}
		linkedlist* preve = temp->prev;
		linkedlist* curr = temp->next;
		preve->next = temp->next;
		curr->prev = temp->prev;
		size--;
	}
	printf("The list has been deleted Successfully\n");
}

void print_list(){
	if(size==0){
		printf("The list is empty\n");
		return;
	}
	linkedlist* temp = head;
	while(temp != NULL){
		printf("%d ",temp->data);
		temp = temp->next;
	}
	printf("\nThe list size is %d\n",size);
}


void clear_list(){
	if(size==0){
		printf("The list is already Empty\n");
		return;
	}
	linkedlist* temp = head;
	while(temp!=NULL){
		linkedlist* f_temp = temp;
		temp = temp->next;
		free(f_temp);
	}
	size = 0;
	head = NULL;
	printf("The list has been cleared successfully\n");
}



void main(){
	int opt;
	while(1){
		printf("Double linked list operation\n");
		printf("1. Create List\n");
		printf("2. Insert in List\n");
		printf("3. Delete in List\n");
		printf("4. View List\n");
		printf("5. Clear List\n");
		printf("6. Exit\n\n");

		printf("Enter the operation: ");
		if(scanf("%d", &opt)!=1){
			printf("Invalid entry, Enter only Integer\n");
			while(getchar()!='\n');
			continue;
		}
		if(opt==1){
			createlist();
			printf("\n");
		}	
		else if(opt==2){
			insert();
			printf("\n");
		}
                else if(opt==3){
                	delete();
			printf("\n");
                }
                else if(opt==4){
                	print_list();
			printf("\n");
                }
                else if(opt==5){
                	clear_list();
			printf("\n");
                }
                else if(opt==6){
                	printf("Exiting....\n");
			printf("\n");
			return;
                }
		else{
			printf("Invalid entry, Enter only Integer\n");
			printf("\n");
		}
	}
}
