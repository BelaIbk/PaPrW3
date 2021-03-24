#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

typedef unsigned int uint;

//#define N 100000000
  #define N 100
//#define N 1000

//----------------------------------
// Merge sort functions from 
// https://www.geeksforgeeks.org/merge-sort/


// l: left, m: middle, r:right
void merge(int32_t arr[], uint l, uint m, uint r) {
    uint n1 = m - l + 1;
    uint n2 = r - m;
 
    // Temp arrays
    int32_t *L = malloc(n1 * sizeof(int32_t));
    int32_t *R = malloc(n2 * sizeof(int32_t));
    for (uint i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (uint j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    //Merge back
    uint i = 0; // Initial index of first subarray
    uint j = 0; // Initial index of second subarray
    uint k = l; // Initial index of merged subarray
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

    free(L);
    free(R);
}

// l:left index, r:right index
void mergeSort(int32_t arr[], uint l, uint r)
{
    if (l < r) {
        uint m = l + (r - l) / 2;

#pragma omp parallel sections num_threads(2)
        {
#pragma omp section 
            {
                mergeSort(arr, l, m);
            }
#pragma omp section
            {
                mergeSort(arr, m + 1, r);
            }
        }

        merge(arr, l, m, r);
    }
}

void printArray(int32_t arr[], uint size) {
    uint i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

//-------------------------------

void fillArray(int32_t arr[], uint size, uint mod) {
    for (uint i = 0; i < size; i++){
        arr[i] = rand() % mod;
    }
}

int main() {
    int32_t *array = (int32_t *) malloc(N * sizeof(int32_t));

    fillArray(array, N, 1000);

    double startTime = omp_get_wtime();
    mergeSort(array, 0, N-1);
    double endTime = omp_get_wtime();

    printArray(array, N);

    printf("%2.3fs\n", endTime-startTime);

    free(array);

    return EXIT_SUCCESS;
}