#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
sem_t empty,mutex,full;
int buffer[10],in=0,out=0;
void* producer(void* args){
        int no=*((int*)args);
        int i,item;
//      free(args);
        for(i=0;i<4;i++){
        item=rand()%100;
        sem_wait(&empty);
        sem_wait(&mutex);
        printf("Producer %d produced %d\n",no,item);
        buffer[in]=item;
        in=(in+1)%10;
        sem_post(&mutex);
        sem_post(&full);
        }
}
void* consumer(void* args){
        int no=*((int*)args);
        int i,item;
//      free(args);
         for(i=0;i<4;i++){
        item=buffer[out];
        sem_wait(&full);
        sem_wait(&mutex);
        printf("Consumer %d consumed %d\n",no,item);
        out=(out+1)%10;
        sem_post(&mutex);
        sem_post(&empty);
        }
}
int main(){
        pthread_t pro[4],con[4];
        int i;
        sem_init(&empty,0,10);
        sem_init(&mutex,0,1);
        sem_init(&full,0,0);
        int a[]={1,2,3,4};
        for(i=0;i<4;i++){
                        pthread_create(&pro[i],NULL,&producer,(void*)&a[i]);
        }
        for(i=0;i<4;i++){
                 pthread_create(&con[i],NULL,&consumer,(void*)&a[i]);
        }
        for(i=0;i<4;i++){
                pthread_join(pro[i],NULL);
        }
        for(i=0;i<4;i++){
                pthread_join(con[i],NULL);
        }
        sem_destroy(&mutex);
         sem_destroy(&full);
         sem_destroy(&empty);
        return 0;
}

