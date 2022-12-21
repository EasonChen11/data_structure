#include <stdio.h>
#define SIZE 50000

int Readfile(int data[]);

void SelectionSort(int list[], int size);

void swap(int * a, int * b);

void PrintList(int list[], int size);

int main() {
    int data[SIZE],size;
    size=Readfile(data);
    SelectionSort(data,size);
    return 0;
}

int Readfile(int data[]) {
    FILE* fp= fopen("list.txt","r");
    int input,index=0;
    while ( fscanf(fp,"%d",&data[index++])!=EOF);
    fclose(fp);
    return index-1;
}

void SelectionSort(int list[], int size) {
    int index=0;
    while(index<size){
        printf("step %d:\n",index);
        PrintList(list,size);
        int minValue=list[index],minIndex=index,i;
        for (i = index+1; i < size; ++i) {
            if(minValue>list[i]){
                minIndex=i;
                minValue=list[minIndex];
            }
            swap(&list[index],&list[minIndex]);
            index++;
        }
    }
}

void PrintList(int list[], int size) {
    int i;
    for (i = 0; i < size; ++i) {
        printf("%d ",list[i]);
    }
    putchar('\n');
}

void swap(int * a, int * b) {
    int save=*a;
    *a=*b;
    *b=save;
}
