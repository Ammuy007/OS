#include <stdio.h>
int pagefound(int f[],int count,int a){
        int i;
        for(i=0;i<count;i++){
                if(f[i]==a){
                        return 1;
                }
        }
        return 0;
}
void fifo(int arr[],int n,int f[],int fno){
        int i,h=0,j,k=0,count=0,p=0,front=0;
        int fifoarr[fno][n];
        for(i=0;i<fno;i++){
                for(j=0;j<n;j++){
                        fifoarr[i][j]=-1;
                }
        }
        for(i=0;i<n;i++){
                if(pagefound(f,count,arr[i])){
                        h++;
                }
                else{
                        p++;
                        f[front]=arr[i];
                        front=(front+1)%fno;
                        if(count<fno){
                                count++;
                        }
                }
                for(j=0;j<fno;j++){
                        if(j<count){
                                fifoarr[j][i]=f[j];
                        }
                        else{
                                fifoarr[j][i]=-1;
                        }
                }
        }
        for(i=0;i<fno;i++){
                for(j=0;j<n;j++){
                        if(fifoarr[i][j]!=-1){
                                printf(" %d\t",fifoarr[i][j]);
                        }
                        else{
                                printf("\t");
                        }
                }
                printf("\n");
        }
        printf("\n No of page faults and page hits :%d,%d\n",p,h);
}
int recentaccess(int arr[],int i,int a){
        int j,count=0;
        for(j=i;j>=0;j--){
                count++;
                if(arr[j]==a){
                        return count;
                }
        }
}
void lru(int arr[],int n,int f[],int fno){
        int index=0,i,j,h=0,lruarr[fno][n],x,count,p=0;
        for(i=0;i<n;i++){
                if(pagefound(f,count,arr[i])){
                        h++;
                }
                else{
                        p++;
                        if(count==fno){
                                int max=-1;
                                for(j=0;j<fno;j++){
                                        x=recentaccess(arr,i,f[j]);
                                        if(x>max){
                                                index=j;
                                                max=x;
                                        }
                                }
                                f[index]=arr[i];
                        }
                        else{
                                f[count++]=arr[i];
                        }
                }
                for(j=0;j<fno;j++){
                        if(j<count){
                                lruarr[j][i]=f[j];
                        }
                        else{
                                lruarr[j][i]=-1;
                        }
                }
        }
        for(i=0;i<fno;i++){
                for(j=0;j<n;j++){
                        if(lruarr[i][j]!=-1){
                                printf(" %d\t",lruarr[i][j]);
                        }
                        else{
                                printf("\t");
                        }
                }
                printf("\n");
        }
        printf("The number of page faults and page hits is %d,%d\n",p,h);
}
int totalaccess(int arr[],int i,int a){
        int j,count=0;
        for(j=i;j>=0;j--){
                if(arr[j]==a){
                        count++;
                }
        }
        return count;
}

void lfu(int arr[], int n, int f[], int fno) {
    int i, j, h = 0, p = 0, count = 0;
    int freq[fno];  // Array to store the frequency of frames
    int lastUsed[fno]; // Array to store the last used time of frames
    int lfuarr[fno][n]; // Visualization array

    for(i = 0; i < fno; i++) {
        freq[i] = 0; // Initialize frequency counts
        lastUsed[i] = -1; // Initialize last used indices
    }

    for(i = 0; i < n; i++) {
        int found = 0;
        for(j = 0; j < count; j++) {
            if(f[j] == arr[i]) {
                freq[j]++; // Increase the frequency since it's a hit
                lastUsed[j] = i; // Update last used index
                h++; // Increment hits
                found = 1;
                break;
            }
        }

        if (!found) {
            p++; // Increment page faults
            if (count < fno) { // If there is still space in the frames
                f[count] = arr[i];
                freq[count] = 1; // Initialize frequency count for new frame
                lastUsed[count] = i; // Set last used index
                count++;
            } else { // If no space, find the least frequently used frame
                int minFreq = freq[0], minIndex = 0;
                for (j = 1; j < fno; j++) {
                    if (freq[j] < minFreq || (freq[j] == minFreq && lastUsed[j] < lastUsed[minIndex])) {
                        minFreq = freq[j];
                        minIndex = j;
                    }
                }
                f[minIndex] = arr[i]; // Replace the LRU page
                freq[minIndex] = 1; // Reset the frequency count for the new page
                lastUsed[minIndex] = i; // Update the last used index
            }
        }

        // Update the visualization matrix
        for (j = 0; j < fno; j++) {
            lfuarr[j][i] = (j < count) ? f[j] : -1;
        }
    }

    // Output the LFU array
    for (i = 0; i < fno; i++) {
        for (j = 0; j < n; j++) {
            if (lfuarr[i][j] != -1) {
                printf(" %d\t", lfuarr[i][j]);
            } else {
                printf("\t");
            }
        }
        printf("\n");
    }
    printf("Page faults and page hits %d,%d\n", p,h);
}


int main(){
        int nf,np;
        printf("How many page requests?\n");
        scanf("%d",&np);
        printf("How many frames?\n");
        scanf("%d",&nf);
        int i,arr[np],F[nf];
        printf("Enter the reference string separated by spaces\n");
        for(i=0;i<np;i++){
                scanf("%d",&arr[i]);
        }
        for(i=0;i<nf;i++){
                F[i]=-1;
        }
        printf("\nFIFO\n");
        fifo(arr,np,F,nf);
        printf("\n----------------------------------------------\n");
        printf("\nLRU\n");
        lru(arr,np,F,nf);
         printf("\n----------------------------------------------\n");
        printf("\nLFU\n");
        lfu(arr,np,F,nf);
         printf("\n----------------------------------------------\n");
return 0;
}











