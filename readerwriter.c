#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
sem_t rw,mutex;
int x=1,readcnt=0;

void* readerfn(void* args){
        sem_wait(&mutex);
        readcnt++;
        if(readcnt==1){
                sem_wait(&rw);
        }
        sleep(1);
        sem_post(&mutex);
        printf("Reader %d:The value is %d\n",(*(int*)args),x);
        sem_wait(&mutex);
        readcnt--;
        if(readcnt==0){
                sem_post(&rw);
        }
        sem_post(&mutex);
        return NULL;
}
void* writerfn(void* args){
        sem_wait(&mutex);
        printf("Writer %d: Changed value to %d\n",(*(int*)args),x*=2);
        sem_post(&mutex);
        return NULL;
}
int main(){
        pthread_t reader[10],writer[5];
        int i;
        int a[]={1,2,3,4,5,6,7,8,9,10};
        sem_init(&mutex,0,1);
        sem_init(&rw,0,1);
        for(i=0;i<10;i++){
                pthread_create(&reader[i],NULL,&readerfn,(void*)&a[i]);

        }
         for(i=0;i<5;i++){
                pthread_create(&writer[i],NULL,&writerfn,(void*)&a[i]);
        }
        for(i=0;i<10;i++){
                pthread_join(reader[i],NULL);
        }
        for(i=0;i<5;i++){
                pthread_join(writer[i],NULL);
        }
        sem_destroy(&mutex);
        sem_destroy(&rw);
        return 0;
}
