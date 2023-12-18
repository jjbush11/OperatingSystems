//
// Created by James  Bush on 9/22/23.
//

#ifndef ASSIGNMENT2PQU_PQUEUE_JJBUSH_H
#define ASSIGNMENT2PQU_PQUEUE_JJBUSH_H

#define MAX_NAME_LENGTH 63

typedef struct {
    unsigned int weight;
    char name[1 + MAX_NAME_LENGTH];
} Thing;

typedef struct PQueueStruct {
    int priority;
    void *data;
    struct PQueueStruct *next;
} PQueueNode;

int enqueue(PQueueNode **pqueue, int priority, void *data);

void *dequeue(PQueueNode **pqueue);

void *peek(PQueueNode *pqueue);

void printQueue(PQueueNode *pqueue, void (printFunction)(void*));

int getMinPriority(PQueueNode *pqueue);

int queueLength(PQueueNode *pqueue);

void printThing(void *data);


#endif //ASSIGNMENT2PQU_PQUEUE_JJBUSH_H
