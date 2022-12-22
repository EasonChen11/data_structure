#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 24
void Swap(int *a,int *b){
    int save=*a;
    *a=*b;
    *b=save;
}
void PrintList(int list[],int size){
    int i;
    for(i=0;i<size;i++){
        printf("%d ",list[i]);
    }
    putchar('\n');
}

int *RandomData(){
    srand(time(NULL));
    int *list= (int*)malloc(sizeof (int)*SIZE);
    for (int j = 0; j < SIZE; ++j) {
        list[j]=rand()%SIZE;
    }
    return list;
}