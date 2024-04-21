#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
sem_t chopstick[5];
void* dining(void* args){
        int ph=*((int *)args);
        printf("Philopher %d has come to eat\n",ph);
        sem_wait(&chopstick[ph]);
        printf("Philosopher %d has taken left chopstick\n",ph);
        sem_wait(&chopstick[(ph+1)%5]);
        printf("Philosopher %d has taken right chopstick\n",ph);
        printf("Philosopher %d has started eating\n",ph);
        sleep(1);
        printf("Philosopher %d has finished eating\n",ph);
        sem_post(&chopstick[ph]);
        printf("Philosopher %d dropped left chopstick\n",ph);
        sem_post(&chopstick[(ph+1)%5]);
        printf("Philosopher %d dropped right chopstick\n",ph);
        return NULL;
}
int main(){
        pthread_t philo[5];
        int i;
        int p[]={1,2,3,4,5};
        do{
                for(i=0;i<5;i++){
                        sem_init(&chopstick[i],0,1);
                }
                for(i=0;i<5;i++){
                        pthread_create(&philo[i],NULL,&dining,&p[i]);
                }
                for(i=0;i<5;i++){
                        pthread_join(philo[i],NULL);
                }

        }while(1);
        return 0;
}
