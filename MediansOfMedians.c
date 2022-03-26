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

void partitionMedian (int arr[], int low, int high, int pivot)
{
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
 
    for (int j = low; j < high; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(arr, i,high);
        }
    }
    swap(arr,i,pivot);

}

void printArray(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
}


int medianOfMedian(int *A, int n, int k)
{
    // divide l'array in blocchi da 5
    int numeroBlocchi = n/5;
    
    if (n < 3)
    {
        printArray(A, n);
        return A[n/2];
        
        
    } else {
    
    int blocchi[n / 5][5];
    int indiceBlocco = 0;
    for (int i = 0; i < n; i = i + 5)
    {
        blocchi[indiceBlocco][0] = A[i];
        blocchi[indiceBlocco][1] = A[i + 1];
        blocchi[indiceBlocco][2] = A[i + 2];
        blocchi[indiceBlocco][3] = A[i + 3];
        blocchi[indiceBlocco][4] = A[i + 5];
        indiceBlocco++;
    }

    for (int i = 0; i < n / 5 - 1; i++)
    {
        quickSort(blocchi[i], 0, 5);
    }

    // se esiste un blocco di lunghezza minore di 5 allora faccio...
    if (n % 5 != 0)
    {
        for (int i = 0; i < n % 5; i++)
        {
            blocchi[indiceBlocco][i] = A[n - (n / 5) + i];
        }
        indiceBlocco++;
        quickSort(blocchi[n / 5], 0, n % 5);
    }

    // calcola le mediane dei blocchi da 5 e le salva in un Array
    int pivot=0;
    if (n % 5 == 0)
    {
        int mediane[indiceBlocco];
        for (int i = 0; i < indiceBlocco; i++)
        {
            mediane[i] = blocchi[i][5 / 2];
        }
        pivot = medianOfMedian(mediane, indiceBlocco, indiceBlocco/2);
    } else {
        int mediane[indiceBlocco];
        for (int i = 0; i < indiceBlocco-1; i++)
        {
            mediane[i] = blocchi[i][5 / 2];
        }
        mediane[indiceBlocco] = blocchi[indiceBlocco][n%5/2];
        pivot = medianOfMedian(mediane, indiceBlocco, indiceBlocco/2);
    }
    
    
    //partizionamento Array
    int numeriPiuPiccoli=0;
    for (int i = 0; i < n; i++)
    {
        if (A[i] < pivot)
        {
            numeriPiuPiccoli++;
        }
        
    }
    
    int low[numeriPiuPiccoli];
    int lowindex=0;
    int high[n-numeriPiuPiccoli];
    int highindex=0;

    for (int i = 0; i < n; i++)
    {
        if (A[i] < pivot)
        {
            low[lowindex] = A[i];
            lowindex++;
        } else {
            high[highindex] = A[i];
            highindex++;
        }
        
    }
    


    if (k < pivot)
    {
        return medianOfMedian(low,numeriPiuPiccoli,k);
    } else if (k > pivot) {
        return medianOfMedian(high,n-numeriPiuPiccoli,pivot-k-1);
    } else {
        return pivot;
    }
    
    }
    


}

int main(int argc, char const *argv[])
{
    int a[] = {1,2,3,4,5,1000,8,9,99};
    int n = 9;

    printf("\nmedians of medians di 0: %d", medianOfMedian(a,n,0));
    printf("\nmedians of medians di 1: %d", medianOfMedian(a,n,1));
    printf("\nmedians of medians di 7: %d", medianOfMedian(a,n,7));

    return 0;
}

