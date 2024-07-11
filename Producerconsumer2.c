#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
sem_t empty1,empty2,full1,full2;
int buffer_int[5],buffer_c[26];
pthread_mutex_t mutex1,mutex2;
int in1=0,in2=0,out1=0,out2=0;
char char_item='A';
void* producer1(void* args){
    int item;
    while(1){
        sleep(1);
    item=(item+1)%5;
    sem_wait(&empty1);
    pthread_mutex_lock(&mutex1);
    buffer_int[in1]=item;
    in1=(in1+1)%5;
    printf("Produced integer %d\n",item);
    pthread_mutex_unlock(&mutex1);
    sem_post(&full1);
    }
    pthread_exit(NULL);
    return NULL;
}
void* producer2(void* args){
    char alpha;
    while(1){
        sleep(1);
       alpha= char_item++;
        if(char_item>'Z'){
            char_item='A';
        }
        sem_wait(&empty2);
        pthread_mutex_lock(&mutex2);
        buffer_c[in2]=alpha;
        in2=(in2+1)%26;
        printf("Produced alphabet %c\n",alpha);
        pthread_mutex_unlock(&mutex2);
        sem_post(&full2);
    }
     pthread_exit(NULL);
    return NULL;
}
void* consumer(void* args){
    int item=-1;
    char alpha='a';
    while(1){
    sem_wait(&full1);
    pthread_mutex_lock(&mutex1);
    item=buffer_int[out1];
    out1=(out1+1)%5;
    pthread_mutex_unlock(&mutex1);
    sem_post(&empty1);
    printf("Consumed integer %d\n",item);
    sleep(2);
    //Consume character
    sem_wait(&full2);
    pthread_mutex_lock(&mutex2);
    alpha=buffer_c[out2];
    out2=(out2+1)%26;
    pthread_mutex_unlock(&mutex2);
    sem_post(&empty2);
    printf("Consumed alphabet %c\n",alpha);
    sleep(2);
    }
    pthread_exit(NULL);
    return NULL;
}
int main(){
    sem_init(&empty1,0,5);
    sem_init(&empty2,0,26);
    sem_init(&full1,0,0);
    sem_init(&full2,0,0);
    pthread_mutex_init(&mutex1,NULL);
    pthread_mutex_init(&mutex2,NULL);
    pthread_t prod1,prod2,cons;
    pthread_create(&prod1,NULL,(void*)producer1,NULL);
    pthread_create(&prod2,NULL,(void*)producer2,NULL);
    pthread_create(&cons,NULL,(void*)consumer,NULL);
    pthread_join(prod1,NULL);
    pthread_join(prod2,NULL);
    pthread_join(cons,NULL);
    sem_destroy(&empty1);
    sem_destroy(&full1);
    pthread_mutex_destroy(&mutex1);
    return 0;
}
