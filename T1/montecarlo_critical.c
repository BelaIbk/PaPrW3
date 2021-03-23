#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 50000000

double montecarlo(size_t n, size_t num_threads) {

    size_t total_sum = 0;

    #pragma omp parallel for
    for (size_t i = 0; i < num_threads; i++) {
        size_t inner_sum = 0;
        unsigned int seed = omp_get_thread_num();
    
        for (size_t i = 0; i < (size_t) n / num_threads; i++) {
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
    size_t num_threads = omp_get_max_threads();

    double startTime = omp_get_wtime();

    double result = montecarlo(N, num_threads);
    double endTime = omp_get_wtime();
	printf("%2.3fs (N=%d, Result=%f)\n", endTime-startTime, N, result);

}