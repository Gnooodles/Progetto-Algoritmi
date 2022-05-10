#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void swap2(int *H, int x, int y) {
    int temp = H[x];
    H[x] = H[y];
    H[y] = temp;
}

//-------------------------------------------------------------------------------------------------------

int left(int i){
 return 2*i+1;
}

int right(int i){
 return 2*i+2;
}

int parent(int i){
 return (int)((i-1)/2);
}


void heapify(int *H, int i, int heapsize){

    //int heapsize = scanArray(H);

    int l = left(i);
    int r = right(i);
    int m=i;

    if (l < heapsize && H[l] > H[m]){
        m = l;
    }

    if (r < heapsize && H[r] > H[m]){
        m = r;
    }

    if (m != i){
        swap2(H, m, i);
        heapify(H, m, heapsize);
    }
}

void buildMaxHeap(int *H, int n){

    for (int i = n / 2 +1 ; i >= 0; i--){
        heapify(H, i, n);
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
            swap2(H,i,p);
            i = parent(i);
        }
    }
}

int extractMaxHeap(int *H, int heapsize){

    if( heapsize >= 0){
        swap2(H,0,heapsize);
        heapsize = heapsize - 1;
        heapify(H,0, heapsize);

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

double duration(struct timespec start, struct timespec end) {
    return end.tv_sec - start.tv_sec
         + ((end.tv_nsec - start.tv_nsec ) / (double) 1000000000.0);
}
double getResolution(){
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    do {
        
        clock_gettime(CLOCK_MONOTONIC, &end);
    } while (duration(start, end) == 0.0);
    return duration(start, end);
}

int main(){
    /*
    int a[1000];

    int n = scanArray(a); //Leggo da una riga di input un array

    buildMaxHeap(a,n); //funziona

    printArray(a, n);
    
    //printf("\n%d", parent(5));
    printf("\n");
    //swap2(a,0,1);
    printf("%d", extractMaxHeap(a,n));

    printf("\n");
    //printArray(a, n);*/




    return 0;
}