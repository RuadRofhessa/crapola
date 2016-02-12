/*

Jason Ruther

*/
#include <stdio.h>
#include <stdlib.h>

typedef  struct  Points  {
	float  axis[2];// [0] X [1] Y (X,Y)
	int  id;  
}Points;

typedef  enum  {
	SortById,
	SortByXAxis
}SortType;
Points *fill_Array(char* filename, int* length);
/*
Parameters:
file name: The name of the input file
length: A pointer to the variable where the length of the array should be held
Return: An allocated and filled array of points
*/
void print_Set(Points *set, int number_of_points);
/*
Parameters:
set: an array of points
number_of_points: the length of the array
Return: None
*/

void merge_sort(Points *set, int len, SortType sort );
/*
Parameters:
set: an array of points
low : the lowest valid index to sort
high: the highest valid index to sort
number_of_points: the length of the array
sort: designates whether to sort on the Id or axis[0] (X)
Return: None
*/
void merge(Points *set, Points *temp, int left, int right, int rightEnd, SortType sort );

void mSort(Points *set, Points *temp, int left, int right, SortType sort );
/* I had to change this a bit to get my brain to work with it but i think its a bit better*/

int binary_search(Points *set, int number_of_points, int ID_Target);
/*
Parameters:
set: an array of points sorted on their Id’s
number_of_points: the length of the array
ID_Target: the Id to search for
Return: The index of the target Id if found, '-1' otherwise.
*/
void range_query_on_x(Points *set, int number_of_points, int mean, int std_dev);
/*
Parameters:
set: an array of points sorted on axis[0] (X) number_of_points: the length of the array
x: the axis[0] value at the middle of the range
distance: how far in either direction to search
Return: None

*/


int main(int argc, char* argv[]){
		
		if (argc != 2){
			printf("invalid usage: a.out <input file name>\n");
			return 1;
		}

		int len;
		Points* point_Array = fill_Array(argv[1], &len);
		if (point_Array == NULL){
			printf("check");
			return 1;
		}
		
		SortType sort_Type = SortById;

		printf("\nBefore ID sort\n");
		print_Set(point_Array, len);

		merge_sort( point_Array, len, sort_Type);

		printf("\nAfter ID sort\n");
		print_Set(point_Array, len);

		int ID_target = -1, index;
		while ( 0 == 0 ){
			printf( "\nChoose an ID to search for: ");
			scanf( "%d", &ID_target );
			
			if ( ID_target > -1 ){ 
				index = binary_search(point_Array, len, ID_target);
				break;
			}
			else
				printf("please input a positive value for point ID\n");
		}
		if ( index == -1 )
			printf("Unable to find ID %d\n\n", ID_target);
		else
			printf("ID %d (X,Y) (%f,%f)\n\n", ID_target, point_Array[index].axis[0], point_Array[index].axis[1]);

		sort_Type = SortByXAxis;
		merge_sort( point_Array, len, sort_Type);

		printf("Sorting by X axis\n");
		print_Set(point_Array, len);

		int std_dev = 0, mean = 0;
		while ( 0 == 0 ){

			printf("Choose a mean: ");
			scanf("%d", &mean);
			printf("\n");
			printf("Pick a stanard deviation: ");
			scanf("%d", &std_dev);
			printf("\n");

			if ( mean+std_dev > len || mean-std_dev < 0 )
				printf("the stanard diviation is beyond the range of the array\n");

			else if ( mean < 0 || std_dev < 0 )
				printf("please input a positive value for mean and standard deviation\n");

			else {
				range_query_on_x(point_Array, len, mean, std_dev);
				break;
			}

		}
		free(point_Array);
		return 0;
}
/*
1 Read  in  a  file  of  points,  each  point  has  an  ID,  an  x  and  y  coordinate  (axis[0] and  axis[1]  respectively)
2 merge sort  on  IDs
3 binary  search  for  an  ID
4 merge sort  again  on  the  X  axis 
5 perform  a  range  query  on  X with  user  input  of  a  point  X  and  a  distance  from that  point  X
*/

