#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

void swap(int *H, int x, int y)
{
    int temp = H[x];
    H[x] = H[y];
    H[y] = temp;
}

typedef struct
{
    int k, h;
} coppia;

coppia partition(int *a, int i, int j)
{
    int pivot = a[i];
    int k = i;
    int h = i + 1;
    for (int l = i + 1; l < j; l++)
    {
        if (a[l] == pivot)
        {
            swap(a, l, h);
            h++;
        }
        else if (a[l] < pivot)
        {
            swap(a, k, l);
            swap(a, h, l);
            k++;
            h++;
        }
    }
    return (coppia){.k = k, .h = h};
}

void quickSort(int *a, int i, int j)
{
    if (i >= j - 1)
    {
        return;
    }
    coppia c = partition(a, i, j);
    quickSort(a, i, c.k);
    quickSort(a, c.h, j);
}

void printArray(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
}

void division(int A[], int mediane[], int mIndex, int n, int i, int j)
{

    if (j < n)
    {
        quickSort(A, i, j+1); // ordina il blocco
        mediane[mIndex] = A[(i + j) / 2];
        division(A, mediane, mIndex+1, n, j + 1, j + 5);
    }
    else
    {
        quickSort(A, i, n);
        mediane[mIndex] = A[(i + n-1) / 2];

    }
}

int partitionMedian (int arr[], int n, int pivot)
{
    int i = 0;
    for (int j = 0; j < n; j++)
    {
        if (arr[j] < pivot)
        {
            
            swap(arr, i, j);
            i = i+1;
        }
        
    }
    swap(arr, i, n-1);
    return i;
    

}

int median(int *A, int n, int i, int j, int k)
{
    int numBlocchi;
    if (n%5 != 0) {
        numBlocchi = n/5+1;
    } else {
        numBlocchi = n/5;
    }

    int B[n];
    for (int i = 0; i < n; i++)
    {
        B[i] = A[i];
    }
    
    int mediane[numBlocchi];
    int mIndex = 0;
    division(B, mediane, mIndex, n, 0, 4);

    //printf("med: %d", mediane[numBlocchi/2]);
    int medOfMed = mediane[numBlocchi/2];

    //printArray(mediane, numBlocchi);

    int pivot = partitionMedian(A,n,medOfMed);
    //printArray(A,n);

    if (k == medOfMed)
    {
        return pivot;
    } else if (k < medOfMed)
    {
        return median(A,pivot,0,pivot-1,k);
    } else {
        return median(A,n-pivot-1,pivot+1, n-1, k);
    }
    


}

int main()
{
    int b[] = {90,2,8,10};
    int m = 4;
    printf("%d",median(b,m,0,m,8));


    int a[] = {4, 3, 7, 5, 1, 6, 2, 9, 15, 10,11,8};
    int n = 12;

    printf("\n%d",median(a,n,0,n-1,6));

    printf("\n");

    return 0;
}
