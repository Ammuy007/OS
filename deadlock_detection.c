#include <stdio.h>
int isRightAlloc(int Need[],int Work[],int m){
    int i;
    for(i=0;i<m;i++){
        if(Need[i]>Work[i]){
            return 0;
        }
    }
    return 1;
}
int main() {
    int n,i,j,m;
    printf("How many processes?\n");
    scanf("%d",&n);
    printf("How many resource types?\n");
    scanf("%d",&m);
    int Alloc[n][m],Avail[m],Work[m],Finish[n],Request[n][m];
    printf("Enter the Allocation matrix\n");
    for(i=0;i<n;i++){
        Finish[i]=0;
        for(j=0;j<m;j++){
            scanf("%d",&Alloc[i][j]);
        }
    }
    printf("Enter the Request matrix\n");
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            scanf("%d",&Request[i][j]);
        }
    }
    printf("Enter the available matrix\n");
    for(i=0;i<m;i++){
        scanf("%d",&Avail[i]);
        Work[i]=Avail[i];
    }
    int cycle=0,count=n;
    while(count!=0){
        for(i=0;i<n;i++){
            if(Finish[i]==0 && isRightAlloc(Request[i],Work,m)){
                Finish[i]=1;
                count--;
                for(j=0;j<m;j++){
                    Work[j]+=Alloc[i][j];
                    Alloc[i][j]=0;
                    Request[i][j]=0;
                }
                cycle=0;
            }
            cycle++;
        }
        if(cycle>=2*n){
            break;
        }
    }
    if(count==0){
        printf("\nNo deadlock\n");
    }
    else{
        printf("\nDeadlock\n");
    }
}

