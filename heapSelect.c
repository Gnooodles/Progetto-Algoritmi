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
    int m;

    if (l < heapsize && H[l] > H[i]){
        m = l;
    }else{
        m = i;
    }

    if (r < heapsize && H[r] > H[m]){
        m = r;
    }

    if (m != i){
        swap2(H, i, m);
        heapify(H, m, heapsize);
    }
}

int *buildMaxHeap(int *H, int n){

    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(H, i, n);
    }
    return *H;
}

void heapInsert(int *H, int k, int heapsize){

    // int heapsize = scanArray(H);

    if( heapsize < sizeof(H) ){
        heapsize = heapsize + 1;
        H[heapsize - 1] = k;
        int i = heapsize;

        int p = parent(i);

        while( i > 0 && H[i] > H[p] ){
            swap2(H,i,p);
            i = parent(i);
        }
    }
}

int extractMaxHeap(int *H, int heapsize){

    if( heapsize > 0){

       int max = H[0];
       H[0] = H[heapsize - 1];
       heapify(H,0,heapsize);

        return max;

    } else {
        return INT_MIN;
    }
}

int heapSelect(int *a, int k, int heapsize){
    
    int b[5000];                                         //vettore per heap ausiliaria
    int *H1 = buildMaxHeap(a, heapsize);
    int *H2 = buildMaxHeap(b, 0);
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

    //Costruzione max heap
    buildMaxHeap(a,n);

    printArray(a, n);
    
    printf("\n");

    //Estrazione massimo
    printf("Il massimo è: ");
    int k = extractMaxHeap(a,n);
    printf("%d\n",k);
    printArray(a, n);

    printf("\n");

    //Inserimento chiave
    heapInsert(a, 10, n);
    printArray(a,n);

    printf("\n");

    return 0;
}