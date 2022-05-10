#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define INT_MIN -999999
#define MAX_LINE_SIZE 10000

int scanArray(int *a)
{ // legge un array di numeri dall'input
    // scan line of text
    char line[MAX_LINE_SIZE];
    scanf("%[^\n]", line);

    // convert text into array
    int size = 0, offset = 0, numFilled, n;
    do
    {
        numFilled = sscanf(line + offset, "%d%n", &(a[size]), &n);
        if (numFilled > 0)
        {
            size++;
            offset += n;
        }
    } while (numFilled > 0);

    return size;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
}

int partition(int *a, int p, int q) // PARTITION GIUSTO
{
    int i, x;
    i = p - 1;
    x = a[q - 1];
    for (int j = p; j < q; j++)
    {
        if (a[j] <= x)
        {
            i = i + 1;
            swap(&a[j], &a[i]);
        }
    }

    return i;
}

int quickSelect(int *a, int i, int j, int k)
{

    if (k - 1 < i || k - 1 >= j)
    {
        return INT_MIN;
    }
    else if (i == j - 1 && k - 1 == i)
    {
        return a[k - 1];
    }
    else
    {

        int m = partition(a, i, j);

        if (k - 1 < m)
        {
            return quickSelect(a, i, m, k);
        }
        else
        {
            return quickSelect(a, m, j, k);
        }
    }
}



int randint(int n) {
  
    

    // Chop off all of the values that would cause skew...
    int end = RAND_MAX / n; // truncate skew

    end *= n;

    // ... and ignore results from rand() that fall above that limit.
    // (Worst case the loop condition should succeed 50% of the time,
    // so we can expect to bail out of this loop pretty quickly.)
    int r;
    while ((r = rand()) >= end);

    return r % n;
  
}

int *creaArray(int lunghezza) {
    int *a = malloc(lunghezza * sizeof(int));
    for (int i = 0; i < lunghezza; i++)
    {
        a[i] =  randint(100000);
    }
    return a;
    
}

double duration(struct timespec start, struct timespec end) {
    return end.tv_sec - start.tv_sec
         + ((end.tv_nsec - start.tv_nsec ) / (double) 1000000000.0);
}
double getResolution(int *a, int n, int k){
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    do {
        quickSelect(a,0,n,k);
        clock_gettime(CLOCK_MONOTONIC, &end);
    } while (duration(start, end) == 0.0);
    return duration(start, end);
}



int main(int argc, char const *argv[])
{
    /*
    int s[10000];
    int n = scanArray(s);
    int k;
    scanf("%d", &k);
    int i = quickSelect(s, 0, n, k);
    printf("%d", i);
    */

    int *a = creaArray(1000000000);
    int k = randint(100000);
    printf("%f\n", getResolution(a,1000000000,k));

    return 0;
}
