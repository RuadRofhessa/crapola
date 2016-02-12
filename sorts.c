#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

typedef struct SortStat{
	unsigned long int comparisons;
	unsigned long int swaps;
	long double duration;
}SortStat;

typedef struct Arrays{
	int* first;//bubble_Sort
	int* second;//selection_Sort
	int* third;//insertion_Sort
} Arrays;

Arrays* generate_Arrays( int len);

SortStat* bubble_Sort( int array[], int len);

SortStat* selection_Sort(int array[], int len);

SortStat* insertion_Sort( int array[], int len);

void free_data(Arrays* array);

#define Eten 10
#define Ehundred 100
#define Ethousand 1000
#define Etenthousand 10000

void main(void){

	srand(time(NULL));

	
	Arrays* ranArrayten = generate_Arrays(Eten);
	if (ranArrayten == NULL)
		return;
		
	Arrays* ranArrayhund = generate_Arrays(Ehundred);
	if (ranArrayhund == NULL)
		return;
		
	Arrays* ranArraythousand = generate_Arrays(Ethousand);
	if (ranArraythousand == NULL)
		return;
		
	Arrays* ranArraytenthous = generate_Arrays(Etenthousand);
	if (ranArraytenthous == NULL)
		return;
	
	printf("\nFor Array size 10\n");
	
	SortStat* Stat = bubble_Sort( ranArrayten->first, Eten);
	printf("Bubble sort made %lu comparisons, %lu swaps, and took %le\n", Stat->comparisons, Stat->swaps, Stat->duration);
	
	Stat = selection_Sort(ranArrayten->second, Eten);
	printf("Selection sort made %lu comparisons, %lu swaps, and took %le\n", Stat->comparisons, Stat->swaps, Stat->duration);
	
	Stat = insertion_Sort(ranArrayten->third, Eten);
	printf("Insertion sort made %lu comparisons, %lu swaps, and took %le\n", Stat->comparisons, Stat->swaps, Stat->duration);
	
	
	
	free(Stat);
	Stat = bubble_Sort( ranArrayhund->first, Ehundred);
	printf("\nFor Array size 100\n");
	printf("Bubble sort made %lu comparisons, %lu swaps, and took %le\n", Stat->comparisons, Stat->swaps, Stat->duration);
	
	Stat = selection_Sort(ranArrayhund->second, Ehundred);
	printf("Selection sort made %lu comparisons, %lu swaps, and took %le\n", Stat->comparisons, Stat->swaps, Stat->duration);
	
	Stat = insertion_Sort(ranArrayhund->third, Ehundred);
	printf("Insertion sort made %lu comparisons, %lu swaps, and took %le\n", Stat->comparisons, Stat->swaps, Stat->duration);

	
	free(Stat);
	Stat = bubble_Sort( ranArraythousand->first, Ethousand);
	printf("\nFor Array size 1000\n");
	printf("Bubble sort made %lu comparisons, %lu swaps, and took %le\n", Stat->comparisons, Stat->swaps, Stat->duration);
	Stat = selection_Sort(ranArraythousand->second, Ethousand);
	printf("Selection sort made %lu comparisons, %lu swaps, and took %le\n", Stat->comparisons, Stat->swaps, Stat->duration);
	Stat = insertion_Sort(ranArraythousand->third, Ethousand);
	printf("Insertion sort made %lu comparisons, %lu swaps, and took %le\n", Stat->comparisons, Stat->swaps, Stat->duration);

	
	free(Stat);
	Stat = bubble_Sort( ranArraytenthous->first, Etenthousand);
	printf("\nFor Array size 10000\n");
	printf("Bubble sort made %lu comparisons, %lu swaps, and took %le\n", Stat->comparisons, Stat->swaps, Stat->duration);
	Stat = selection_Sort(ranArraytenthous->second, Etenthousand);
	printf("Selection sort made %lu comparisons, %lu swaps, and took %le\n", Stat->comparisons, Stat->swaps, Stat->duration);
	Stat = insertion_Sort(ranArraytenthous->third, Etenthousand);
	printf("Insertion sort made %lu comparisons, %lu swaps, and took %le\n", Stat->comparisons, Stat->swaps, Stat->duration);




	free(ranArrayten);
	free_data(ranArrayhund);
	free_data(ranArraythousand);
	free_data(ranArraytenthous);
	free(Stat);

}

Arrays* generate_Arrays(int len){

	if ( len <= 0){
		printf("Invalid Array Size");
		return NULL;
	}
	Arrays* ranArrays = malloc( sizeof(Arrays));
	if( ranArrays == NULL){
		printf("Unable to allocate memory for struct");
		return NULL;
	}
	int i;
	ranArrays->first = malloc( sizeof(int) * len);
	if ( ranArrays->first == NULL ){
		printf("Unable to allocate memory for int arrays");
		free(ranArrays);
		return NULL;
	}
	ranArrays->second = malloc( sizeof(int) * len);
	if( ranArrays->second == NULL){
		printf("Unable to allocate memory for int arrays");
		free(ranArrays);
		free(ranArrays->first);
		return NULL;
	}
	ranArrays->third = malloc ( sizeof(int) * len);
	if( ranArrays->second == NULL){
		printf("Unable to allocate memory for int arrays");
		free(ranArrays);
		free(ranArrays->first);
		free(ranArrays->second);
		return NULL;
	}
	for( i = 0; i < len; i++){
		*(ranArrays->first) = rand();
		*(ranArrays->second) = rand();
		*(ranArrays->third) = rand();
	}

	return ranArrays;
}

SortStat* bubble_Sort(int* input, int size){
	
	SortStat *s = malloc(sizeof(SortStat));
	s->comparisons = 0;
	s->swaps = 0;
	s->duration = 0;
	int i, j, swaps, swap;
	for ( i = 0; i < size; i++){
		swaps = 0;
		for( j = 0; j < size; j++){
			s->comparisons += 1;
			if ( *(input+i) < *(input+j)){				
				s->swaps++;
				swap = *(input+i);
				*(input+i) = *(input+j);
				*(input+j) = swap;
				swaps++;
			}
		}
		s->comparisons++;
		if ( swaps <= 0)
			break;
	}
	return s;
}

SortStat* selection_Sort( int* input, int size)
{
	SortStat* s = malloc(sizeof(SortStat));
	s->comparisons = 0;
	s->swaps = 0;
	s->duration = 0;
	
	int i = 0, j = 0, min = 0, swap = 0;
	for( i = 0; i < size; i++){
		min = i;
		for( j = i+1; j < size; j++)
		s->comparisons++;
			if( *(input+j) < *(input+min))
				min = j;
		s->comparisons++;
		if( min != i){
			s->swaps++;
			swap = *(input+i);
			*(input+i) = *(input+min);
			*(input+min) = swap;
		}
	}
	
	return s;
}

SortStat* insertion_Sort(int* input, int size){
	
	SortStat* s = malloc( sizeof(SortStat));;
	s->comparisons = 0;
	s->swaps = 0;
	s->duration = 0;
	
	int i = 0, j = 0, element = 0;
	
	for( i = 1; i < size; i++){
		element = input[i];
		s->comparisons++;
		j = i;
		while( j > 0 && input[j-1] > element){
			s->swaps++;
			s->comparisons++;
			input[j] = input[j-1];
			j -= 1;
		}
		s->swaps++;
		input[j] = element;
	}
	return s;
}


void free_data( Arrays* arrays){	
	free(arrays->first);
	free(arrays->second);
	free(arrays->third);
	free(arrays);
}
