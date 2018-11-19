#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common_threads.h"

/**
 * Now go one step further by implementing a general solution to **barrier synchronization**.
 *
 * Assume there are two points in a sequential piece of code, called *P1* and *P2*.
 *
 * Putting a **barrier** between *P1* and *P2* guarantees that all threads
 * will execute *P1* before any one thread executes *P2*.
 *
 * Your task: write the code to implement a `barrier()` function that can be used in this manner.
 *
 * It is safe to assume you know *N* (the total number of threads in the running program) and
 * that all *N* threads will try to enter the barrier.
 *
 * Again, you should likely use two semaphores to achieve the solution, and some other integers to count things.
 *
 * See `barrier.c` for details.
 */

// If done correctly, each child should print their "before" message
// before either prints their "after" message. Test by adding sleep(1)
// calls in various locations.

// You likely need two semaphores to do this correctly, and some
// other integers to track things.

typedef struct __barrier_t {

    // add semaphores and other information here
    int n; //the number of threads
    int count;
    sem_t sem_mutex;
    sem_t sem_barrier;


} barrier_t;


// the single barrier we are using for this program
barrier_t b;

void barrier_init(barrier_t *b, int num_threads) {

    // initialization code goes here
    b->n = num_threads;
    b->count = 0;
    sem_init(&b->sem_mutex, 0, (unsigned int) 1);
    sem_init(&b->sem_barrier, 0, (unsigned int) 1);
}

/**
 * Thanks internet
 * https://stackoverflow.com/questions/6331301/implementing-an-n-process-barrier-using-semaphores
 */
void barrier(barrier_t *b) {

    // barrier code goes here
    sem_wait(&b->sem_mutex);
    b->count += 1;
    sem_post(&b->sem_mutex);


    if (b->count == b->n) {
        sem_post(&b->sem_barrier); // unblock ONE thread
    }

    sem_wait(&b->sem_barrier);
    sem_post(&b->sem_barrier); // once we are unblocked, it's our duty to unblock the next thread
}

//
// XXX: don't change below here (just run it!)
//
typedef struct __tinfo_t {
    int thread_id;
} tinfo_t;

void *child(void *arg) {
    tinfo_t *t = (tinfo_t *) arg;
    printf("child %d: before\n", t->thread_id);
    barrier(&b);
    printf("child %d: after\n", t->thread_id);
    return NULL;
}


// run with a single argument indicating the number of 
// threads you wish to create (1 or more)
int main(int argc, char *argv[]) {
    assert(argc == 2);
    int num_threads = atoi(argv[1]);
    assert(num_threads > 0);

    pthread_t p[num_threads];
    tinfo_t t[num_threads];

    printf("parent: begin\n");
    barrier_init(&b, num_threads);

    int i;
    for (i = 0; i < num_threads; i++) {
        t[i].thread_id = i;
        Pthread_create(&p[i], NULL, child, &t[i]);
    }

    for (i = 0; i < num_threads; i++)
        Pthread_join(p[i], NULL);

    printf("parent: end\n");
    return 0;
}

