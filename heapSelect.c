#include <stdio.h>
#include <stdlib.h>

int INT_MIN = -9999;

// Codice per leggere un Array da input

#define MAX_LINE_SIZE 1000 // maximum size of a line of input

int scanArray(int *a){
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

void swap(int *x, int *y){
    int t;
    t = *x;
    *x = *y;
    *y = t;
}

//-------------------------------------------------------------------------------------------------------

void heapify(int *H, int i){

    int heapsize = scanArray(H);

    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int m;

    if (l <= heapsize && H[l] > H[i]){
        m = l;
    }else{
        m = i;
    }

    if (r <= heapsize && H[r] > H[m]){
        m = r;
    }

    if (m != i){
        swap(&m, &i);
        heapify(H, m);
    }
}

void buildMaxHeap(int *H, int n){

    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(H, i);
    }
}

void heapInsert(int *H, int k){

    int heapsize = scanArray(H);

    if( heapsize < sizeof(H) ){
        heapsize = heapsize + 1;
        H[heapsize] = k;
        int i = heapsize;

        int p = parent(i);

        while( i > 0 && H[i] > H[p] ){
            swap(&i,&p);
            i = parent(i);
        }
    }
}

int extractMaxHeap(int *H){
    int heapsize = scanArray(H);

    if( heapsize > 0){
        swap(1,&heapsize);
        heapsize = heapsize - 1;
        heapify(H,1);

        return H[heapsize + 1];
    } else {
        return INT_MIN;
    }
}

void heapSelect(int *H, int n, int k){

    //TODO:
    
}
//----------------------------------------------------------------------------------------------------------------------

void printArray(int *a, int n){
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
}

int main(){
    int a[1000];

    int n = scanArray(a); //Leggo da una riga di input un array

    build(a,n);

    printArray(a, n);

    return 0;
}