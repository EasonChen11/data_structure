#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
typedef int aType;

int readArray (aType []);
void printArray (aType [], int);
void heapify(aType [], int);
void reheapup(aType [], int);


int main(void)
{
	int count;
	aType array[SIZE];//create array and set size

	count=readArray(array);//count storage the least index of array
	printf("\nContent of array:\n");
	printArray(array, count);

	printf("\nProcessing heapify:\n");
	heapify(array,count);//set array -> heap
}

int readArray (aType a[])//read from file and put data into array
{
	char filename[20];
	FILE * fp;
	int count=0;

	printf("Please enter a filename: ");
	scanf ("%s",filename);//enter file name
	fp = fopen (filename, "r");//open file to read

	while (fscanf(fp, "%d", &a[count++]) != EOF);//read number from the file and put into array

	fclose(fp);//close file

	return (count-1);//return the least index of array
}

void printArray (aType a[], int count)//print contain number in array
{
	int i;

	for (i=0; i<count; ++i)//print data in the list step by step
		printf ("%d ", a[i]);
	printf("\n");
}

void heapify(aType H[], int size)//from file array put into heap
{
	int i;

	for (i=1;i<size; ++i){
		if (H[i] > H[(i-1)/2])
			reheapup(H, i);
		printArray(H,size);
	}
}

void reheapup(aType H[], int start)//
{
	int i, temp;

	for (i=start; i>0; i=(i-1)/2)
		if (H[i] > H[(i-1)/2]) {
			temp=H[(i-1)/2];//swap father node and child node
			H[(i-1)/2] = H[i];
			H[i] = temp;
		}
}

