#include "num_threads.h"
#include "interface.h"
#include <iostream>
#include "experiments.h"
#include <omp.h>
#include <iostream>

int main() {

    unsigned T = get_num_threads();
    int N = 10000000;
    unsigned* V = new unsigned[N];

    run_experiments_for(V, N, randomize, 10, 100);

    return 0;
}