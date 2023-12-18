//
// Created by James  Bush on 11/8/23.
// Worked on with anthony mazzola 
//

#ifndef SCHEDULAR_SCHEDULAR_JJBUSH_H
#define SCHEDULAR_SCHEDULAR_JJBUSH_H

typedef struct {
    int taskID; // unique ID for this task
    int submitTime; // the time at which this task is submitted
    int totalBurstTime; // total time that this task will run
    int totalWaitTime; // the total time that this task has waited
} Task;

void schedule();

#endif //SCHEDULAR_SCHEDULAR_JJBUSH_H
