#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LEN 20

typedef struct account{
	int accountID;
	char* name;
	double amount;
}account;

account* load_accounts(char* inputFile, int* size);//loads accounts and mallocs a account struct array[size] and returns the pointer
account* find_account( account* accounts, int* size, int accountID);//finds an account based off accountID returns point of the account
void update_accounts(char* updateFile, account* accounts, int* size);//updates the account requires update file account # ammount
void write_accounts(char* outputFile, account* accounts, int* size);// writes the account array to a file called output
void free_accounts(account* accounts, int* size);//clears all malloc memory


int main ( int argc, char **argv )
{
	if (argc != 4 ){
		printf("insufficent arguments\n");
		return;
	}
	account* accounts;
	int size;

	accounts = load_accounts(argv[1], &size);
	if ( accounts == NULL ){
		printf("unable to load account file\n");
		return 0;
	}

	update_accounts(argv[2], accounts, &size);

	write_accounts(argv[3], accounts, &size);

	free_accounts( accounts, &size);

	return 0;

}

account* load_accounts( char* inputFile, int* size)
{

	FILE* fp = fopen(inputFile, "r");
	if ( fp == NULL)
		return NULL;

	account* accountArray = malloc( sizeof (account)* *(size));
	
	int i = 0;
	for( i = 0; i < *(size); i++ )
		(accountArray+i)->name = malloc( sizeof (char) * MAX_STRING_LEN);


	fscanf(fp, "%d \n", size);
	//printf("%d size", *size);
	for ( i = 0; i < *(size); i++){
		fscanf( fp, "%d %s %lf", &(accountArray+i)->accountID, (accountArray+i)->name, &(accountArray+i)->amount);
		printf("\n %d ID, %s NAME, %f AMOUNT \n", ((accountArray+i)->accountID), (accountArray+i)->name, ((accountArray+i)->amount));
	}
	fclose(fp);
	return accountArray;
}

account* find_account(account* accounts, int* size, int accountID)
{

	int i = 0;

	for( i = 0; i < *(size); i++ )
		if ( (accounts)->accountID == accountID );
			return (accounts+i);

	return NULL;
}

void update_accounts( char* updateFile, account* accounts, int* size )
{
	FILE* fp = fopen(updateFile, "r");
	if ( fp == NULL){
		printf("Unable to open update file");
		return;
	}

	int AccountID = 0, i = 0, updateSize = 0;
	double transaction = 0;
	account* temp;

	fscanf(fp, "%d", &(updateSize));

	for ( i = 0; i < *(size); i++ ){
		fscanf(fp, "%d %lf", &(AccountID), &(transaction));
		temp = find_account(accounts, size, AccountID);
		if (temp == NULL)		
			printf("Unable to find account %d", &AccountID);

		else{
			(temp)->amount += transaction;
			//printf("%d, %lf \n", (temp)->amount, transaction);
		}
	}
}

void write_accounts( char* outputFile, account* accounts, int* size)
{
	FILE* fp = fopen(outputFile, "w");
	if ( fp == NULL ) {
		printf("Unable to open output file");
		return;
	}
	int i = 0;

	for( i = 0; i < *(size); i++){
		fprintf(fp, "%d %s %f\n", (accounts+i)->accountID, (accounts+i)->name, (accounts+i)->amount);
		//printf("%d %s %f \n", (accounts+i)->accountID, (accounts+i)->name, (accounts+i)->amount);
	}
	return;

}

void free_accounts(account* accounts, int* size)
{
	int i = 0;

	for ( i = 0; i < *(size); i++)
		free((accounts+i)->name);

	free(accounts);
}
