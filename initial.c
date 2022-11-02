#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define name_size 20
#define room_size 20
struct data{
    int phone_number;
    char name[name_size];
    char room[room_size];
    struct data *next;
};
typedef struct data dType;

void readfile(dType ** head);

void sort_list(dType ** head, dType * new_node);

void print_list(dType * head);

int find_name(dType * head);

int main() {
    dType *head=NULL;
    readfile(&head);
    printf("Content of list ordered according to name:\n");
    print_list(head);
    putchar('\n');
    while(find_name(head));
    return 0;
}

int find_name(dType * head) {
    printf("Enter name: ");
    char input_name[name_size];
    scanf("%s",input_name);
    if(strcmp(input_name,"done.")==0)
        return 0;
    while(head){
        if(strcmp(head->name,input_name)==0)
            break;
        head=head->next;
    }
    if(head){
        printf("phone: %d; Room: %s\n\n",head->phone_number,head->room);
    } else{
        printf("not found\n\n");
    }
    return 1;
}

void print_list(dType * head) {
    while (head){
        printf("%d %s %s\n",head->phone_number,head->name,head->room);
        head=head->next;
    }
}

void readfile(dType ** head) {
    FILE *fp= fopen("./inputA.txt","r");
    if(fp==NULL){
        printf("file can't open\n");
        exit(1);
    }
    int phone_number_carry;
    while( fscanf(fp,"%d",&phone_number_carry)!=EOF){
        dType *new_node=(dType*) malloc(sizeof (dType));
        new_node->phone_number=phone_number_carry;
        fscanf(fp,"%s",new_node->name);
        fscanf(fp,"%s",new_node->room);
        new_node->next=NULL;
        sort_list(head,new_node);
    }
}

void sort_list(dType ** head, dType * new_node) {
    if(*head==NULL){
        *head=new_node;
        return;
    }
    if(strcmp((*head)->name,new_node->name)>0){
        new_node->next=(*head);
        (*head)=new_node;
        return;
    }
    dType *now=(*head)->next,*before=(*head);
    while (now){
        if(strcmp(now->name,new_node->name)>0)
            break;
        before=now;
        now=now->next;
    }
    before->next=new_node;
    new_node->next=now;
}
