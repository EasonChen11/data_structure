#include "lab08a.h"

int main(){
    FILE* fp= fopen("list.txt","w");
    srand(time(NULL));
    for (int i = 0; i < SIZE; ++i) {
        fprintf(fp,"%d ",rand()%SIZE);
    }
    fclose(fp);
}