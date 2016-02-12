#include <stdio.h>
#include <stdlib.h>

typedef struct node_{

        int val;
        struct node_ *next;
		struct node_ *previous;

}node;


node* insert_at_head(node *head, int val);

node* create_list(char *file);

void print_list(node *head);

node* delete_even(node *head);

void delete_node(node *current);

void delete_list( node *head);

int main(int argv, char *argc[]){
	
	if ( argv != 2 ){
		printf(" not enough arguments. Usage ./a.out <input file name> \n");
		return -1;
	}
	
	node *head, *temp;
	head = NULL;
	
	head = create_list( argc[1]);
	
	temp = head;
	print_list ( temp );
	
	temp = head; //for some reason just calling either function decides to break it doesn't even get into the function and the points are NULL
	head = delete_even( temp );
	
	//temp = head;
	//delete_list( temp ); //same for this one also
	
	return 1;

}

node* create_list(char *file){

	FILE* fp = fopen( file, "r");
	if ( fp == NULL ){
		printf("Unable to open file");
		return NULL;
	}
	node *temp_head;
	temp_head = NULL;
	int val = 0;
	int i = 0;
	while ( i == 0 ){
			
		fscanf(fp, "%d", &(val));
		temp_head = insert_at_head(temp_head, val);
		
		if (feof(fp))
			break;	
	}
	
	return temp_head;
}

void print_list ( node *head){

	if ( head == NULL ){
		printf("empty list");
		return;
	}
	
	printf("Print list \n");
	node *temp = head;
	
	while ( temp->next != NULL ){
	
		
		printf( "%d ", temp->val);
		temp = temp->next;
		if ( temp == NULL )
			break;
	}
	
	printf("\n");

}

node* insert_at_head(node *head, int val){

        if ( head == NULL){
		
            head = malloc(sizeof(node));
            head->val = val;
            head->next = NULL;
            head->previous = NULL;
            return head;
				
        } else {
		
			node *new_Node = malloc(sizeof(node));
			new_Node->val = val;
			new_Node->next = head;
			new_Node->previous = NULL;
			head->previous = new_Node;
			return new_Node;
			
		}
}

node* delete_even(node* head){

	node* temp = head;

	while( temp->next != NULL ){
	
		if ( temp->val%2 == 0 ){
			delete_node(temp);
		}
		
		if ( temp == NULL )
			break;
	}
}

void delete_node(node *current){

	node *temp = current;
	if ( temp->next == NULL && temp->previous == NULL ){
		printf("Empty List");
		return;
	}
	
	
	if ( temp->previous == NULL ){
		
		temp = temp->next;
		free(current);
		current = temp;
		return;
		
	}
		
	
	if (temp-> next == NULL ){
	
		temp = temp->previous;
		free(current);
		current = temp;
	
	}
	

	(*(temp->previous)).next = temp->next;
	(*(temp->next)).previous = temp->previous;
	free(current);
	current = temp;
	
}

void delete_list ( node* head ){

	node *temp = head;
	
	while ( temp->next != NULL) {
	
		delete_node ( temp );
		
		if ( temp == NULL )
			break;
	}
	
	printf("\nDeleted the list\n");
	
}
