#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>

int x = 0;
pthread_mutex_t key;


void *addition(){
        int processor_no;

        for(int i=0; i<100 ; i++){
            processor_no = sched_getcpu();
	    pthread_mutex_lock(&key);
            x++;
            printf("Addition thread, Processor no: %d, x: %d\n", processor_no, x);
	    pthread_mutex_unlock(&key);
        }
}

void *subtraction(){
        int processor_no;

        for(int i=0; i<100 ; i++){
        processor_no = sched_getcpu();
	    pthread_mutex_lock(&key);
        x--;
        printf("Subtraction thread, Processor no: %d, x: %d\n", processor_no, x);
	    pthread_mutex_unlock(&key);
        }


}




void main(){
        pthread_t  tid1, tid2;
        pthread_create(&tid1, NULL, &addition, NULL);
        pthread_create(&tid2, NULL, &subtraction, NULL);
        int processor_no;

        for(int i=0; i<100 ; i++){
        processor_no = sched_getcpu();
        printf("Main thread, Processor no: %d\n", processor_no);
        }

        // To force to main thread to wait until sub-thread is complete
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

}

