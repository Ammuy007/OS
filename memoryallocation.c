#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 25

void WorstFit(int num_blocks, int num_proc, int block_sizes[], int process_sizes[]) {
    int fragment[MAX_BLOCKS], block_allocated[MAX_BLOCKS], block_index[MAX_BLOCKS];
    // Reset block_allocated array
    for (int i = 0; i < num_blocks; i++) {
        block_allocated[i] = 0;
    }

    // Worst Fit algorithm implementation
    int temp;
    for (int i = 0; i < num_proc; i++) {
        int highest = -1; // Initialize highest for each process
        for (int j = 0; j < num_blocks; j++) {
            if (block_allocated[j] != 1) { // If block_allocated[j] is not allocated
                temp = block_sizes[j] - process_sizes[i];
                if (temp >= 0 && temp > highest) { // Update highest for worst fit
                    block_index[i] = j;
                    highest = temp;
                }
            }
        }
        fragment[i] = highest;
        if (highest != -1) {
            block_allocated[block_index[i]] = 1;
        } else {
            block_index[i] = -1; // Set block_index to -1 when no suitable block is found
        }
    }
    printf("\nWorst Fit\n");
    printf("Process_no:\tProcess_size:\tBlock_no:\tBlock_size:\tFragment\n");
    for (int i = 0; i < num_proc; i++) {
        if (block_index[i] != -1) {
            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, process_sizes[i], block_index[i] + 1, block_sizes[block_index[i]], fragment[i]);
        } else {
            printf("%d\t\t%d\t\t-1\t\t-1\t\t-1 (No suitable block)\n", i + 1, process_sizes[i]); // Print message when no suitable block is found
        }
    }
}

void BestFit(int num_blocks, int num_proc, int block_sizes[], int process_sizes[]) {
    int fragment[MAX_BLOCKS], block_allocated[MAX_BLOCKS], block_index[MAX_BLOCKS];
    // Reset block_allocated array
    for (int i = 0; i < num_blocks; i++) {
        block_allocated[i] = 0;
    }

    // Best Fit algorithm implementation
    int temp;
    for (int i = 0; i < num_proc; i++) {
        int best_fit_index = -1;
        int min_fragment = 10000;
        for (int j = 0; j < num_blocks; j++) {
            if (block_allocated[j] != 1) {
                temp = block_sizes[j] - process_sizes[i];
                if (temp >= 0 && temp < min_fragment) {
                    best_fit_index = j;
                    min_fragment = temp;
                }
            }
        }
        if (best_fit_index != -1) {
            block_index[i] = best_fit_index;
            fragment[i] = min_fragment;
            block_allocated[best_fit_index] = 1;
        } else {
            block_index[i] = -1; // Set block_index to -1 when no suitable block is found
        }
    }
    printf("\nBest Fit\n");
    printf("Process No\tProcess Size\tBlock No\tBlock Size\tFragment\n");
    for (int i = 0; i < num_proc; i++) {
        if (block_index[i] != -1) {
            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, process_sizes[i], block_index[i] + 1, block_sizes[block_index[i]], fragment[i]);
        } else {
            printf("%d\t\t%d\t\t-1\t\t-1\t\t-1 (No suitable block)\n", i + 1, process_sizes[i]); // Print message when no suitable block is found
        }
    }
}

void FirstFit(int num_blocks, int num_proc, int block_sizes[], int process_sizes[]) {
    int fragment[MAX_BLOCKS], block_allocated[MAX_BLOCKS], block_index[MAX_BLOCKS];
    // Reset block_allocated array
    for (int i = 0; i < num_blocks; i++) {
        block_allocated[i] = 0;
    }

    // First Fit algorithm implementation
    int temp;
    for (int i = 0; i < num_proc; i++) {
        temp = -1; // Initialize temp for each process
        for (int j = 0; j < num_blocks; j++) {
            if (block_allocated[j] != 1) { // If block_allocated[j] is not allocated
                temp = block_sizes[j] - process_sizes[i];
                if (temp >= 0) { // If the block can accommodate the process
                    block_index[i] = j;
                    block_allocated[j] = 1; // Mark the block as allocated
                    break;
                }
            }
        }
        if (temp >= 0) {
            fragment[i] = temp;
        } else {
            block_index[i] = -1; // Set block_index to -1 when no suitable block is found
        }
    }
    printf("\nFirst Fit\n");
    printf("Process No\tProcess Size\tBlock No\tBlock Size\tFragment\n");
    for (int i = 0; i < num_proc; i++) {
        if (block_index[i] != -1) {
            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, process_sizes[i], block_index[i] + 1, block_sizes[block_index[i]], fragment[i]);
        } else {
            printf("%d\t\t%d\t\t-1\t\t-1\t\t-1 (No suitable block)\n", i + 1, process_sizes[i]); // Print message when no suitable block is found
        }
    }
}

int main() {
    int num_blocks, num_proc;
    printf("Enter the number of blocks:\n");
    scanf("%d", &num_blocks);
    printf("Enter the number of processes:\n");
    scanf("%d", &num_proc);

    int block_sizes[MAX_BLOCKS], process_sizes[MAX_BLOCKS];
    printf("Enter the size of the blocks:\n");
    for (int i = 0; i < num_blocks; i++) {
        printf("Block %d:", i + 1);
        scanf("%d", &block_sizes[i]);
    }
    printf("Enter the size of the processes:\n");
    for (int i = 0; i < num_proc; i++) {
        printf("Process %d:", i + 1);
        scanf("%d", &process_sizes[i]);
    }

    WorstFit(num_blocks, num_proc, block_sizes, process_sizes);
    BestFit(num_blocks, num_proc, block_sizes, process_sizes);
    FirstFit(num_blocks, num_proc, block_sizes, process_sizes);

    return 0;
}
