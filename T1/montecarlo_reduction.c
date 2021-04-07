#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 500000000

double montecarlo(size_t n) {

    
    size_t sum = 0;

    #pragma omp parallel
    {
        unsigned int seed = omp_get_thread_num();

        #pragma omp for reduction (+: sum)
        for (size_t i = 0; i < n; i++) {
            double x = rand_r(&seed) / (double) RAND_MAX;
            double y = rand_r(&seed) / (double) RAND_MAX;
            sum+= (x * x + y * y <= 1);
        }
    }

    return 4 * sum / (double) n;
}

int main() {
    double startTime = omp_get_wtime();
    double result = montecarlo(N);
    double endTime = omp_get_wtime();
    
	printf("%2.3fs (N=%d, Result=%f)\n", endTime-startTime, N, result);
}