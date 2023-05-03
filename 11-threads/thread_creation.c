#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

/*
    build with gcc -pthread thread_creaion.c
*/

void printId() {
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    fprintf(stdout, "pid: %d, itd: %ld\n", pid, tid);
}

void* th_func(void* args) {
    fprintf(stdout, "[Thread]: ");
    printId();
    return (void*) 0;
}


int main(int argc, char* argv[]) {
    fprintf(stdout, "[Main]: ");
    printId();
    pthread_t nth; 
    if(pthread_create(&nth, NULL, th_func, NULL) < 0) {
        fprintf(stderr, "[Main]: Error creating thread\n");
    }
    sleep(2);
    return 0;
}