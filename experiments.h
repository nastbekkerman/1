#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#pragma once

typedef struct experiment_result_ {
    double result;
    double time_ms;
    double speedup;
} experiment_result;

experiment_result* run_experiments(unsigned* V, unsigned count, double (*accumulate)(unsigned*, unsigned, unsigned, unsigned), unsigned min, unsigned max);
void print_experiment_results(const experiment_result* results);
void run_experiments_for(unsigned* V, unsigned count, double (*accumulate)(unsigned*, unsigned, unsigned, unsigned), unsigned min, unsigned max);
