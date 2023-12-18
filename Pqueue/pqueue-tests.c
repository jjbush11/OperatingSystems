#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.jjbush.h" // use your .h file

Thing *createThing(char *name, unsigned int weight) {
    Thing *thing;
    if (name == NULL)
        return NULL;
    if (strlen(name) == 0 || strlen(name) > MAX_NAME_LENGTH)
        return NULL;
    thing = (Thing *) malloc(sizeof(Thing));
    strcpy(thing->name, name);
    thing->weight = weight;
    return thing;
}

//--------------------------------------------------------------------------

int checkResult(Thing *testThing, Thing *expectedThing) {
    int rtnval = 0;

    if (testThing == NULL) {
        printf("ERROR: checking result; have NULL pointer\n");
        rtnval = 1;
    } else {
        if ( strcmp(testThing->name, expectedThing->name) ) {
            printf("ERROR: checking result; expected '%s' but got '%s'\n",
                   expectedThing->name, testThing->name);
            rtnval = 1;
        }
        if ( testThing->weight != expectedThing->weight ) {
            printf("ERROR: checking result; expected %u but got %u\n",
                   expectedThing->weight, testThing->weight);
            rtnval = 1;
        }
    }
    return rtnval;
}

//--------------------------------------------------------------------------

int pqueueTests() {
    int minPriority;
    PQueueNode *pqueue = NULL;
    Thing *thing;
    int rc, numfails;

    numfails = 0;

    Thing *rock = createThing("rock", 5);
    enqueue(&pqueue, 3, rock);

    Thing *toad = createThing("toad", 1);
    enqueue(&pqueue, 8, toad);

    Thing *macBook = createThing("MacBook", 6);
    enqueue(&pqueue, 1, macBook);

    Thing *corgi = createThing("corgi", 25);
    enqueue(&pqueue, 9, corgi);

    Thing *textbook = createThing("textbook", 8);
    enqueue(&pqueue, 2, textbook);

    Thing *brick = createThing("brick", 3);
    enqueue(&pqueue, 12, brick);

    Thing *shovel = createThing("shovel", 12);
    enqueue(&pqueue, 9, shovel);

    Thing *couch = createThing("couch", 125);
    enqueue(&pqueue, 2, couch);

    Thing *hondaCivic = createThing("Honda Civic", 3200);
    enqueue(&pqueue, 1, hondaCivic);

    printQueue(pqueue, printThing);

    printf("--------------------------------------------------\n");
    thing = peek(pqueue);
    printf("peek: ");
    printThing(thing);
    rc = checkResult(thing, macBook);
    if (rc != 0)
        ++numfails;

    thing = dequeue(&pqueue);
    printf("dequeued: ");
    printThing(thing);
    rc = checkResult(thing, macBook);
    if (rc != 0)
        ++numfails;

    thing = peek(pqueue);
    printf("peek: ");
    printThing(thing);
    rc = checkResult(thing, hondaCivic);
    if (rc != 0)
        ++numfails;

    thing = dequeue(&pqueue);
    printf("dequeued: ");
    printThing(thing);
    rc = checkResult(thing, hondaCivic);
    if (rc != 0)
        ++numfails;

    thing = peek(pqueue);
    printf("peek: ");
    printThing(thing);
    rc = checkResult(thing, textbook);
    if (rc != 0)
        ++numfails;

    printf("--------------------------------------------------\n");

    Thing *table = createThing("table", 56);
    enqueue(&pqueue, 1, table);

    Thing *cake = createThing("cake", 4);
    enqueue(&pqueue, 2, cake);

    Thing *candle = createThing("candle", 2);
    enqueue(&pqueue, 20, candle);

    printQueue(pqueue, printThing);

    printf("--------------------------------------------------\n");

    Thing *queueContents[] = {table, textbook, couch, cake, rock, toad, corgi, shovel, brick, candle};
    unsigned int priorities[] = {1, 2, 2, 2, 3, 8, 9, 9, 12, 20};

    int idx = 0;

    while (queueLength(pqueue) > 0) {
        minPriority = getMinPriority(pqueue);
        printf("min priority = %d\n", minPriority);
        if (minPriority != priorities[idx]) {
            printf("ERROR: expected priority %u; got %d\n",
                   priorities[idx], minPriority);
            ++numfails;
        }
        thing = dequeue(&pqueue);
        printf("dequeued: ");
        printThing(thing);
        rc = checkResult(thing, queueContents[idx]);
        if (rc != 0)
            ++numfails;
        ++idx;
    }

    // try one more peek(), one more getMinPriority(), and one more peek() --
    // all should fail
//    printf("printing ");
//    printQueue(pqueue, printThing);

    minPriority = getMinPriority(pqueue);
    if (minPriority != -1) {
        printf("ERROR: expected priority %d; got %d\n", -1, minPriority);
        ++numfails;
    }

    thing = peek(pqueue);
    if (thing != NULL) {
        printf("ERROR: expected NULL from peek(); got non-NULL\n");
        ++numfails;
    }

    thing = dequeue(&pqueue);
    if (thing != NULL) {
        printf("ERROR: expected NULL from dequeue(); got non-NULL\n");
        ++numfails;
    }

    if (numfails == 0)
        printf("SUCCESS! All tests pass.\n");
    else
        printf("Fail: %d test(s) did not pass\n", numfails);

    return numfails;
}

//--------------------------------------------------------------------------

int main() {
    pqueueTests();
}

