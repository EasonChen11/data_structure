//
// Created by ysche on 2022/10/13.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define filename_size 20

struct sc{
    int score;
    struct sc *next;
};
typedef struct sc scType;

void readfile_and_in_list(scType ** head,char *filename,int *count);
void Add_Data_to_List(struct sc **head,int score);
void printScore(scType *head);

void link_list_to_array(scType * head, int count, int **array);

int user_search(int * array,int count);

int binary_search(int * array, int target,int left,int right);

int main(){
    scType *datalist=NULL;
    char filename[filename_size];
    int count=0,*array;
    readfile_and_in_list(&datalist, filename,&count);
    link_list_to_array(datalist,count,&array);
    while (1){
        if(!user_search(array,count))
            return 0;
    }
}

int user_search(int * array,int count) {//read user need
    printf("enter which number wont to search : ");
    int number;
    scanf("%d",&number);
    if(number<0){
        printf("search cancel\n");
        return 0;
    }
    int ans=binary_search(array, number,0,count-1);//search
    if(ans==-1){
        printf("%d not found in list\n",number);
    }else{
        printf("%d is the %d index in list\n",number,ans);
    }
    return 1;
}

int binary_search(int array[], int target,int left,int right) {
    if (left>right){//not found
        return -1;
    }
    int mid = (left+right)/2;
    if(array[mid]==target){//find
        return mid+1;
    }else if(array[mid]>target){
        return binary_search(array, target,left,mid-1);//target < the number in array
    }else{
        return binary_search(array, target,mid+1,right);//target > the number in array
    }
}

void link_list_to_array(scType * head, int count, int **array) {//read link list to array
    *array = (int*)malloc(sizeof(int)*count);
    int index = 0;
    while (index<count){
        (*array)[index]=head->score;
        head=head->next;
        index++;
    }
}

void readfile_and_in_list(scType ** head,char *filename,int *count) {//read numbers
    printf("Please enter the file name to open:(example:./data.txt)");
    scanf("%s",filename);//read input filename
    rewind(stdin);//clear
    assert(strlen(filename)<filename_size);//check the filename size legitimate
    FILE *fp= fopen(filename,"r");
    if(fp==NULL){//check file is legitimate
        printf("cancel");
        return;
    }
    printf("read file:%s\ndata:\n",filename);
    int score;
    while ( fscanf(fp, "%d",&score)!=EOF){
        printf("%d ",score);
        Add_Data_to_List(head,score);//add number in the link list
        (*count)++;
    }
    fclose(fp);
    printf("\nsorting:\n");
    printScore(*head);
}
void Add_Data_to_List(scType ** head, int score) {
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