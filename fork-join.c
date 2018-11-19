#include <stdio.h>
#include <unistd.h>
#include "common_threads.h"

/**
 * The first problem is just to implement and test a solution to the **fork/join problem**, as described in the text.
 * Even though this solution is described in the text, the act of typing it in on your own is worthwhile;
 * even Bach would rewrite Vivaldi, allowing one soon-to-be master to learn from an existing one.
 * See `fork-join.c` for details. Add the call `sleep(1)` to the child to ensure it is working.
 */

sem_t s;

void *child(void *arg) {
    printf("child\n");
    // use semaphore here
    sem_wait(&s);
    sleep(1);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    // init semaphore here
    sem_init(&s, 1, 1);
    printf("parent: begin\n");
    Pthread_create(&p, NULL, child, NULL);
    // use semaphore here
    sem_wait(&s);
    printf("parent: end\n");
    return 0;
}

