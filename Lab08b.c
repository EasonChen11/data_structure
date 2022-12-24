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

int BubbleSort(int * list);
int BubbleSortAddFrontCheck(int * list);
int BubbleSortAddStopCheck(int * list);

int main() {
    RandomData();//random number list put in Lab08b.txt

//heap sort part
    printf("Heap Sort part\n");
    int *data=ReadFile();//read lab08b.txt
    printf("Content of array:\n");PrintList(data,SIZE);//print origin contain
    printf("Processing Heap Sort:\n");
    int *heap=Heapify(data,SIZE);//let read list become heap
    printf("heapify:\n");PrintList(heap,SIZE);//print after heapify list
    putchar('\n');HeapSort(heap);
    printf("Content of array:\n");PrintList(heap,SIZE);//print after heap sort list

    printf("Processing Heap Sort to sort sorted list:\n");
    int *heap2=Heapify(heap,SIZE);//let read list become heap
    printf("heapify:\n");PrintList(heap,SIZE);//print after heapify list
    putchar('\n');HeapSort(heap2);
    printf("Content of array:\n");PrintList(heap2,SIZE);//print after heap sort list


    printf("\n\nBubble Sort part\n");
    int *data1= ReadFile();//read lab08b.txt
    int *data2= ReadFile();
    int *data3= ReadFile();
    printf("sort unsorted list:\n");
    printf("Bubble sort : %d iterations\n", BubbleSort(data1));//normal bubble sort
    printf("Bubble sort improve 1 : %d iterations\n", BubbleSortAddFrontCheck(data2));//improve 1 bubble sort
    printf("Bubble sort improve 2: %d iterations\n", BubbleSortAddStopCheck(data3));//improve 2 bubble sort
    printf("\nsort sorted list:\n");
    printf("Bubble sort : %d iterations\n", BubbleSort(data1));//normal bubble sort
    printf("Bubble sort improve 1 : %d iterations\n", BubbleSortAddFrontCheck(data2));//improve 1 bubble sort
    printf("Bubble sort improve 2: %d iterations\n", BubbleSortAddStopCheck(data3));//improve 2 bubble sort
    return 0;
}
void HeapSort(int * heap) {
/***from select sort, we need through all the value which in the list
 * to pick up the smallest value and its index.
 * So we use heap to find the biggest value. And put it to the end of list.
 * then, bottom up the heap inorder to find the second bigger value.
 * again and again, then we will get the sorting list.
 ***/
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
int BottomUp(int list[],int size){//(i-1)/2 let the least value go to its correct place
    int newValueIndex=size-1,step=0;
    while(newValueIndex>0 && list[newValueIndex]>list[(newValueIndex-1)/2]) {//check the new value whether bigger than its father and index is legal
        Swap(&list[newValueIndex], &list[(newValueIndex - 1) / 2]);//go up
        newValueIndex=(newValueIndex - 1) / 2;//update index
        step++;
    }
    return step;
}
int TopDown(int list[],int size){//i*2+1 i*2+2 when we delete the biggest value, then we put the least value to the top.use top down reheap
    int newValueIndex=0,step=0;
    while(newValueIndex*2+1<size){//check the node have child
        step++;
        int maxChildIndex;
        if(newValueIndex*2+2<size) {//find the biggest children
            if (list[newValueIndex * 2 + 1] > list[newValueIndex * 2 + 2])maxChildIndex = newValueIndex * 2 + 1;
            else maxChildIndex = newValueIndex * 2 + 2;
        }else maxChildIndex= newValueIndex * 2 + 1;
        if(list[newValueIndex]<list[maxChildIndex]){//if the node is the biggest value -> cancel top down, not swap node and continue top down
            Swap(&list[newValueIndex],&list[maxChildIndex]);//swap to node
            newValueIndex=maxChildIndex;//update index
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
    printf("Heapify took %d steps.\n",step);
    return heap;
}

//bubble sort
int BubbleSort(int * list) {//n+n+n+...+n (n items) -> O(n^2)
    PrintList(list,SIZE);
    int iterations=0;
    int i,j;
    for (i = SIZE-1; i >0; --i) {//find the smaller value
        for (j = SIZE-1; j > 0; --j) {//put the smaller value to front of list
            if(list[j]<list[j-1])Swap(&list[j], &list[j - 1]);
            iterations++;//storage step times
        }
    }
    PrintList(list,SIZE);
    return iterations;
}
int BubbleSortAddFrontCheck(int * list) {//n+(n-1)+(n-2)+...+1 -> O(n^2)
/***
 * every time, we will put the smallest value which is in the leftover list to front of list.
 * do not check all the list every time.
 * we only need check the not sort part, because the smallest value we have put it to  front of list.
 * ***/
    PrintList(list,SIZE);
    int iterations=0,frontUnsortIndex=0;
    while(frontUnsortIndex<SIZE-1){
        int i;
        for (i = SIZE-1; i > frontUnsortIndex; --i) {
            if(list[i]<list[i-1])Swap(&list[i], &list[i - 1]);
            iterations++;
        }
        frontUnsortIndex++;
    }
    PrintList(list,SIZE);
    return iterations;
}
int BubbleSortAddStopCheck(int * list) {//if not any swap -> stop sort
/***
 * is similar BubbleSortAddFrontCheck function.
 * in this function, add the check item.
 * this item will storage whether have change in this travel time.
 * if this time don't have change, it show that this list complete sorting.
 * so, use this method sort the sorted list will spend less steps.
 * ***/
    PrintList(list,SIZE);
    int iterations=0,frontUnsortIndex=0;
    while(frontUnsortIndex<SIZE-1){
        int i,haveSwap=0;
        for (i = SIZE-1; i > frontUnsortIndex; --i) {
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
void Swap(int *a,int *b){//change two values which in the same list
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
void RandomData(){//create random number list and put in Lab08b.txt
    srand(time(NULL));
    FILE *fp= fopen("Lab08b.txt","w");
    for (int j = 0; j < SIZE; ++j) {
        fprintf(fp,"%d ",rand()%SIZE);
    }
    fclose(fp);
}
int *ReadFile(){//read number list from Lab08b.txt
    int *data=(int*) malloc(sizeof (int)* SIZE);
    FILE *fp= fopen("Lab08b.txt","r");
    for (int i = 0; i < SIZE; ++i) {
        fscanf(fp,"%d",data+i);
    }
    fclose(fp);
    return data;
}