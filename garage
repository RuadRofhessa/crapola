/*
 
	Jason Ruther
	
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 20//max length allocated for strings

typedef struct Car{
	int year;
	char* make;
	char* model;
	int miles;
} Car;

void fill_garage( Car** garage, char* cars, int* size);	/*takes a **Car mallocs memory for the array based off first int value of input file then mallocs the strings[MAX_STRING_LEN]
							 and then loads the data based off input file in the car array*/
		
int equals (Car* car, int year, char* make, char* model);//compares data from the Car with data recieved to see if the data matches 1 is match 0 is not a match

void drive_cars(Car* garage, int* num_cars, char* driving_records);//opens an update file then goes through the array comparing year make and model and updating millage if its a match

void store_car_statistics(Car* garage, int num_cars, char* outFile);//opens an output file for writing writes size  then year make model millage for each element in the array

void empty_garage(Car* garage, int num_cars);//free the malloced memory for the strings then the car array



int main(int argc, char* argv[]){//should have 4 inputs excutable's name[0] input file's name[1] update file's name[2] and output's file name[3]

	if ( argc != 4 ){
		printf("Insuficent arguments\n Correct ussage: %s <garage input file> <garage update file> <garage output file>\n", argv[0]);
		return -1;
	}

	Car* garage = NULL;
	int size = 0;//size of the garage array

	fill_garage( &garage, argv[1], &size );
	if ( garage == NULL )
		return -1;

	drive_cars( garage, &size, argv[2] );

	store_car_statistics( garage, size, argv[3]);

	empty_garage( garage, size );

	return 0;
}



void fill_garage( Car** garage, char* cars, int* size){

/*	file opening for input file 						*/
	FILE* fp = fopen(cars, "r");

	if ( fp == NULL ){
		printf("Unable to open input file\n");
		return;
	}

/*	sets the size of the garage						*/
	fscanf(fp, "%d", size);

	if (*(size) <= 0 ){
		printf("Invalid garage size");
		return;
	}

/*	memory allocation of car  array						*/
	*(garage) = malloc(sizeof(Car) * *(size) );
	
	if (*garage == NULL){
		printf("Unable to allocate memory for garage");
		return;
	}

	int i = 0;
	for ( i = 0; i < *(size); i++ ){
		(*(garage)+i)->make = NULL;
		(*(garage)+i)->model = NULL;

/*		allocated memory for the strings within the car array		*/
		(*(garage)+i)->make = malloc(sizeof(char)* MAX_STRING_LEN);
		(*(garage)+i)->model = malloc(sizeof(char)* MAX_STRING_LEN);
		if ((*(garage)+i)->make == NULL || (*(garage)+i)->model == NULL ){
			printf("unable to allocate memory for make or model names [%d]", i);
			free(*(garage));
			*(garage) = NULL;
			return;
		}

/*		sets data from the input file to the car array			*/
		fscanf(fp, "%d %s %s %d", &(*(garage)+i)->year, (*(garage)+i)->make, (*(garage)+i)->model, &(*(garage)+i)->miles);
	}

	fclose(fp);
}



int equals ( Car* car, int year, char* make, char* model ){

	if ( (car)->year != year ){
		return 0;
	}else if(strcmp(make, (car)->make) != 0){
		return 0;
	}else if(strcmp(model, (car)->model) != 0){
		return 0;
	}

	return 1;
}



void drive_cars(Car* garage, int* num_cars, char* driving_records ){

/*	opens update file for reading						*/
	FILE* fp = fopen(driving_records, "r");

	if ( fp == NULL ){
		printf("Unable to open update file\n");
		return;
	}
/*	gets first data value of the file and set that for the size of the file	*/
	int size = 0;
	fscanf(fp, "%d", &size);
	if ( size == 0){
		printf("no new records for update\n");
		return;
	}

	if (size < 0 ){
		printf("invalid update size\n");
		return;
	}

	int i = 0, j = 0, year = 0, miles = 0;
	char make[MAX_STRING_LEN];
	char model[MAX_STRING_LEN];

	for ( j = 0; j < size; j++ ){
		fscanf(fp, "%d %s %s %d", &year, make, model, &miles);//loads file data in temp values
		for( i = 0; i < *(num_cars); i++)
			if ( equals( (garage+i), year, make, model) == 1)//check to see if equal if it is update the miles of the car if not does nothing
				(garage+i)->miles += miles;
		
	}

	fclose(fp);
}



void store_car_statistics(Car* garage, int num_cars, char* outFile){

/*	Opens output file for writing						*/
	FILE* fp = fopen(outFile, "w");

	if ( fp == NULL ){
		printf("Unable to make output file");
		return;
	}

/*	writes the size of the garage as first value of the file		*/
	fprintf(fp, "%d\n", num_cars);

	int i = 0;
	for ( i = 0; i < num_cars; i++)//writes every car to the garage in order of year make model and miles
		fprintf(fp, "%d %s %s %d\n", (garage+i)->year, (garage+i)->make, (garage+i)->model, (garage+i)->miles);

	fclose(fp);
}



void empty_garage(Car* garage, int size){

	int i = 0;

	for( i = 0; i < size; i++){//frees all string allocated data
		free((garage+i)->make);
		free((garage+i)->model);
	}

	free(garage);//free all allocated memory for the garage
}
