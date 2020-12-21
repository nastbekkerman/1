#ifdef __cplusplus
#define EXTERN_C extern "C"
#include <cstdio>

using std::fprintf;

#else

#define EXTERN_C
#include <stdio.h> 

#endif


#include <cmath>
#include <iostream>
#include <vector>
#include <thread>
#include <omp.h> //MSVC: /openmp, gcc: -fopenmp 
#include <ctime>
#include <iomanip>
#include "interface.h"
#include "num_threads.h"

#define A 1103515245
#define b 12345
#define c 4294967296



std::vector<unsigned> get_A(unsigned T) {

    std::vector<unsigned> result;
    result.reserve(T);
    result.emplace_back(A);
    for (unsigned i = 1; i < T + 1; i++) {
        result.emplace_back((result.back() * A) % c);
    }
    return result;

}


#ifdef _MSC_VER

constexpr std::size_t CACHE_LINE = std::hardware_destructive_interference_size;

#else

#define CACHE_LINE 64 

#endif


double randomize(unsigned* V, unsigned N, unsigned min, unsigned max) {

    unsigned T = get_num_threads();
    std::vector<unsigned> multipliers = get_A(T);
    double full_sum = 0;
    std::vector<double> partial_rand(T);
    std::vector<std::thread> threads;
    unsigned seed = std::time(0);
    for (std::size_t t = 0; t < T; ++t)
        threads.emplace_back([t, T, V, N, seed, &partial_rand, multipliers, min, max]() {
        auto At = multipliers.back();
        unsigned off = (b * (At - 1) / (A - 1)) % c;
            unsigned x = ((seed * multipliers[t]) % c + (b * (multipliers[t] - 1) / (A - 1)) % c) % c;
            double my_median = 0;
            for (size_t i = t; i < N; i += T) {
                V[i] = x % (max - min) + min ;
                my_median += V[i];
                x = (x * At) % c + off % c;
            }
            partial_rand[t] = my_median;
            });
    for (auto& thread : threads)
        thread.join();
    for (unsigned i = 0; i < T; ++i)
        full_sum += partial_rand.at(i);

    return full_sum / N;
}





