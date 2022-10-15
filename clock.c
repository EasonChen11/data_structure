/** This program performs a search and measure how much time it takes **/
/** two experiments:
    1. searching for a random key
    2. searching for a key not in list
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10
#define SIZE 64000

void SeqSearch(int [], int, int);

int main(void)
{
    FILE * ifp;
    int i, key, data[SIZE];
    clock_t start_time, elapsed_time;

    // random_data.txt with SIZE number of data
    ifp = fopen("random_data.txt", "r");
    for (i=0; i<SIZE; i++)
        fscanf(ifp, "%d", &data[i]);
    fclose(ifp);

    srand(time(0));  // to be used by random key

    //repeat for different sizes of data
    for (i=1; i<=MAX; ++i){
        key = rand()%SIZE;  // key is 0 .. SIZE-1

        // clock the start time
        // repeat the search many times
        // clock the end time
        // print size vs. time

        start_time = clock();

/*** if time is too small to check,
     then use this instead of just calling search() once
		//for (int j=0; j<MAX*1000; ++j)
			search (data, key, 1000*i);
****/
        SeqSearch (data, key, 1000*i);

        elapsed_time = clock() - start_time;

        printf("Size: %d; Time used: %lf\n\n",
               1000*i, (double) elapsed_time/CLOCKS_PER_SEC);
    }

    // using a key not in the list
    putchar('\n');
    putchar('\n');
    for (i=1; i<=MAX; ++i){
        key = SIZE;  // key is not in the list

        start_time = clock();
        search (data, key, 1000*i);
        elapsed_time = clock() - start_time;

        printf("Size: %d; Time used: %lf\n\n",
               1000*i, (double) elapsed_time/CLOCKS_PER_SEC);
    }

}

void SeqSearch(int data [], int key, int limit)
{
    int i=0;
    while (i<limit && data[i] != key)
        ++i;
    if (i == limit) printf("key: %d not found\n", key);
    else printf("key: %d found at: %d\n", key, i);
}
