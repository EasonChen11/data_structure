#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int cmp( const void *a,  const void*b){//compare the items in the list
    return *(int*)a- *(int*)b;//small to big
}
int main(){
    int items,time_range;
    printf("How many items:");
    scanf("%d",&items);//get number of items
    printf("What is the time range:");
    scanf("%d",&time_range);//get time range
    FILE *fp= fopen("./inputA.txt","w");//open file
    srand(time(NULL));//time reset
    int *pag=(int*) malloc(sizeof (int)*items);
    for(int i=0;i<items;i++){//create random number
        pag[i]=rand()%time_range;
    }
    qsort(pag, items,sizeof (int),cmp);//sorting
    for(int i=0;i<items;i++){
        fprintf(fp,"%d %d\n",i+1,pag[i]);//output the file
    }
    fclose(fp);//close the file
    free(pag);//free memory
}