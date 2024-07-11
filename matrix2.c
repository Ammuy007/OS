#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <fcntl.h>
struct shared{
        int row;
        int col;
        int mat[10][10];
};
int main(){
        int i,j;
        struct shared* shmptr;
 //       key_t key=ftok("abcd",67);
        int shmid=shmget((key_t)1222,sizeof(struct shared),0666);
        shmptr=shmat(shmid,NULL,0);
        printf("The transpose is\n");
        for(i=0;i<shmptr->col;i++){
                for(j=0;j<shmptr->row;j++){
                        printf("%d\t\t",shmptr->mat[j][i]);
                }
                printf("\n");
        }
return 0;
}

