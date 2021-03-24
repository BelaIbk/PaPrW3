#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

typedef unsigned int uint;

#define N 10
//#define N 100000000

//-------------------------------------------------------------------------------
// Merge sort functions from https://www.geeksforgeeks.org/merge-sort/

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int32_t arr[], uint l, uint m, uint r) {
    uint i, j, k;
    uint n1 = m - l + 1;
    uint n2 = r - m;
 
    /* create temp arrays */
    uint L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int32_t arr[], uint l, uint r)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        uint m = l + (r - l) / 2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
}


/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int32_t arr[], uint size) {
    uint i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

//-------------------------------------------------------------------------------

void fillArray(int32_t arr[], uint size, uint mod) {
    for (uint i = 0; i < size; i++){
        arr[i] = rand() % mod;
    }
}


void testMergesort() {
    int32_t a1[] = {9,0,1,3,6,2,8,4,5,1};
    int32_t *a2 = (int32_t *) malloc(10 * sizeof(int32_t));

    fillArray(a2, 10, 10);
    printf("Test array 1 unsorted: ");
    printArray(a1, 10);
    printf("Test array 2 unsorted: ");
    printArray(a2, 10);

    mergeSort(a1, 0, 9);
    mergeSort(a2, 0, 9);

    printf("Test array 1 sorted: ");
    printArray(a1, 10);
    printf("Test array 2 sorted: ");
    printArray(a2, 10);

    free(a2);
}


int main() {
    testMergesort();

    int32_t *array = (int32_t *) malloc(N * sizeof(int32_t));

    fillArray(array, N, 1000);

    printArray(array, N);

    double startTime = omp_get_wtime();
    mergeSort(array, 0, N-1);
    double endTime = omp_get_wtime();
    printf("%2.3fs\n", endTime-startTime);

    printArray(array, N);
    free(array);
}