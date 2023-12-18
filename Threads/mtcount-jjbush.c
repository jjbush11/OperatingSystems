//
// Created by James  Bush on 10/9/23.
//

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

void *doCount(void *param){
    CountInfo *data;
    int i, count=0;

    data = (CountInfo *) param;

    for (i=data->startIndex; i<=data->endIndex; ++i) {
        if (g_vals[i] > data->threshold)
            ++count;
    }

    data->count = count;

    pthread_exit(NULL);
}