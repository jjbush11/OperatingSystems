//
// Created by James  Bush on 9/20/23.
//

#include <stdio.h>
#include <stdlib.h>
#include "pqueue.jjbush.h"

int enqueue(PQueueNode **pqueue, int priority, void *data) {

    PQueueNode *node = (PQueueNode *)malloc(sizeof(PQueueNode));
    node->priority = priority;
    node->data = data;
    node->next = NULL;

    PQueueNode *current = *pqueue;

    if (current == NULL || priority > current->priority) {
        node->next = *pqueue;
        *pqueue = node;
    }
    else {
        // While there is a next node and the next node's priority is higher
        while (current->next != NULL && priority < current->next->priority) {
            current = current->next;
        }

        // Set the node in the correct place
        node->next = current->next;
        current->next = node;
    }

    return 0;
}

void *dequeue(PQueueNode **pqueue) {

    PQueueNode *current = *pqueue;
    PQueueNode *prev = NULL;

    if (current == NULL) {
        return NULL;
    }

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        *pqueue = NULL;
    }
    else {
        prev->next = NULL;
    }

    void *data = current->data;
    free(current);
    return data;
}

void *peek(PQueueNode *pqueue) {
    PQueueNode *current = pqueue;
    void *data;
    if (current == NULL) {
        return NULL;
    }

    while (current->next != NULL){
        current = current ->next;
        if (current->next == NULL) {
            data = current->data;
        }
    }

    return data;
}

void printQueue(PQueueNode *pqueue, void (printFunction)(void*)) {
    PQueueNode *current = pqueue;
    while (current != NULL){
        printFunction(current->data);
        current = current->next;
    }
}

int getMinPriority(PQueueNode *pqueue) {
    PQueueNode *current = pqueue;
    if (current == NULL) {
        return -1;
    }

    while (current->next != NULL){
        current = current ->next;
    }

    return current->priority;
}

int queueLength(PQueueNode *pqueue) {
    int counter = 0;
    PQueueNode *current = pqueue;
    if (current == NULL) {
        return counter;
    }

    while (current != NULL){
        current = current ->next;
        counter++;
    }

    return counter;
}

void printThing(void *data) {
    Thing *thing = (Thing *) data;
    printf("%s (%u lbs) \n", thing->name, thing->weight);
}

