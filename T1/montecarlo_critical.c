#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 500000000

double montecarlo(size_t n) {

    size_t total_sum = 0;

    #pragma omp parallel
    {
        unsigned int seed = omp_get_thread_num();
    
        size_t inner_sum = 0;
        #pragma omp for
        for (size_t i = 0; i < n; i++) {
            double x = rand_r(&seed) / (double) RAND_MAX;
            double y = rand_r(&seed) / (double) RAND_MAX;
            inner_sum+= (x * x + y * y <= 1);
        }

        #pragma omp critical
        total_sum += inner_sum;
    }

    return 4 * total_sum / (double) n;
}

int main() {
    double startTime = omp_get_wtime();
    double result = montecarlo(N);
    double endTime = omp_get_wtime();

	printf("%2.3fs (N=%d, Result=%f)\n", endTime-startTime, N, result);
}