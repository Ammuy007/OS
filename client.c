#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
struct shmem{
        char chat[100];
        int status;
};
int main(){
        struct shmem* shmptr;
        key_t key=1234;
        int shmid=shmget(key,sizeof(struct shmem),0666);
        shmptr=shmat(shmid,NULL,0);
        while(1){
                while(shmptr->status!=1);
                printf("Server :");
                fputs(shmptr->chat,stdout);
                if (strcmp(shmptr->chat, "Stop\n") == 0){
                        exit(1);
                }
                printf("Enter some data\n");
                fgets(shmptr->chat,sizeof(shmptr->chat),stdin);
                shmptr->status=0;
                if (strcmp(shmptr->chat, "Stop\n") == 0){
                        exit(1);
                }
        }
        shmdt(shmptr);
        return 0;
}
