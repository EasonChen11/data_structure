#include "heap.h"
//use heap sort
void HeapSort(int * heap, int size);

/***from select sort, we need through all the value which in the list
 * to pick up the smallest value and its index.
 * So we use heap to find the biggest value. And put it to the end of list.
 * then, bottom up the heap inorder to find the second bigger value.
 * again and again, then we will get the sorting list.
 ***/
 int main() {
    int *data=RandomData(),size= SIZE;
    printf("original list:\n");PrintList(data,size);
    int *heap=Heapify(data,size);
    printf("heapify:\n");PrintList(heap,size);
    HeapSort(heap,size);
    printf("Content of array:\n");PrintList(heap,size);
    return 0;
}

void HeapSort(int * heap, int size) {
    int unSortSize=size;
    while (unSortSize>0){
        Swap(&heap[--unSortSize],&heap[0]);
        TopDown(heap,unSortSize);
        if(unSortSize==0)break;
        printf("Reheaping with the smaller array ...\n");
        PrintList(heap,unSortSize);
    }
}
