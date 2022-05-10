#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int INT_MIN = -9999;

// Codice per leggere un Array da input

#define MAX_LINE_SIZE 10000 // maximum size of a line of input

int scanArray(int *a)
{
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

void swap(int *x, int *y)
{
    int t;
    t = *x;
    *x = *y;
    *y = t;
}

void swap2(int *H, int x, int y)
{
    int temp = H[x];
    H[x] = H[y];
    H[y] = temp;
}

void printArray(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
}

//-------------------------------------------------------------------------------------------------------

int left(int i)
{
    return 2 * i + 1;
}

int right(int i)
{
    return 2 * i + 2;
}

int parent(int i)
{
    return (int)((i - 1) / 2);
}

void minHeapify(int *H, int i, int heapsize)
{
    int l = left(i);
    int r = right(i);
    int m = i;

    if (l < heapsize && H[l] < H[m])
    {
        m = l;
    }

    if (r < heapsize && H[r] < H[m])
    {
        m = r;
    }

    if (m != i)
    {
        swap2(H, m, i);
        minHeapify(H, m, heapsize);
    }
}

void minHeapify2(int *H2, int i, int heapsize, int *A)
{
    int l = left(i);
    int r = right(i);
    int m = i;

    if (l < heapsize && A[H2[l]] < A[H2[m]])
    {
        m = l;
    }

    if (r < heapsize && A[H2[r]] < A[H2[m]])
    {
        m = r;
    }

    if (m != i)
    {
        swap2(H2, m, i);
        minHeapify2(H2, m, heapsize, A);
    }
}

void fixUp(int *H, int i, int heapsize)
{
    int p = parent(i);
    if (i <= 0)
    {
        return;
    }
    else if (H[p] > H[i])
    {
        swap2(H, p, i);
        fixUp(H, p, heapsize);
    }
}

void buildMinHeap(int *H, int n)
{
    for (int i = n - 1; i >= 0; i--)
    {
        minHeapify(H, i, n);
    }
}

void insert(int *H, int k, int heapsize, int *A)
{
    heapsize = heapsize + 1;
    H[heapsize - 1] = k;
    int i = heapsize - 1;

    int p = parent(i);

    while (i > 0 && A[H[i]] < A[H[p]])
    {
        swap2(H, i, p);
        i = p;
        p = parent(i);
    }
}

int extractMin(int *H, int heapsize, int *A)
{
    if (heapsize >= 0)
    {
        swap2(H, 0, heapsize - 1);
        heapsize = heapsize - 1;
        minHeapify2(H, 0, heapsize, A);

        return H[heapsize];
    }
    else
    {
        return INT_MIN;
    }
}

int getMin(int *H)
{
    return H[0];
}

//----------------------------------------------------------------
// HEAP SELECT GIUSTO 



int heapSelect(int *A, int n, int k)
{
    // creo H1 min heap da vettore A
    buildMinHeap(A, n); // theta(n)

    // creo H2 min heap che contiene solo radice di H1
    int *H2 = malloc(10000 * sizeof(int));
    int n2 = 0;
    H2[0] = 0;
    n2++;

    // iterazioni
    for (int i = 0; i < k; i++) // theta(k)
    {
        // estrae la radice di H2
        int index = extractMin(H2, n2, A);
        n2--;

        // inserisco i figli sinistro e destro del nodo appena estratto in H2
        if (left(index) < n)
        {
            insert(H2, left(index), n2,A);
            n2++;
        }

        if (right(index) < n)
        {
            insert(H2, right(index), n2,A);
            n2++;
        }
    }


    return A[getMin(H2)];
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
        heapSelect(a,n,k);
        clock_gettime(CLOCK_MONOTONIC, &end);
    } while (duration(start, end) == 0.0);
    return duration(start, end);
}


int main(int argc, char const *argv[])
{
    
    /*
    // HEAP SELECT
    int *a = malloc(10000 * sizeof(int));
    int n = scanArray(a); // Leggo da una riga di input un array
    int k;
    scanf("%d", &k);

    int res = heapSelect(a, n, k-1);

    printf("%d", res);
    */
    int *a = creaArray(1000000000);
    int k = randint(100000);
    printf("%f\n", getResolution(a,1000000000,k));
    //printArray(a, 10000);

    return 0;
}
