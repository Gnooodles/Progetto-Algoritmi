#include <stdio.h>
#include <stdlib.h>

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

// ritorna l'indice del nodo genitore
int parent(int i) {
    return (i - 1) / 2;
}

// ritorna l'indice del figlio sx
int left_child(int i) {
    return 2*i + 1;
}

// ritorna l'indice del figlio dx
int right_child(int i) {
    return 2*i + 2;
}

void swap(int H[], int x, int y) {
    int temp = H[x];
    H[x] = H[y];
    H[y] = temp;
}

// moves the item at position i of array a
// into its appropriate position
void heapify(int a[], int i, int n){
    // find left child node
    int left = left_child(i);

    // find right child node
    int right = right_child(i);

    // find the largest among 3 nodes
    int m = i;

    // check if the left node is larger than the current node
    if (left < n && a[left] < a[m]) {
        m = left;
    }

    // check if the right node is larger than the current node
    if (right < n && a[right] < a[m]) {
        m = right;
    }

    // swap the largest node with the current node 
    // and repeat this process until the current node is larger than 
    // the right and the left node
    if (m != i) {
        swap(a,m,i);
        heapify(a, m, n);
    }

}

// converts an array into a heap
void buildMinHeap(int a[], int n) {
    int i;
    for (i = n - 1; i >= 0; i--) {
        heapify(a, i, n);
    } 
}

// insert the item at the appropriate position
void insert(int a[], int data, int *n) {
    // first insert the time at the last position of the array 
    // and move it up
    a[*n] = data;
    *n = *n + 1;


    // move up until the heap property satisfies
    int i = *n - 1;
    int p = parent(i);
    while (i > 0 && a[i] < a[p]) {
        swap(a,i,p);
        i = p;
        p = parent(i);
    }
}

// deletes the max item and return
int extract_min(int a[], int *n) {
    int min_item = a[0];

    // replace the first item with the last item
    a[0] = a[*n - 1];
    *n = *n - 1;

    // maintain the heap property by heapifying the 
    // first item
    heapify(a, 0, *n);
    return min_item;
}

int getMin(int *H){
    return H[0];
}

int heapSelect(int a[], int n, int k){

    buildMinHeap(a, n);                                        //vettore per heap ausiliaria
    int H2[n];

    H2[0] = a[0];

    for(int i = 1; i < k; i++){
        int min = extract_min(H2,n);

        int *l = &(a[2*(min-*a)+1]);
        int *r = &(a[2*(min-*a)+2]);
        if(l-a < n){
            insert(H2,*l,&(i)-1);
        }
        if(r-a < n){
            insert(H2,*r,&(i)-1);
        }
    }
    return getMin(&H2);
}

void printArray(int *a, int n){
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
}


int main(){

    int *a = malloc(1000 * sizeof(int));

    int n = scanArray(a); //Leggo da una riga di input un array

    int k;
    scanf("%d", &k);

    int res = heapSelect(a,n,k);

    printf("%d\n", res);

    return 0;
}