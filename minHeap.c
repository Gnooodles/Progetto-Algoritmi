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

void fixUp(int *H, int i, int heapsize) {
    int p = parent(i);
    if (i<=0)
    {
        return;
    } else if (H[p] > H[i]) {
        swap2(H,p,i);
        fixUp(H,p, heapsize);
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

void insert2(int *H, int k, int heapsize) {
    heapsize = heapsize + 1;
    H[heapsize - 1] = k;
    fixUp(H,heapsize - 1,heapsize);
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



int main(int argc, char const *argv[])
{
    
    int *a = malloc(1000 * sizeof(int));
    int n = scanArray(a); // Leggo da una riga di input un array

    buildMinHeap(a,n);
    printf("\n\n\n\n");
    printArray(a, n);

    extractMin(a,n);
    n--;
    printf("\n");
    printArray(a,n);


    return 0;
}
