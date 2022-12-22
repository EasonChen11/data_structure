#include "lab08a.h"

int main() {
    int data[SIZE],size;
    size=Readfile(data);
    SelectionSort(data,size);
    return 0;
}

int Readfile(int data[]) {//read file list.txt and return list size
    FILE* fp= fopen("list.txt","r");
    int input,index=0;
    while ( fscanf(fp,"%d",&data[index++])!=EOF);
    fclose(fp);
    return index-1;
}

void SelectionSort(int list[], int size) {
    int index=0;
    while(index<size){//step by step check all the value in the list
        printf("step %d:\n",index);
        PrintList(list,size);
        int minValue=list[index],minIndex=index,i;//storage the min value and its index
        for (i = index+1; i < size; ++i) {//go through all the value behind of not sorting list
            if(minValue>list[i]){//if find the smaller value -> change value and index
                minIndex=i;
                minValue=list[minIndex];
            }
        }
        swap(&list[index],&list[minIndex]);//change the minimum value to the correct place
        index++;
    }
}

void PrintList(int list[], int size) {
    int i;
    for (i = 0; i < size; ++i) {//print all the data
        printf("%d ",list[i]);
    }
    putchar('\n');
}

void swap(int * a, int * b) {//change the two  value in the list
    int save=*a;
    *a=*b;
    *b=save;
}
