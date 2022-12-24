#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 25

int BottomUp(int list[],int size);
int TopDown(int list[],int size);
int* Heapify(int list[],int size);

void Swap(int *a,int *b);
void PrintList(int list[],int size);
void RandomData();
int *ReadFile();

void HeapSort(int * heap);
/***from select sort, we need through all the value which in the list
 * to pick up the smallest value and its index.
 * So we use heap to find the biggest value. And put it to the end of list.
 * then, bottom up the heap inorder to find the second bigger value.
 * again and again, then we will get the sorting list.
 ***/

int BubbleSort(int * list);
int BubbleSortAddFrontCheck(int * list);
int BubbleSortAddStopCheck(int * list);

int main() {
    RandomData();

    printf("Heap Sort part\n");
    int *data=ReadFile();
    printf("Content of array:\n");PrintList(data,SIZE);
    printf("Processing Heap Sort:\n");
    int *heap=Heapify(data,SIZE);
    printf("heapify:\n");PrintList(heap,SIZE);
    HeapSort(heap);
    printf("Content of array:\n");PrintList(heap,SIZE);


    printf("\n\nBubble Sort part\n");
    int *data1= ReadFile();
    int *data2= ReadFile();
    int *data3= ReadFile();
    printf("Bubble sort : %d iterations\n", BubbleSort(data1));
    printf("Bubble sort improve 1 : %d iterations\n", BubbleSortAddFrontCheck(data2));
    printf("Bubble sort improve 2: %d iterations\n", BubbleSortAddStopCheck(data3));
    return 0;
}
void HeapSort(int * heap) {
    int unSortSize=SIZE,step=0;
    while (unSortSize>0){
        Swap(&heap[--unSortSize],&heap[0]);
        step+=TopDown(heap,unSortSize);
        if(unSortSize==0)break;
        printf("Reheaping with the smaller array ...\n");
        PrintList(heap,unSortSize);
    }
    printf("Heap Sort: %d steps.(not include heapify)\n\n",step);
}

//heap function
int BottomUp(int list[],int size){//(i-1)/2
    int newValueIndex=size-1,step=0;
    while(newValueIndex>0 && list[newValueIndex]>list[(newValueIndex-1)/2]) {
        Swap(&list[newValueIndex], &list[(newValueIndex - 1) / 2]);
        newValueIndex=(newValueIndex - 1) / 2;
        step++;
    }
    return step;
}
int TopDown(int list[],int size){//i*2+1 i*2+2
    int newValueIndex=0,step=0;
    while(newValueIndex*2+1<size){
        step++;
        int maxChildIndex;
        if(newValueIndex*2+2<size) {
            if (list[newValueIndex * 2 + 1] > list[newValueIndex * 2 + 2])maxChildIndex = newValueIndex * 2 + 1;
            else maxChildIndex = newValueIndex * 2 + 2;
        }else maxChildIndex= newValueIndex * 2 + 1;
        if(list[newValueIndex]<list[maxChildIndex]){
            Swap(&list[newValueIndex],&list[maxChildIndex]);
            newValueIndex=maxChildIndex;
        }
        else break;
    }
    return step;
}
int* Heapify(int list[],int size){
    int i,*heap,step=0;
    heap= (int*)malloc(sizeof (int)*size);
    for (i = 0; i < size; ++i) {
        heap[i]= list[i];
        step+=BottomUp(heap,i+1);
    }
    printf("Heapify took %d steps.\n\n",step);
    return heap;
}

//bubble sort
int BubbleSort(int * list) {//n+n+n+...+n (n items) -> O(n^2)
    PrintList(list,SIZE);
    int iterations=0;
    int i,j;
    for (i = SIZE-1; i >0; --i) {
        for (j = SIZE-1; j > 0; --j) {
            if(list[j]<list[j-1])Swap(&list[j], &list[j - 1]);
            iterations++;
        }
    }
    PrintList(list,SIZE);
    return iterations;
}
int BubbleSortAddFrontCheck(int * list) {//n+(n-1)+(n-2)+...+1 -> O(n^2)
    PrintList(list,SIZE);
    int iterations=0,frontUnsortIndex=0;
    while(frontUnsortIndex<SIZE-1){
        int i;
        for (i = 24; i > frontUnsortIndex; --i) {
            if(list[i]<list[i-1])Swap(&list[i], &list[i - 1]);
            iterations++;
        }
        frontUnsortIndex++;
    }
    PrintList(list,SIZE);
    return iterations;
}
int BubbleSortAddStopCheck(int * list) {//if not any swap -> stop sort
    PrintList(list,SIZE);
    int iterations=0,frontUnsortIndex=0;
    while(frontUnsortIndex<SIZE-1){
        int i,haveSwap=0;
        for (i = 24; i > frontUnsortIndex; --i) {
            if(list[i]<list[i-1]) { Swap(&list[i], &list[i - 1]);haveSwap=1; }
            iterations++;
        }
        if(!haveSwap)break;
        frontUnsortIndex++;
    }
    PrintList(list,SIZE);
    return iterations;
}

//general function
void Swap(int *a,int *b){
    int save=*a;
    *a=*b;
    *b=save;
}
void PrintList(int list[],int size){
    int i;
    for(i=0;i<size;i++){
        printf("%2d ",list[i]);
    }
    putchar('\n');
}
void RandomData(){
    srand(time(NULL));
    FILE *fp= fopen("Lab08b.txt","w");
    for (int j = 0; j < SIZE; ++j) {
        fprintf(fp,"%d ",rand()%SIZE);
    }
    fclose(fp);
}
int *ReadFile(){
    int *data=(int*) malloc(sizeof (int)* SIZE);
    FILE *fp= fopen("Lab08b.txt","r");
    for (int i = 0; i < SIZE; ++i) {
        fscanf(fp,"%d",data+i);
    }
    fclose(fp);
    return data;
}