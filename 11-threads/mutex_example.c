#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

struct shared_counter_t {
    pthread_mutex_t mtx;
    uint cnt;
    uint idx;
};

static struct shared_counter_t* scp = NULL;

void shared_counter_create() {
    scp = malloc(sizeof(struct shared_counter_t));
    scp->idx = 0;
    scp->cnt = 0;
    pthread_mutex_init(&scp->mtx, NULL);
}

void* th_func(void* arg) {
    while(scp != NULL) {
        pthread_mutex_lock(&scp->mtx);
        if(scp->cnt >= 10) {
            scp->idx--;
            printf("idx value: %d\n", scp->idx);
        } else {
            scp->cnt++;
            printf("cnt value: %d\n", scp->cnt);
        }
        
        if(scp->idx > 0) {
            pthread_mutex_unlock(&scp->mtx);
        } else {
            pthread_mutex_unlock(&scp->mtx);
            pthread_mutex_destroy(&scp->mtx);
            free(scp);
            scp = NULL;
        }
        sleep(1);
    }
    pthread_exit((void*)0);
}

int main(int argc, char* argv[]) {
    pthread_t tid1, tid2;
    shared_counter_create();
    scp->idx = 2;

    pthread_create(&tid1, NULL, th_func, NULL);
    pthread_create(&tid2, NULL, th_func, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}