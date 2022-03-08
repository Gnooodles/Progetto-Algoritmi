#include <stdio.h>
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

int main(int argc, char const *argv[])
{
    int s[10000];
    int n = scanArray(s);
    int k;
    scanf("%d", &k);
    int i = quickSelect(s, 0, n, k);
    printf("%d", i);

    return 0;
}
