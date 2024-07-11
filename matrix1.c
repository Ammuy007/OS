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
        key_t key=ftok("abcd",67);
        int shmid=shmget((key_t)1222,sizeof(struct shared),IPC_CREAT|0666);
        shmptr=shmat(shmid,NULL,0);
        printf("Enter the number of rows\n");
        scanf("%d",&shmptr->row);
        printf("Enter the number of columns\n");
        scanf("%d",&shmptr->col);
        printf("Enter the elements\n");
        for(i=0;i<shmptr->row;i++){
                for(j=0;j<shmptr->col;j++){
                        scanf("%d",&shmptr->mat[i][j]);
                }
        }
        printf("The matrix is\n");
        for(i=0;i<shmptr->row;i++){
                for(j=0;j<shmptr->col;j++){
                        printf("%d\t\t",shmptr->mat[i][j]);
                }
                printf("\n");
        }
return 0;
}
