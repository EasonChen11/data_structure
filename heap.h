#include "generalfunction.h"

void BottomUp(int list[],int size){//(i-1)/2
    int newValueIndex=size-1;
    while(newValueIndex>0 && list[newValueIndex]>list[(newValueIndex-1)/2]) {
        Swap(&list[newValueIndex], &list[(newValueIndex - 1) / 2]);
        newValueIndex=(newValueIndex - 1) / 2;
    }
}

void TopDown(int list[],int size){//i*2+1 i*2+2
    int newValueIndex=0;
    while(newValueIndex*2+1<size){
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
}

int* Heapify(int list[],int size){
    int i,*heap;
    heap= (int*)malloc(sizeof (int)*size);
    for (i = 0; i < size; ++i) {
        heap[i]= list[i];
        BottomUp(heap,i+1);
    }
    return heap;
}