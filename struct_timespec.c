/** This program uses struct timespec to do more precise time measurement **/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#define HAVE_STRUCT_TIMESPEC

#define MAX 10
#define SIZE 10000
int cmp(const void *a, const void *b);
void readfile(int [],int []);
void Sequential_search_workspace(int [], struct timespec, struct timespec);
void Sequential_search  (int [], int, int);
void Sentinel_search_workspace(int [],struct timespec,struct timespec);
void Sentinel_search (int [], int, int);
void Binary_search_recursion_workspace(int [],struct timespec,struct timespec);
int Binary_search_recursion(int [], int ,int ,int );
void Binary_search_loop_workspace(int [],struct timespec,struct timespec);
int Binary_search_loop(int [], int,int,int);

int main(void)
{
    int data[SIZE+1],sorting_data[SIZE];
    data[SIZE]=-1;
    struct timespec tt1, tt2;
    readfile(data,sorting_data);
    //close file
    srand(time(0));
    // Sequential searching for a fixed key which is not in list
    printf("Sequential searching:\n");
    Sequential_search_workspace(data,tt1,tt2);
    putchar('\n');
    // Sentinel searching for a fixed key which is not in list
    printf("Sentinel searching:\n");
    Sentinel_search_workspace(data,tt1,tt2);
    putchar('\n');
    //sorting list
    qsort(sorting_data,SIZE+1, sizeof(int),cmp);
    // Binary search using recursion for a fixed key which is not in list
    printf("Binary search using recursion:\n");
    Binary_search_recursion_workspace(sorting_data,tt1,tt2);
    putchar('\n');
    printf("Binary search using loop:\n");
    Binary_search_loop_workspace(sorting_data,tt1,tt2);
    putchar('\n');
}


int cmp(const void *a, const void *b) {
    return (*((int*)a))-(*((int*)b));
}

void readfile(int data[], int sorting_data[]){
    FILE *ifp = fopen("random_data.txt", "r");
    for (int i=0; i<SIZE; ++i){
        fscanf(ifp, "%d", &data[i]);
        sorting_data[i] = data[i];
    }
    fclose(ifp);

}

void Sequential_search_workspace(int data[],struct timespec tt1,struct timespec tt2){
    FILE *Sequential_search_time=fopen("Sequential_search_time.txt", "w");
    for (int i=1; i<=MAX; ++i){
        clock_gettime(CLOCK_REALTIME, &tt1);
        Sequential_search (data, SIZE, 1000*i);
        clock_gettime(CLOCK_REALTIME, &tt2);
        printf("Size: %d; time: %ld\n",
               1000*i, tt2.tv_nsec - tt1.tv_nsec);
        fprintf(Sequential_search_time,"%d\t%ld\n",
                1000*i, tt2.tv_nsec - tt1.tv_nsec);
    }
    fclose(Sequential_search_time);
}
void Sequential_search(int data [], int key, int limit)
{
    int i=0;
    while (i<limit && data[i] != key)
        ++i;
    if (i == limit) printf("Key %d not found\n", key);
    else printf("Key %d found at %d\n", key, i);
}

void Sentinel_search_workspace(int data[],struct timespec tt1,struct timespec tt2){
    FILE *Sentinel_search_time=fopen("Sentinel_search_time.txt", "w");
    for (int i=1; i<=MAX; ++i){
        clock_gettime(CLOCK_REALTIME, &tt1);
        Sentinel_search(data, SIZE, 1000*i);
        clock_gettime(CLOCK_REALTIME, &tt2);
        printf("Size: %d; time: %ld\n",
               1000*i, tt2.tv_nsec - tt1.tv_nsec);
        fprintf(Sentinel_search_time,"%d\t%ld\n",
                1000*i, tt2.tv_nsec - tt1.tv_nsec);
    }
    fclose(Sentinel_search_time);
}
void Sentinel_search(int data [], int key, int limit)
{
    int i=0;
    int lest = data[limit];
    while (data[i] != lest){
        if (data[i] == key){
            printf("Key %d found at %d\n", key, i);
            return;
        }
        ++i;
    }
    printf("Key %d not found\n", key);
}

void Binary_search_recursion_workspace(int sorting_data[],struct timespec tt1,struct timespec tt2){
    FILE *BinarySearch_recursion_time=fopen("BinarySearch_recursion_time.txt", "w");
    for (int i=1; i<=MAX; ++i){
        clock_gettime(CLOCK_REALTIME, &tt1);
        int ans=Binary_search_recursion(sorting_data,SIZE,0,1000*i);//search
        if(ans==-1){
            printf("Key %d not found\n",SIZE);
        }else{
            printf("Key %d found at %d\n",SIZE,ans);
        }
        clock_gettime(CLOCK_REALTIME, &tt2);
        printf("Size: %d; time: %ld\n",
               1000*i, tt2.tv_nsec - tt1.tv_nsec);
        fprintf(BinarySearch_recursion_time,"%d\t%ld\n",
                1000*i, tt2.tv_nsec - tt1.tv_nsec);
    }
    fclose(BinarySearch_recursion_time);
}
int Binary_search_recursion(int sorting_data[], int target,int left,int right) {
    if (left>right){//not found
        return -1;
    }
    int mid = (left+right)/2;
    if(sorting_data[mid]==target){//find
        return mid+1;
    }else if(sorting_data[mid]>target){
        return Binary_search_recursion(sorting_data, target,left,mid-1);//target < the number in array
    }else{
        return Binary_search_recursion(sorting_data, target,mid+1,right);//target > the number in array
    }
}

void Binary_search_loop_workspace(int sorting_data[],struct timespec tt1,struct timespec tt2){
    FILE *BinarySearch_loop_time=fopen("BinarySearch_loop_time.txt", "w");
    for (int i=1; i<=MAX; ++i){
        clock_gettime(CLOCK_REALTIME, &tt1);
        int ans=Binary_search_loop(sorting_data,SIZE,0,1000*i);//search
        if(ans==-1){
            printf("Key %d not found\n",SIZE);
        }else{
            printf("Key %d found at %d\n",SIZE,ans);
        }
        clock_gettime(CLOCK_REALTIME, &tt2);
        printf("Size: %d; time: %ld\n",
               1000*i, tt2.tv_nsec - tt1.tv_nsec);
        fprintf(BinarySearch_loop_time,"%d\t%ld\n",
                1000*i, tt2.tv_nsec - tt1.tv_nsec);
    }
    fclose(BinarySearch_loop_time);
}
int Binary_search_loop(int sorting_data[], int target,int left,int right) {
    int mid;
    while (left <= right){
        mid = (left+right)/2;
        if (sorting_data[mid] == target) {
            return mid;
        }else if (target < sorting_data[mid]) {
            right = mid - 1;
        }else
            left = mid+1;
    }
    return -1;
}
