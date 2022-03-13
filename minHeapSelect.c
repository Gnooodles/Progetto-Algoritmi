#include <stdio.h>
#include <stdlib.h>

int INT_MIN = -9999;

// Codice per leggere un Array da input

#define MAX_LINE_SIZE 1000 // maximum size of a line of input

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

void buildMinHeap(int *H, int n)
{
    for (int i = n - 1; i >= 0; i--)
    {
        minHeapify(H, i, n);
    }
}

void insert(int *H, int k, int heapsize)
{
    heapsize = heapsize + 1;
    H[heapsize - 1] = k;
    int i = heapsize - 1;

    int p = parent(i);

    while (i > 0 && H[i] < H[p])
    {
        swap2(H, i, p);
        i = p;
        p = parent(i);
    }
}

int extractMin(int *H, int heapsize)
{
    if (heapsize >= 0)
    {
        swap2(H, 0, heapsize - 1);
        heapsize = heapsize - 1;
        minHeapify(H, 0, heapsize);

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
// HEAP SELECT

int heapSelect(int *A, int n, int k)
{
    //creo H1 min heap da vettore A
    buildMinHeap(A,n);

    //creo H2 min heap che contiene solo radice di H1
    int *H2 = malloc(n * sizeof(int));
    int n2 = 0;
    //H2[0] = getMin(A);
    insert(H2,getMin(A),n2);
    n2++;

    //iterazioni
    for (int i = 0; i < k; i++)
    {
        //estrae la radice di H2
        //printf("\n -->h2 prima estraz ");
        //printArray(H2,n2);
        int min = extractMin(H2,n2);
        n2--;
        //printf("\n -->h2 dopo estraz");
        //printArray(H2,n2);

        //inserisco i figli sinistrto e destro in H2
        if (left(i) < n)
        {
            insert(H2,A[left(i)],n2);
            n2++;
            //printf("\n -->h2 dopo ins sx ");
            //printArray(H2,n2);
        }
        
        if (right(i) < n)
        {
            insert(H2,A[right(i)],n2);
            n2++;
            //printf("\n -->h2 dopo ins dx ");
            //printArray(H2,n2);
        }
    }

    //prendo il minimo di H2 che corrisponde al k-esimo elemento se ordinassi l'array
    return getMin(H2);
    


}




int main(int argc, char const *argv[])
{
    /* PROVE MIN HEAP
    // int a[1000];
    // usando un allocazione di memoria per l'array in modo che sia dinamico
    int *a = malloc(1000 * sizeof(int));

    int n = scanArray(a); // Leggo da una riga di input un array
    // printf("%d\n", n);
    buildMinHeap(a, n); // funziona
    printArray(a, n);


        a[4] = 12121;
        printf("\n");
        printArray(a, n+1);
        */

    // inserisco 1 nella heap [2 3 6 4]
    /*
    insert(a, 1, n);
    n++;
    printf("\n");
    printArray(a, n);

    printf("\n%d", extractMin(a,n));
    n--;
    printf("\n");
    printArray(a, n);

    */

    // HEAP SELECT
    int *a = malloc(1000 * sizeof(int));
    int n = scanArray(a); // Leggo da una riga di input un array
    int k;
    scanf("%d", &k);

    int res = heapSelect(a,n,k-1);

    printf("il %d-esimo elemento è:%d", k, res);


    return 0;
}
