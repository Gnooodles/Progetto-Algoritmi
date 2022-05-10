#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>
// Codice per leggere un Array da input

#define MAX_LINE_SIZE 100000 // maximum size of a line of input

int scanArray(int *a, int maxLen){
	char str[ MAX_LINE_SIZE];
	scanf("%[^\n]", str);
	int i = 0, j = 0, res, offset, value;
	do {
		res = sscanf(str +j, "%i %n", &value, &offset);
		if (res == 1) {
			a[i++] = value;
			j = j + offset;
		}

	} while ((res == 1) && ( i  < maxLen));
	return i; //numero di elementi nell array
}
void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void insertionSort(int *array, int from, int to){
	for(int  i = from + 1; i <= to; i++){
		for(int j = i; j > from; j--){
			if(array[j] < array[j-1]){
				swap(array+j, array +j-1);
			}
		}
	}
}





int partition(int *a, int left, int right, int pivotIndex, int n){
	int pivotValue = a[pivotIndex];
	swap(a+pivotIndex,a+right);
	int storeIndex = left;
	for(int i = left; i < right; i++){
		if(a[i] < pivotValue){
			swap(a+storeIndex, a+i);
			storeIndex++;
		}
	}
	int storeIndexEq = storeIndex;
	for(int i = storeIndex; i < right; i++){
		if(a[i] == pivotValue){
			swap(a+storeIndexEq, a+i);
			storeIndexEq++;
		}
	}
	swap(a+right, a+storeIndexEq);
	if(n < storeIndex){
		return storeIndex;
	}
	if(n <= storeIndexEq){
		return n;
	}
	return storeIndexEq;

}


int partition5(int *a, int left, int right){
	int i = left + 1;
	while(i <= right){
		int j = i;
		while( j > left && a[j-1] > a[j]){
			swap(a+j-1, a+j);
			j = j -1;
		}
		i = i+1;
	}
	return floor((left + right)/2);
}

void findAndSwapLast(int *array, int p, int q, int n){
	int i = p;
	while(array[i] != n && i <= q){
		i++;
	}
	if (i <= q){
		swap(array +i, array + q);
	}
}


int getMedianVal(int * array, int p, int q){
	int size = (q - p + 1 + 4) / 5; // ceil((q-p+1)/5.0)
	int *auxArray = malloc(sizeof(int)*size);
	int j = 0 , i = 0;
	for(i = p; i <= q ; i = i + 5){
		int top = i+4;
		if(top <= q){
			insertionSort(array, i, i+4);
			auxArray[j] = array[i+2];
			j++;
		} else {
			insertionSort(array, i, q);
			auxArray[j] = array[(q+i)/2];
		}
	}
	if (size == 1){
		return auxArray[0];
	} else {
		int res = getMedianVal(auxArray, 0, size - 1);
		free(auxArray);
		return res;
	}
}

void medianSelect(int *array, int p, int q, int k){
	int m = getMedianVal(array, p, q);
	findAndSwapLast(array, p, q, m);
	int mp = partition5(array, p, q);
	//printArray(array, q - p + 1);
	if (mp == k) {
		printf("%d\n", array[k]);
	} else if (mp < k){
		medianSelect(array, mp + 1, q, k);
	} else {
		medianSelect(array, p, mp - 1, k);
	}
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
        medianSelect(a,0,n,k);
        clock_gettime(CLOCK_MONOTONIC, &end);
    } while (duration(start, end) == 0.0);
    return duration(start, end);
}


int main(int argc, char const *argv[])
{
	/*
    int a[ MAX_LINE_SIZE] = {};
	int len = scanArray(a,  MAX_LINE_SIZE);
	int p = 0;
	scanf("%d", &p);
	//quickSortSelection(a, len, p-1);
	//minheapSelection(a, len, p);
	 medianSelect(a, 0, len -1, p-1);
	 */


	int *a = creaArray(5000000);
    int k = randint(100000);
    printf("%f\n", getResolution(a,5000000,k));

    return 0;
}


