#include <stdio.h>

#define SIZE 100
typedef int aType;

int readArray (aType []);
void printArray (aType [], int);
void heapify(aType [], int);
void reheapup(aType [], int);
int FindingTheLargestDataItems(aType heap[], aType * count);
void reheapdown(aType [], aType);
void swap(aType *,aType *);
int main(void)
{
    aType count,repeatTimes;
	aType array[SIZE];//create array and set size
    aType maxNumber[SIZE];
	count=readArray(array);//count storage the least index of array
    if(count==0){//check the heap weather empty
        printf("heap is empty!\n");
        return 0;
    }

	printf("\nContent of array:\n");
	printArray(array, count);

	printf("\nProcessing heapify:\n");
	heapify(array,count);//set array -> heap
    printf("\nFind the k largest\n");
    while(1){
        printf("k=");//read the k
        scanf("%d", &repeatTimes);
        if(repeatTimes<=count)//repeat_time is legal
            break;
        else
            printf("k is out of range\n");
    }
    for (int i = 1; i <= repeatTimes; ++i) {
        printf("\nthe %d largest number: ",i);
        maxNumber[i-1]=FindingTheLargestDataItems(array, &count);//get the largest number in the heap
    }
    printf("k=%d :\n",repeatTimes);
    printArray(maxNumber,repeatTimes);//print the larger number list
}

int FindingTheLargestDataItems(aType heap[], aType * count) {//find the largest in the heap and remove it. then ,heapify.
    aType maxNumberInHeap=heap[0];
    printf("%d\n",maxNumberInHeap);//print larger number
    printf("heap:\n");
    printArray(heap,*count);//print heap before remove the largest number
    printf("remove largest number %d\n",heap[0]);
    heap[0]=heap[--(*count)];//change fist node and the least node and size of list minus 1
    reheapdown(heap, *count);
    printArray(heap,*count);
    return maxNumberInHeap;//return the largest number
}

void reheapdown(aType heap[], aType count) {
    aType i,start=0;
    for(i=start;i<count;){//top down
        printArray(heap,count);
        aType j;//storage the largest index of children
        if(heap[i*2+1]>=heap[i*2+2])//left child's number bigger than right child's number
            j=i*2+1;//storage left child's index
        else
            j=i*2+2;//storage right child's index
        if(heap[i]<heap[j] && j<count){//if father have children, and check father smaller than children
            swap(&heap[i],&heap[j]);//swap node
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

void swap(aType *small,aType *big){//change the two number in the list
    aType save=*small;
    *small=*big;
    *big=save;
}