#include "lab08a.h"

int main() {
    int data[SIZE],size;
    size=Readfile(data);
    InsertionSort(data, size);
    return 0;
}

int Readfile(int data[]) {//read file list.txt and return list size
    FILE* fp= fopen("list.txt","r");
    int input,index=0;
    while ( fscanf(fp,"%d",&data[index++])!=EOF);
    fclose(fp);
    return index-1;
}

void InsertionSort(int list[], int size) {
    int index=0;//first node
    while(index<size){//until end of list
        int insertValue=list[index],i=index;//storage which vale we want to insert and i is the check lab in the list
        while ( i >0 && insertValue<=list[i-1]) {//if lab in the list and the before vale bigger than insert value
                list[i]=list[i-1];//go to the next step to storage
                i--;
        }
        list[i]=insertValue;//put insert vale in the correct sit
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
