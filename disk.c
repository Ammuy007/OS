#include <stdio.h>
#include <stdlib.h>
void fcfs(int initial,int n,int req[]){
        int i,seek=0;
        for(i=0;i<n;i++){
                seek=seek+abs(initial-req[i]);
                initial=req[i];
        }
        printf("\nFCFS\nTotal seek time=%d\n",seek);
        printf("--------------------------------------------------------------\n");
}
void scan(int initial,int n,int req[],int track,int move){
        int i,j,temp=0,seek = 0;

    // Sorting the queue of requests
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (req[j] > req[j + 1]) {
                temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }
        }
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        if (initial < req[i]) {
            index = i;
              break;
        }
    }

    if (move == 1) {
        // Moving towards the higher end of the disk
        for (i = index; i < n; i++) {
            seek += abs(initial - req[i]);
            initial = req[i];
        }
        // If the head is not already at the end, move to the end
        if (index != 0){
            seek += abs(track - 1 - initial);
        }
        initial = track - 1;
        // Move towards the lower end of the disk
        for (i = index - 1; i >= 0; i--) {
            seek += abs(initial - req[i]);
           initial = req[i];
        }
    } else {
        // Moving towards the lower end of the disk
        for (i = index - 1; i >= 0; i--) {
            seek += abs(initial - req[i]);
            initial = req[i];
        }
        // If the head is not already at the start, move to the start
        if (index != n){
            seek += abs(initial - 0);
        }
        initial = 0;
        // Move towards the higher end of the disk
        for (i = index; i < n; i++) {
            seek += abs(initial - req[i]);
            initial = req[i];
        }
    }
    printf("\nSCAN\nTotal seek time=%d\n", seek);
         printf("\n-----------------------------------------------\n");
}

void cscan(int initial,int n,int req[],int track,int move){
        int i,j,temp=0,seek=0;
        for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (req[j] > req[j + 1]) {
                temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }
        }
    }

    int index = 0;
    for (i = 0; i < n; i++) {
        if (initial < req[i]) {
            index = i;
            break;
        }
    }
        if(move==1)
        {
            for(i=index;i<n;i++)
            {
                seek+=abs(req[i]-initial);
                initial=req[i];
            }
            //  last movement for max size
            seek+=abs(track-req[i-1]-1);
            /*movement max to min disk */
            seek+=abs(track-1-0);
            initial=0;
            for( i=0;i<index;i++)
            {
                 seek+=abs(req[i]-initial);
                 initial=req[i];

            }
        }
        // if movement is towards low value
        else
        {
            for(i=index-1;i>=0;i--)
            {
                seek+=abs(req[i]-initial);
                initial=req[i];
            }
            //  last movement for min size
            seek+=abs(req[i+1]-0);
            /*movement min to max disk */
            seek+=abs(track-1-0);
            initial =track-1;
            for(i=n-1;i>=index;i--)
            {
                 seek+=abs(req[i]-initial);
                 initial=req[i];

            }
        }

        printf("CSCAN\nTotal seek time=%d\n-------------------------------------------\n",seek);
}
int main(){
        int move,n,initial,i,track;
        printf("How many requests?\n");
        scanf("%d",&n);
        int req[n];
        printf("Enter the requests\n");
        for(i=0;i<n;i++){
                scanf("%d",&req[i]);
        }
        printf("Enter the initial head positiion\n");
        scanf("%d",&initial);
        printf("Enter the maximum number of tracks\n");
        scanf("%d",&track);
        //0-high to low,1-low to high
        printf("Enter the direction(0/1)\n");
        scanf("%d",&move);
        fcfs(initial,n,req);
        scan(initial,n,req,track,move);
        cscan(initial,n,req,track,move);
}
