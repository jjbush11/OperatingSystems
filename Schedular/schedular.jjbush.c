//
// Created by James  Bush on 11/8/23.
//

#include "schedular.jjbush.h"
#include "pqueue.jjbush.h"
#include <stdbool.h>
#include <printf.h>
#include <stdlib.h>

void schedule() {

    // Create futureQueue
    PQueueNode *fcfs = NULL;
    PQueueNode *sjf = NULL;
    int currentID = 1;

    // Create tasks
    Task *t1 = (Task *) malloc(sizeof(Task));
    t1->submitTime = 0;
    t1->totalBurstTime = 6;

    Task *t2 = (Task *) malloc(sizeof(Task));
    t2->submitTime = 0;
    t2->totalBurstTime = 8;

    Task *t3 = (Task *) malloc(sizeof(Task));
    t3->submitTime = 0;
    t3->totalBurstTime = 7;

    Task *t4 = (Task *) malloc(sizeof(Task));
    t4->submitTime = 0;
    t4->totalBurstTime = 3;

    // Add taskID to each task and make FCFS queue
    Task *tasks[] = {t1, t2, t3, t4};
    for (int i=0; i<4; ++i) {
        tasks[i]->taskID = i;
        tasks[i]->totalWaitTime = 0;
        enqueue(&fcfs, tasks[i]->submitTime, tasks[i]);
    }

    int currentTime = getMinPriority(fcfs);
    int totalWaitTime = 0;
    bool done = false;
    while (!done) {
        if (queueLength(fcfs) == 0) {
            done = true;
        } else {
            Task *task = dequeue(&fcfs);
            task->totalWaitTime = task->totalWaitTime + (currentTime - task->submitTime);
            totalWaitTime = totalWaitTime + task->totalWaitTime;
            currentTime = currentTime + task->totalBurstTime;
        }
    }
    printf("Wait time FCFS: %d\n", totalWaitTime);
    int fcfsWaitTime = totalWaitTime;

    // Add tasks to sjf queue and reset total wait time
    for (int i=0; i<4; ++i) {
        currentID = currentID + 1;
        tasks[i]->taskID = currentID;
        tasks[i]->totalWaitTime = 0;
        enqueue(&sjf, tasks[i]->totalBurstTime, tasks[i]);
    }

    currentTime = 0;
    totalWaitTime = 0;
    done = false;
    while (!done) {
        if (queueLength(sjf) == 0) {
            done = true;
        } else {
            Task *task = dequeue(&sjf);
            task->totalWaitTime = task->totalWaitTime + (currentTime - task->submitTime);
            totalWaitTime = totalWaitTime + task->totalWaitTime;
            currentTime = currentTime + task->totalBurstTime;
        }
    }
    printf("Wait time SJF: %d\n", totalWaitTime);

    int meanWaitTime = (totalWaitTime + fcfsWaitTime)/2;
    printf("Mean wait time: %d\n", meanWaitTime);
}