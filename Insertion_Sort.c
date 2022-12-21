#include <stdio.h>
#define SIZE 50000

int Readfile(int data[]);

void InsertionSort(int list[], int size);

void PrintList(int list[], int size);

int main() {
    int data[SIZE],size;
    size=Readfile(data);
    InsertionSort(data, size);
    return 0;
}

int Readfile(int data[]) {
    FILE* fp= fopen("list.txt","r");
    int input,index=0;
    while ( fscanf(fp,"%d",&data[index++])!=EOF);
    fclose(fp);
    return index-1;
}

void InsertionSort(int list[], int size) {
    int index=0;
    while(index<size){
        int insertValue=list[index],i=index-1;
        while ( i >=0 && insertValue<list[i]) {
                list[index]=list[i--];
        }
        printf("step %d:\n",index++);
        PrintList(list,size);
    }
}

void PrintList(int list[], int size) {
    int i;
    for (i = 0; i < size; ++i) {
        printf("%d ",list[i]);
    }
    putchar('\n');
}
