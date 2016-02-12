#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct point{//(X,Y) cords of graph
	int x;
	int y;
}point;

struct point* read_file(char* file_name, int size);//opens file_name and makes an array[size] and returns a pointer of point type
double distance(point pointone, point pointtwo);//calculates the distance from (X1, Y1) to (X2, Y2) and returns the value
point* sort(struct point*, int size);//sorts the points in the array by distance from the origin (0,0). takes an array of point and size
void print_points(struct point* array, int size);//prints the points in the array


int main ( int argc, char **argv )
{

	if (argc != 3 ){
		printf("insuficent arrguments, ./a.out <number of points> <filename>");
		return 0;
	}
	int size = atoi(argv[1]);//covert char to int

	point* pairArray = read_file( argv[2], size);

	printf("before sort\n");
	print_points(pairArray, size);

	pairArray = sort( pairArray, size );
	if ( pairArray == NULL ){
		printf("Unable to allocate memory");
		return 0;
	}
	
	printf("after sort\n");
	print_points(pairArray, size);

	free(pairArray);
	return 1;
}

point* read_file(char * filename, int size)
{
	FILE* fp = fopen(filename, "r");//opens the file
	if ( fp == NULL ){
		printf("Unable to open or find file");
		return NULL;
	}

	point* pointArray = malloc( sizeof(point)* size);
	
	int i = 0;
	for ( i = 0; i < size; i++)//reads x y cords from a file
		fscanf( fp, "%d %d", &((pointArray+i)->x), &((pointArray+i)->y));

	fclose(fp);	
	return pointArray;
}

point* sort( point* pointArray, int size)
{
	point origin = {0, 0}, temp = {0, 0};

	int i = 0, j = 0;
	for ( i = 0; i < size; i++ )//bubble short
		for ( j = 0; j < size; j++)
			if ( distance(origin, *(pointArray+j)) > distance(origin, *(pointArray+1+j)) )
			{	
				temp = *(pointArray+j);
				*(pointArray+j) = *(pointArray+j+1);
				*(pointArray+j+1) = temp;

			}

	return pointArray;
}

double distance( point one, point two )
{
	double distance = sqrt(pow(((double)one.x-(double)two.x),2)+pow(((double)one.y-(double)two.y),2));//sqrt((X1-X2)^2+(Y1-Y2)^2) distance between points
	return distance;
}

void print_points(point* array, int size)
{
	int i = 0;
	for ( i = 0; i < size; i++ )
		printf("(%d, %d)\n", (array+i)->x, (array+i)->y);

}
