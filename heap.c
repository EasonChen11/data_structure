#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
typedef int aType;

int readArray (aType []);
void printArray (aType [], int);
void heapify(aType [], int);
void reheapup(aType [], int);
void FindingTheLargestDataItems(int [], aType *);
void reheapdown(aType [], aType);
void swap(aType *,aType *);
int main(void)
{
    aType count,repeatTimes;
	aType array[SIZE];//create array and set size

	count=readArray(array);//count storage the least index of array
	printf("\nContent of array:\n");
	printArray(array, count);

	printf("\nProcessing heapify:\n");
	heapify(array,count);//set array -> heap
    printf("How many times:");
    scanf("%d",&repeatTimes);
    while (repeatTimes--)FindingTheLargestDataItems(array,&count);
}

void FindingTheLargestDataItems(aType heap[], aType * count) {
    if(*count==0){
        printf("heap is empty!\n");
        return;
    }
    printf("heap:\n");
    printArray(heap,*count);
    printf("Largest number: %d\n",heap[0]);
    heap[0]=heap[*count-1];
    reheapdown(heap, --(*count));
    printArray(heap,*count);
}

void reheapdown(aType heap[], aType count) {
    aType i,start=0;
    for(i=start;i<count;){//up down
        printArray(heap,count);
        aType j;
        if(heap[i*2+1]>=heap[i*2+2])
            j=i*2+1;
        else
            j=i*2+2;
        if(heap[i]<heap[j] && j<count){
            swap(&heap[i],&heap[j]);
            i=j;
        }else
            break;
    }
}

int readArray (aType a[])//read from file and put data into array
{
	char filename[20];
	FILE * fp;
    aType count=0;

	printf("Please enter a filename: ");
	scanf ("%s",filename);//enter file name
	fp = fopen (filename, "r");//open file to read

	while (fscanf(fp, "%d", &a[count++]) != EOF && count+1<SIZE);//read number from the file and put into array and check input number not overflow

	fclose(fp);//close file

	return (count-1);//return the least index of array
}

void printArray (aType a[], aType count)//print contain number in array
{
    aType i;

	for (i=0; i<count; ++i)//print data in the list step by step
		printf ("%d ", a[i]);
	printf("\n");
}

void heapify(aType H[], aType size)//from file array put into heap
{
    aType i;

	for (i=1;i<size; ++i){//i from 1 to start because avid i-1<0 first node is H[0]
		if (H[i] > H[(i-1)/2])//if the father point is smaller than child node(now we at the i index in the array)
			reheapup(H, i);
		printArray(H,size);
	}
}

void reheapup(aType H[], aType start)//change node and create heap
{
    aType i, temp;

	for (i=start; i>0; i=(i-1)/2)//we at the node which we want to change the place of array and step by step go to father node to check
		if (H[i] > H[(i-1)/2]) {//if the father point is smaller than child node(now we at the i index in the array)
			temp=H[(i-1)/2];//swap father node and child node
			H[(i-1)/2] = H[i];
			H[i] = temp;
		}
}

void swap(aType *small,aType *big){
    aType save=*small;
    *small=*big;
    *big=save;
}