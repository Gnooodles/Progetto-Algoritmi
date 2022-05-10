
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

//clock_gettime(CLOCK_MONOTONIC, &timeNow);
void funzione() {
    long k = 0;
    for (int i = 0; i < 10000; i++)
    {
        for (int i = 0; i < 10000; i++)
    {
        
    }
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
        funzione();
        clock_gettime(CLOCK_MONOTONIC, &end);
    } while (duration(start, end) == 0.0);
    return duration(start, end);
}


int main(int argc, char const *argv[])
{

    double rr = getResolution();
    
    
    printf("%f\n", rr);
    
    return 0;
}
