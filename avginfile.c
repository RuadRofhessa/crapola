#include <stdio.h>
#include <stdlib.h>

int* readFile(char* inputFile);//opens a file called file name returns NULL if cannot open and returns array pointer of int[10]
void writeOut(char* outFile, int min, int max, int avg);//recieves the statisical information and writes it to a file

int findMin(int* array);//find min in a array[10]
int findMax(int* array);//find max in a array[10]
int findAvg(int* array);//find avg of a array[10]

int main ( int argc, char **argv)//returns 0 on error, 1 on success, takes a file name for input then output
{
	
	
	int Min = 0, Max = 0, Avg = 0;

	if ( argc != 3 )//make sure enough information was given
	{
		printf("insufficent arrguments");
		return 0;
	}

	int* numbers=readFile(argv[1]);
	if ( numbers == NULL )//make sure file was found and read
	{
		printf("Unable to find file");
		return 0;
	}

	Min = findMin(numbers);
	Max = findMax(numbers);
	Avg = findAvg(numbers);

	writeOut( argv[2], Min, Max, Avg);
	free(numbers);//clear the maloc
	return 1;
}

int* readFile(char* inputFile )
{

	FILE* fp = fopen(inputFile, "r");
	if ( fp == NULL)
	{
		printf("Invalid file");
		return NULL;
	}//opens file and check to see if sucessful

	int * numbers = malloc( 10 * sizeof(int));//makes the array[10]

	int i = 0;
	for ( i = 0; i < 10; i++)
	{
		fscanf( fp, "%d", numbers+i );//moves number in file to the array[10]
	}
	fclose(fp);//closes file
	return numbers;//returns the point to an array[10]

}

void writeOut(char* outFile, int min, int max, int avg)
{

	FILE* fp = fopen(outFile, "w");
	if ( fp == NULL)
	{
		printf("Invalid File");
		return;
	}//opens file or creates file for writing , returns if error

	fprintf(fp, "Min: %d\nMax: %d\nAvg: %d", min, max, avg);//prints the file
	fclose(fp);//closes the file
}

int findMin( int* numbers)
{
	int low = *(numbers);//sets start point
	int i = 0;
	for ( i = 0; i < 10; i++)
	{
		if ( low > *(numbers + i))//goes through array comparing the numbeers
			low = *(numbers + i);
	}
	
	return low;
}

int findMax ( int* numbers)
{
	int max = *(numbers);
	int i = 0;
	for ( i = 0; i < 10; i++)
	{
		if ( max < *(numbers + i))//goes through the array comparing numbers
			max = *(numbers + i);
	}
		
	return max;
}

int findAvg( int* numbers )
{
	int sum = 0;
	int i = 0;
	for ( i = 0; i < 10; i++)
		sum += *(numbers+1);//makes a sum of the numbers

	return sum/10;//returns the avg
}
