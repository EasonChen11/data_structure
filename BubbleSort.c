#include "generalfunction.h"

int BubbleSort(int * list);


int main(){
    int data1[]= {4,5,8,12,13,15,7,8 ,19, 24 ,13, 21 ,14 ,6 ,13 ,1 ,18 ,12 ,18 ,5 ,8 ,2 ,24 ,7 ,17};
    int data2[]= {4,5,8,12,13,15,7,8 ,19, 24 ,13, 21 ,14 ,6 ,13 ,1 ,18 ,12 ,18 ,5 ,8 ,2 ,24 ,7 ,17};
    printf("Bubble sort : %d iterations\n", BubbleSort(data1));
    printf("Improve Bubble sort : %d iterations\n", BubbleSort(data1));

}

int BubbleSort(int * list) {//n+(n-1)+(n-2)+...+1 -> O(n^2)
    PrintList(list,SIZE);
    int iterations=0,frontUnsortIndex=0;
    while(frontUnsortIndex<SIZE-1){
        int i;
        for (i = 24; i > frontUnsortIndex; --i) {
            if(list[i]<=list[i-1])Swap(&list[i], &list[i - 1]);
            iterations++;
        }
        frontUnsortIndex++;
    }
    PrintList(list,25);
    return iterations;
}
