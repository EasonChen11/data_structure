/*** This program generates HOWMANY numbers of integers and strings of variable sizes ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HOWMANY 10000

void rand_string(int, char []);

int main(void)
{
    FILE * fp;
    int i=0;
    char str[7]; // at most 6 characters

    srand(time(0));

    fp = fopen("random_data.txt", "w");
    while (i++ < HOWMANY)
        fprintf(fp, "%d ", rand()%HOWMANY);
    fclose(fp);

    fp = fopen("random_string.txt", "w");
    i = 0;
    while (i++ < HOWMANY) {
        rand_string(1+rand()%6, str); // strlen: 1..6
        fprintf(fp, "%s ", str);
    }
    fclose(fp);
}

void rand_string(int length, char str[])
{
    int i=0;

    while (i < length)
        str[i++] = 'a'+rand()%26;
    str[i] = '\0';
}
