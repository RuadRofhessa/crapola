#include <stdio.h>
#include <stdlib.h>

int *load_array(char* file, int* length);//loads file takes first number as size of the array, mallocs int array[size] and return address of that array

void insertion_sort(int array[], int size);//sorts the array in asscending order

int binary_search(int array[], int key, int low, int high);//finds a array element and returns the index if -1 then the element does not exist

int fib(int n);//finds the Nth fibonacci number

int main(int argc, char* argv[]){

	if( argc != 2 ){
		printf("Invalid input a.out <file name>");
		return -1;
	}
	int size, i;

/***********************File load******************************/
	int* array = load_array(argv[1], &size );
	if ( array == NULL )
		return -1;

/************************Print array***************************/
	printf("Before Sort\n");
	for ( i = 0; i < size; i++)
		printf(",%d ", *(array+i));

/*************************Sort and reprint*********************/
	insertion_sort( array, size);
	printf("\nAfter Sort\n");
	for ( i = 0; i < size; i++)
		printf(",%d ", *(array+i));

/*****************Find fibonacci numbes then print again*******/
	printf("\nFibnocci numbers\n");
	for ( i = 0; i < size; i++){
		*(array+i) = fib(*(array+i));//FIB calls
		printf(",%d ", *(array+i));
	}

/*******************Pick a number*****************************/
	int input = 0;
	printf("\nPick a number: ");
	scanf("%d", &input);
	if ( input < 0 ){
		printf("Invalid Number");
		free(array);
		return -1;
	}

/*************************find a number**********************/
	int index = binary_search(array, input, 0, size); 
	if ( index == -1)
		printf("input does not exist in the array\n");
	else
		printf("The %d is in index number %d\n", input, index+1);
	
/**************clean up and exit*****************************/
	free(array);

	return 0;
}

int* load_array(char* file, int* length){

	FILE* fp = fopen(file, "r");
	if (file == NULL){
		printf("Unable to load file %s", file);
		return NULL;
	}

	fscanf(fp, "%d", length);

	if (length <= 0){
		printf("Invalid array size");
		return NULL;
	}

	int* Array  = malloc( sizeof(int)* *(length));
	if (Array == NULL){
		printf("Unable to allocate array memory");
		return NULL;
	}
	int i;
	for( i = 0; i < *(length); i++)
		fscanf(fp, "%d",Array+i);

	fclose(fp);
	return Array;  
}


void insertion_sort(int* input, int size){

	int i, j, element = 0;

	for( i = 1; i < size; i++){
		element = input[i];
		j = i;
		while( j > 0 && input[j-1] > element){
			input[j] = input[j-1];
			j -= 1;
		}
		input[j] = element;

	}
}

int binary_search( int b[], int searchKey, int low, int high){

	int middle = (low+high)/2;

	if ( low > high ){
		return -1;
	}
	if ( searchKey == b[middle]){
		return middle;
	}
	else if (searchKey < b[middle]){
		binary_search( b, searchKey, low,  middle - 1);
	}
	else{
		binary_search(b, searchKey, middle + 1, high);
	}
}

int fib( int input ){
	
	int output = 0;
	if ( input < 0 ){
		printf("invalid number n > 0");
		return -1;
	}
	if ( input == 0 )// N = 0 in fib sequences is 0
		return 0;

	if ( input == 1 || input == 2 )//n = 1 or 2 in fib squence is 1
		return 1;

	return fib( input - 1 ) + fib( input - 2 );

}
