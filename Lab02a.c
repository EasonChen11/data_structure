//
// Created by Eason chen on 2022/10/6.
//finish by Eason chen on 2022/10/7.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#define HOWMANY 100//how much of random number
#define filename_size 20

enum Choice{
    Random=1,Readfile
};
struct sc{
    int score;
    struct sc *next;
};
typedef struct sc scType;

void readfile_and_sorting(scType ** head,char *filename);

void random_data(char *filename);

void addScore_and_sorting(scType ** head, int score);

void printScore(scType *head);

void output_file(scType * head,char *filename);

int menu();

void read_filename(char * filename);

int main(){
    char input_filename[filename_size],output_filename[filename_size];
    scType *A=NULL;
    switch (menu()) {//choice the function
        case Random:
            random_data(input_filename);
            break;
        case Readfile:
            read_filename(input_filename);
            break;
    }
    readfile_and_sorting(&A,input_filename);
    output_file(A,output_filename);
}

void read_filename(char * filename) {//user input file name to read
    printf("Please enter the file name to open:(example:./data.txt)");
    scanf("%s",filename);//read output filename
    rewind(stdin);//clear
    assert(strlen(filename)<filename_size);//check the filename size legitimate
}

int menu() {//show the detail function
    int choice;
    while (1){
        printf("1.random a data and sorting. 2.read a file:");
        scanf("%d",&choice);
        rewind(stdin);
        if(choice==1 || choice==2){//check the choice is 1 or 2
            break;
        }else{
            printf("Please enter a choice 1 or 2\n");
        }
    }
    return choice;
}

void output_file(scType * head,char *filename) {//put the data to txt
    printf("Please enter the file name to open:(example:./output.txt)");
    scanf("%s",filename);//read output filename
    rewind(stdin);//clear
    assert(strlen(filename)<filename_size);//check the filename size legitimate
    printf("output file:%s\n",filename);
    FILE *output;
    if((output= fopen(filename,"w"))==NULL){//check file is legitimate
        fclose(output);
        printf("cancel\n");
        return;
    }
    scType *before;
    while (head){//read data before NULL
        fprintf(output,"%d ",head->score);//input to the file
        before=head;
        head=head->next;
        free(before);//free the memory
    }
    fclose(output);
    printf("finish\n");
}

void random_data(char *filename) {//create random numbers file
    printf("Please enter the file name to create:(example:./data.txt)");
    scanf("%s",filename);//input filename
    rewind(stdin);
    assert(strlen(filename)<filename_size);//check the filename size legitimate
    FILE *fp= fopen(filename,"w");
    if(fp==NULL){//check file is legitimate
        printf("cancel");
        return;
    }
    srand(time(0));
    int i=0;
    while (i++ <HOWMANY){
        int k=rand()%HOWMANY;
        fprintf(fp,"%d ",k);
    }//run HOWMANY times
    printf("\n");
    fprintf(fp,"\n");
    fclose(fp);
}

void readfile_and_sorting(scType ** head,char *filename) {//read numbers
    FILE *fp;
    if( (fp = fopen(filename,"r")) == NULL){//check open file legitimate
        fclose(fp);
        printf("%s is not exist\n",filename);
        exit(1);//exit code whether the file can't read
        return;
    }
    printf("read file:%s\ndata:\n",filename);
    int score;
    while ( fscanf(fp, "%d",&score)!=EOF){
        printf("%d ",score);
        addScore_and_sorting(head,score);//add number in the link list
    }
    fclose(fp);
    printf("\nsorting:\n");
    printScore(*head);
}

void addScore_and_sorting(scType ** head, int score) {
    scType *save= (scType*)malloc(sizeof (scType));
    save->score=score;
    save->next=NULL;//create a node
    if(*head==NULL){//first is NULL
        *head=save;
        return;
    }
    if(save->score < (*head)->score){//score is smallest
        save->next=*head;
        *head=save;
        return;
    }
    scType *now=(*head)->next,*before=*head;
    while (now){//find the node that score is bigger than score
        if(save->score < now->score){
            before->next=save;
            save->next=now;
            return;
        }
        before=now;
        now=now->next;
    }
    before->next=save;
}
void printScore(scType *head){//print data
    while (head){
        printf("%d ",head->score);
        head=head->next;
    }
    printf("\n");
}