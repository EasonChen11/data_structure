#include <stdio.h>//1.read data/heapify/reheapup/reheapdown/heapsort/print array
struct heap_storage{
    char name[20];
    int number;
};
typedef struct heap_storage Heap;
int readFile(Heap heap[]);


void printdata(Heap heap[], int size);

void heapup(Heap heap[], int index);

void swap(Heap * pStorage, Heap * pStorage1);

void heapsort(Heap heap[], int size);

void heapdown(Heap * heap, int size);

int main() {
    Heap heap[100];
    int heapSize=readFile(heap);
    printdata(heap,heapSize);
    heapsort(heap,heapSize);
    printdata(heap,heapSize);
    return 0;
}

void heapsort(Heap heap[], int size) {
    while(size!=0){
        swap(&heap[0],&heap[--size]);
        heapdown(heap,size);
        printdata(heap,size);
    }
}

void heapdown(Heap * heap, int size) {
    int index=0,bigIndex;//leaf i*2+1 i*2+2
    while (index*2+1<size){//at least one leaf
        if(index*2+2<size) {
            if (heap[index * 2 + 1].number > heap[index * 2 + 2].number) bigIndex = index * 2 + 1;
            else bigIndex =index *2 +2;
        }else{bigIndex = index * 2 + 1;}
        if(heap[index].number>=heap[bigIndex].number){
            break;
        }else{
            swap(&heap[index],&heap[bigIndex]);
            index=bigIndex;
        }
    }
}

void printdata(Heap heap[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("[%s %d] ",heap[i].name,heap[i].number);
    }
    printf("\n");
}

int readFile(Heap heap[]) {
    char filename[20];
    printf("input file name:");
    scanf("%s",filename);
    FILE *fp= fopen(filename,"r");
    int index=0;
    while ( fscanf(fp,"%s",heap[index].name)!=EOF ){
        fscanf(fp,"%d",&heap[index].number);
        heapup(heap,index);
        index++;
    }
    fclose(fp);
    return index;
}

void heapup(Heap heap[], int index) {
    while(index!=0){
        if(heap[(index-1)/2].number<heap[index].number){
            swap(&heap[(index-1)/2],&heap[index]);
            index=(index-1)/2;
        }else{
            break;
        }
    }
}

void swap(Heap * pStorage, Heap * pStorage1) {
    Heap save =*pStorage;
    *pStorage=*pStorage1;
    *pStorage1=save;
}
