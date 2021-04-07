CFLAGS = -std=gnu11 -Wall -Wextra -lm -O3 -fopenmp 

.PHONY: all
all: montecarlo_critical montecarlo_atomic montecarlo_reduction

.PHONY: clean
clean:
	$(RM) montecarlo_critical montecarlo_atomic montecarlo_reduction

montecarlo_critical: montecarlo_critical.c

montecarlo_atomic: montecarlo_atomic.c

montecarlo_reduction: montecarlo_reduction.c
