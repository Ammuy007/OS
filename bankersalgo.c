  GNU nano 6.2                                                                                                                                                                            bankers.c
#include <stdio.h>
int main(){
        int n,m,i,j,k,y,index=0;
        printf("How many processes?\n");
        scanf("%d",&n);
        printf("How many resources?\n");
        scanf("%d",&m);
        int f[n],need[n][m],ans[n],alloc[n][m],max[n][m],avail[m];
        for(i=0;i<n;i++){
                f[i]=0;
        }
        printf("Enter the avilable matrix\n");
        for(i=0;i<m;i++){
                scanf("%d",&avail[i]);
        }
        printf("Enter the max matrix\n");
        for(i=0;i<n;i++){
                for(j=0;j<m;j++){
                        scanf("%d",&max[i][j]);
                }
        }
         printf("Enter the allocation matrix\n");
        for(i=0;i<n;i++){
                for(j=0;j<m;j++){
                        scanf("%d",&alloc[i][j]);
                }
        }
         for(i=0;i<n;i++){
                for(j=0;j<m;j++){
                        need[i][j]=max[i][j]-alloc[i][j];
                }
        }
        for(k=0;k<n;k++){
                for(i=0;i<n;i++){
                        if(f[i]==0){
                                int flag=0;
                                for(j=0;j<m;j++){
                                        if(need[i][j]>avail[j]){
                                                flag=1;
                                                break;
                                        }
                                }
                                if(flag==0){
                                        ans[index++]=i;
                                        for(y=0;y<m;y++){
                                                avail[y]+=alloc[i][y];
                                        }
                                        f[i]=1;
                                }
                        }
                }
        }
        int flag=1;
        for(i=0;i<n;i++){
                if(f[i]==0){
                        printf("Not safe\n");
                        flag=0;
                        break;
                }
        }
        if(flag==1){
                printf("The safe sequence is\n");
                for(i=0;i<n;i++){
                        printf("P%d\n",ans[i]);
                }
        }
        return 0;
}