Points *fill_Array(char* filename, int* length){
	
	FILE* fp = fopen(filename, "r");
	if ( fp == NULL){
		printf("unable to open %s", filename);
		return NULL;
	}
	
	fscanf(fp, "%d", length);
	if (length <= 0){
		printf("invalid file size first character of file is the size of the set");
		return NULL;
	}
	Points* array = malloc(sizeof(Points) * *length);
	if (array == NULL){
		printf("unable to allocate memory");
		return NULL;
	}
	int i = 0;
	
	for ( i = 0; i < *length; i++)
		fscanf(fp, "%d %f %f", &(array+i)->id, &(array+i)->axis[0], &(array+i)->axis[1]);
		
	return array;

}

void print_Set(Points *set, int len){
	
	int i;
		
	printf("ID   X    Y\n");
	for (i = 0; i < len; i++){
		printf("%d %.2f %.2f\n", set[i].id, set[i].axis[0],set[i].axis[1]);
	}
}

void msort(Points *set, Points *temp, int left, int right, SortType sort)
{
	int center;
	if (left<right){
		center= (left+right)/2;
		msort(set, temp, left,     center, sort);
		msort(set, temp, center+1, right, sort);
		merge(set, temp, left, center+1, right, sort);
	}
}


void merge_sort(Points* set, int len, SortType sort){

	Points *temp = (Points *)malloc(sizeof(Points)*len);
	msort( set, temp, 0, (len-1) , sort);
	free(temp);

}
 
void merge(Points *set, Points *temp, int left, int right, int rightEnd, SortType sort)
{
	int i, num, temp_num, leftEnd= right-1;
	temp_num = left;
	num = rightEnd-left+1;
	if(sort == SortById ){
		while((left<=leftEnd) && (right<=rightEnd)){
			if(set[left].id <= set[right].id)
				temp[temp_num++]=set[left++];

			else
				temp[temp_num++]=set[right++];
		}
	}

	if(sort == SortByXAxis ){
		while((left<=leftEnd) && (right<=rightEnd)){
			if(set[left].axis[0] <= set[right].axis[0])
				temp[temp_num++]=set[left++];
			else
				temp[temp_num++]=set[right++];
		}
	}

	while( left <= leftEnd)
		temp[temp_num++]= set[left++];

	while(right<=rightEnd)
		temp[temp_num++]= set[right++];

	for( i = 1; i<=num; i++, rightEnd--)
		set[rightEnd]=temp[rightEnd];
	
} 

int binary_search(Points *set, int number_of_points, int ID_Target){

	int middle = 0, pass = 0, high = number_of_points-1, low = 0;

	while (low<= high){
		middle = (low+high)/2;

		if (low>high)
			return -1;

		if ( ID_Target == set[middle].id)
			return middle;

		else if ( ID_Target < set[middle].id )
			high = middle - 1;

		else
			low = middle + 1;
	}

	return -1; 
}

void range_query_on_x(Points *set, int number_of_points, int mean, int std_dev){
	int middle = 0, pass = 0, high = number_of_points=1, low = 0, found = 0;

	while (low<=high){
		middle = (low+high)/2;

		if (low>high){
			found = -1;
			break;
		}

		if ( mean == set[middle].axis[0] ){
			found = middle;
			break;
		}
		else if ( mean < set[middle].axis[0])
			high = middle - 1;

		else
			low = middle+1;
	}

	printf("The values within stanard deviation of %d from %d is\n", std_dev, mean);
	int i = 0;
	printf("under mean\n");
	for ( i = 1; i <= std_dev; i++ )
		printf("%d %f %f\n",set[mean-i].id, set[mean-i].axis[0], set[mean-i].axis[1]);

	printf("above mean\n");
	for ( i = 1; i <= std_dev; i++ )
		printf("%d %f %f\n", set[mean+i].id, set[mean+i].axis[0], set[mean+i].axis[1]);
			
}
