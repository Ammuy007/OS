  GNU nano 6.2                                                                                                                                            server2.c                                                                                                                                                      #include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/types.h>
struct shmem{
        char chat[100];
        int status;
};
int main(){
        char buff[100];
        key_t key=1234;
        struct shmem* shmptr;
        int shmid=shmget(key,sizeof(struct shmem),IPC_CREAT|0666);
        shmptr=shmat(shmid,NULL,0);
        shmptr->status=0;
        printf("Process is attached to %p\n",shmptr);
        while(1){
        while(shmptr->status!=0);
        printf("Client: ");
        fputs(shmptr->chat,stdout);
        if (strcmp(shmptr->chat, "Stop\n") == 0){
                        exit(1);
                }
        printf("Enter some data to shared memory\n");
        fgets(shmptr->chat,sizeof(shmptr->chat),stdin);
        shmptr->status=1;
                 if (strcmp(shmptr->chat, "Stop\n") == 0){
                        exit(1);
                }
        }
        shmdt(shmptr);
        shmctl(shmid,IPC_RMID,NULL);
        return 0;
}
