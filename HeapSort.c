#include "heap.h"
//use heap sort
void HeapSort(int * heap);

/***from select sort, we need through all the value which in the list
 * to pick up the smallest value and its index.
 * So we use heap to find the biggest value. And put it to the end of list.
 * then, bottom up the heap inorder to find the second bigger value.
 * again and again, then we will get the sorting list.
 ***/
 int main() {
    int data[]={7,14,14,19,8,2,21,3,20,24,14,10,16,8,2,22,16,21,8,7,16,1,3,18,15},size= SIZE;
    printf("Content of array:\n");PrintList(data,size);
    printf("Processing Heap Sort:\n");
    int *heap=Heapify(data,size);
    printf("heapify:\n");PrintList(heap,size);
    HeapSort(heap);
    printf("Content of array:\n");PrintList(heap,size);
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
