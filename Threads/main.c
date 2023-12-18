//
// Created by James  Bush on 10/6/23.
//

#include <pthread.h>
#include <stdio.h>
#include "mtcount-jjbush.c"



void *doCount(void *);
int prand();

int main(){

    CountInfo numThreadArray[NUMTHREADS];
    pthread_t threadIds[NUMTHREADS];
    float threshold = .5;
    int chunkSize, i, pos, totalCount;

    int i1, i2;
    float f1, f2;
    for (i=0; i<NUMVALS; ++i) {
        i1 = prand(100);
        i2 = prand(100);
        f1 = i1 / 100.0;
        f2 = i2 / 100.0;
        g_vals[i] = f1 / (1.0 + f2);
    }

    // set up bounds for the threads
    chunkSize = NUMVALS / NUMTHREADS;
    pos = 0;
    for (i=0; i<NUMTHREADS; ++i) {
        numThreadArray[i].startIndex = pos; //i * chunkSize
        numThreadArray[i].endIndex = numThreadArray[i].startIndex + chunkSize;
        numThreadArray[i].threshold = threshold;
        pos = pos + chunkSize + 1;
    }

    // adjust last region if necessary
    if (numThreadArray[NUMTHREADS-1].endIndex < NUMVALS-1)
        numThreadArray[NUMTHREADS-1].endIndex = NUMVALS - 1;
    else if (numThreadArray[NUMTHREADS-1].endIndex > NUMVALS-1)
        numThreadArray[NUMTHREADS-1].endIndex = NUMVALS - 1;

    // create child threads
    for (i=0; i<NUMTHREADS; ++i)
        pthread_create(&threadIds[i], NULL, doCount, &numThreadArray[i]);

    // wait for the child threads to terminate
    for (i=0; i<NUMTHREADS; ++i)
        pthread_join(threadIds[i], NULL);

    // gather data from the individual results
    totalCount = 0;
    for (i=0; i<NUMTHREADS; ++i) {
        totalCount += numThreadArray[i].count;
    }

    printf("overall count is %d\n", totalCount);

    return 0;
}

int prand() {
    static int p = 1;
    const int a = 105491;
    const int b = 733;
    const int c = 6619;
    const int base = 100;
    int val;
    p = p*a + b;
    p = p % c;
    val = p % base;
    return val;
}