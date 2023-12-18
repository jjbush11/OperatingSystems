//
// Created by James  Bush on 10/20/23.
//

#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include <pthread.h>

#define SHBUFLEN 10
#define NUM_TO_WRITE 10
#define NUM_CONSUMERS 1

typedef struct {
    int buffer[SHBUFLEN]; // the buffer
    int in; // location to which a producer will write
    int out; // location from which a consumer will read
    int count; // total # items in the buffer
    int active; // whether consumers are still active
    pthread_mutex_t lock; // the lock
} BufferInfo;

typedef struct {
    int myid; // id of the producer
    int numWritten; // total number of characters written by this producer
    BufferInfo *bufferInfo; // pointer to the BufferInfo
} ProducerInfo;

typedef struct {
    int myid; // id of the producer
    int numRead; // total number of characters written by this consumer
    BufferInfo *bufferInfo; // pointer to the BufferInfo
} ConsumerInfo;

void* producer(void *param) {

    int valueToWrite=123;
    ProducerInfo *pinfo = (ProducerInfo*)param;

    for (int i = 0; i <= NUM_TO_WRITE; ++i) {
        if (i < NUM_TO_WRITE) {
            valueToWrite = i;
        } else {
            valueToWrite = -1;
        }
        bool written = false;
        while (!written) {
            pthread_mutex_lock(&pinfo->bufferInfo->lock);
            pinfo->bufferInfo->buffer[pinfo->bufferInfo->in] = valueToWrite;
            if (pinfo->bufferInfo->buffer[pinfo->bufferInfo->in] == valueToWrite) {
                printf("%d has written %d\n", pinfo->myid, valueToWrite);
                pinfo->bufferInfo->count += 1;
                pinfo->numWritten += 1;
                printf("buffer in: %d\n", pinfo->bufferInfo->in);
                written = true;
            }

            pthread_mutex_unlock(&pinfo->bufferInfo->lock);
        }
//        pthread_mutex_unlock(&pinfo->bufferInfo->lock);
    }
    pthread_exit(NULL);
}

void* consumer(void *param) {
    ConsumerInfo *cinfo = (ConsumerInfo*)param;
    int valRead;
    bool done = false; // this is a local variable

    while (!done) {
        bool gotValue = false; // another local variable
        pthread_mutex_lock(&cinfo->bufferInfo->lock);
        while (!gotValue && !done){
            if (cinfo->bufferInfo->active) {
                //try to read a value from the shared buffer
                printf("count %d\n", cinfo->bufferInfo->count);
                if (cinfo->bufferInfo->count > 0) {
                    printf("out index %d\n", cinfo->bufferInfo->out);
                    valRead = cinfo->bufferInfo->buffer[cinfo->bufferInfo->out];
//                    cinfo->bufferInfo->out = (cinfo->bufferInfo->out + 1) % SHBUFLEN;
//                    cinfo->bufferInfo->out += 1;
                    cinfo->bufferInfo->count--;
                    gotValue = true;
                    printf("%d consumer reads %d\n", cinfo->myid, valRead);
                    cinfo->numRead+=1;
                    if (valRead == -1){
                        cinfo->bufferInfo->active = false;
                        done = true;
                        printf("done");
                    } else {
                        cinfo->bufferInfo->active = true;
                    }
                }
            }
        }
        pthread_mutex_unlock(&cinfo->bufferInfo->lock);
    }
    pthread_exit(NULL);
}

int main() {

    BufferInfo binfo;
    ProducerInfo pinfo;
    ConsumerInfo cinfo[NUM_CONSUMERS];

    // Initialize BufferInfo
    binfo.in = 0;
    binfo.out = 0;
    binfo.count = NUM_CONSUMERS;
    binfo.active = 1;
    pthread_mutex_init(&binfo.lock, NULL);

    // Initialize ProducerInfo
    pinfo.myid = 1;
    pinfo.numWritten = 0;
    pinfo.bufferInfo = &binfo;

    // Initialize each element of ConsumerInfo
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        cinfo[i].myid = i + 1; // Adjust the ID of the consumer
        cinfo[i].numRead = 0;
        cinfo[i].bufferInfo = &binfo; // Assign the address of binfo to each consumer
        cinfo[i].bufferInfo->count = NUM_CONSUMERS;
    }

    pthread_t producerTid, consumerTid[NUM_CONSUMERS];

    pthread_create(&producerTid, NULL, producer, &pinfo);
    for (int i=0; i<NUM_CONSUMERS; ++i){
        pthread_create(&consumerTid[i], NULL, consumer, &cinfo[i]);
    }

    pthread_join(producerTid, NULL);
    for (int i=0; i<NUM_CONSUMERS; ++i){
        pthread_join(consumerTid[i], NULL);
    }

    return 0;
} // main()
