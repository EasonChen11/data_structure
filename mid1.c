#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<assert.h>
#define name_size 20
#define room_size 20
struct data{
    int phonenumber;
    char name[name_size];
    char room[room_size];
    struct data *next;
};
typedef struct data dType;

void readfile(dType **normal_list);
void connect_normallist(dType **normal_list,dType *new_node);
void print_list(dType *list);
void link_orderlist(dType *normal_list,dType **order_list);
void connect_orderlist(dType **order_list,dType *new_node);
void putfile(dType *order_list);
void freedata(dType *list);
//try to ADT code

int main()
{
    dType *normal_list=NULL,*order_list=NULL;
    readfile(&normal_list);
    print_list(normal_list);
    link_orderlist(normal_list,&order_list);
    //putchar('\n');print_list(order_list);
    putfile(order_list);
    freedata(normal_list);
    freedata(order_list);
    return 0;
}

void readfile(dType **normal_list){
    FILE *infp=fopen("./inputA.txt","r");
    if(infp==NULL){
        printf("can't open file\n");
        exit(1);
    }
    dType carry;
    while(fscanf(infp,"%d",&carry.phonenumber)!=EOF){
        fscanf(infp,"%s",carry.name);
        assert(strlen(carry.name)<name_size);
        fscanf(infp,"%s",carry.room);
        assert(strlen(carry.room)<room_size);
        carry.next=NULL;
        dType *new_node=(dType*)malloc(sizeof(dType));//create a node
        (*new_node)=carry;
        connect_normallist(normal_list,new_node);//connect list
    }
}

void connect_normallist(dType **normal_list,dType *new_node){
    if((*normal_list)==NULL){//if list is empty
        (*normal_list)=new_node;
        return;
    }
    dType *now =(*normal_list);
    while(now->next){//find the least node
        now=now->next;
    }
    now->next=new_node;
}

void print_list(dType *list){//print data
    while(list){
        printf("%d %s %s\n",list->phonenumber,list->name,list->room);
        list=list->next;
    }
}

void link_orderlist(dType *normal_list,dType **order_list){
    while(normal_list){
        dType *new_node=(dType*)malloc(sizeof(dType));//create a new node
        (*new_node)=(*normal_list);//copy data
        new_node->next=NULL;
        connect_orderlist(order_list,new_node);
        normal_list=normal_list->next;
    }
}

void connect_orderlist(dType **order_list,dType *new_node){
    if((*order_list)==NULL){//if list is empty
        (*order_list)=new_node;
        return;
    }
    if((*order_list)->phonenumber>new_node->phonenumber){//if new node phone number smaller than first node
        new_node->next=(*order_list);
        (*order_list)=new_node;
        return;
    }
    dType *now=(*order_list)->next,*before=(*order_list);
    while(now){
        if(now->phonenumber>new_node->phonenumber) break;//find the node which phone number smaller than new node
        before=now;
        now=now->next;
    }
    before->next=new_node;
    new_node->next=now;
}

void putfile(dType *order_list){//print to file
    FILE *outfp=fopen("./outputB.txt","w");
    if(outfp==NULL){//check open successfully
        printf("can't open file\n");
        exit(1);
    }
    while(order_list){//node by node print to file
        fprintf(outfp,"%d %s %s\n",order_list->phonenumber,order_list->name,order_list->room);
        order_list=order_list->next;
    }
}

void freedata(dType *list){//using recursive free memory
    if(list==NULL){
        free(list);
        return;
    }
    freedata(list->next);
    free(list);
}
