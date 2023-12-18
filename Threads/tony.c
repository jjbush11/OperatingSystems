//
// Created by James  Bush on 10/7/23.
//
//
// Created by Anthony Mazzola on 10/7/23.
//

#include "mtcount.apmazzol.h"
#include "stdio.h"
#include <pthread.h>

#define NUMVALS (1024*1024)
#define NUMTHREADS 4

typedef struct {
    int startIndex; // start index at which to start looking
    int endIndex; // end index at which to stop looking
    float threshold; // threshold value
    int count; // result: #values that are greater than threshold
} CountInfo;

float g_vals[NUMVALS];

void *doCount(void *param);

void *doCount(void *param) {
    CountInfo *data;
    int count = 0;

    data = (CountInfo *) param;

    for (int i = data->startIndex; i <= data->endIndex; i++) {
        if (g_vals[i] > data->threshold) {
            count++;
        }
    }

    data->count = count;

    pthread_exit(NULL);
}

int prand(int num) {
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


int main() {
    int i1, i2;
    float f1, f2;
    for (int i = 0; i < NUMVALS; i++) {
        i1 = prand(100);
        i2 = prand(100);
        f1 = i1 / 100.0;
        f2 = i2 / 100.0;
        g_vals[i] = f1 / (1.0 + f2);
    }

    pthread_t threadsID[NUMTHREADS];
    CountInfo threadData[NUMTHREADS];

    float threshold = 0.5;
    int chunkSize = NUMVALS / NUMTHREADS;

    int totalCount = 0;
    int start;
    int end;

    for (int i = 0; i < NUMTHREADS; i++) {
        start = i * chunkSize;
        end = (i + 1) * chunkSize - 1;

        threadData[i].startIndex = start;
        if (i == NUMTHREADS - 1) {
            threadData[i].endIndex = NUMVALS - 1;
        } else {
            threadData[i].endIndex = end;
        }
        threadData[i].threshold = threshold;
        pthread_create(&threadsID[i], NULL, doCount, &threadData[i]);
        pthread_join(threadsID[i], NULL);
        totalCount += threadData[i].count;
    }

    printf("Total count: %d", totalCount);

    return 0;
}