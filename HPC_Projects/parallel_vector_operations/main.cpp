#include "VectorOps.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <algorithm>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "Usage: ./vector_ops <vector_size> <num_threads>\n";
        return 1;
    }

    int N = std::atoi(argv[1]);
    int numThreads = std::atoi(argv[2]);

    if (N <= 0 || numThreads <= 0) {
        std::cout << "Error: vector size and thread count must be positive.\n";
        return 1;
    }

    std::vector<double> A(N);
    std::vector<double> B(N);

    for (int i = 0; i < N; ++i) {
        A[i] = i + 1;
        B[i] = 2 * (i + 1);
    }

    auto start = std::chrono::high_resolution_clock::now();
    VectorResults results = parallelVectorOps(A, B, numThreads);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    
    std::cout << "\nVector size: " << N << "\n";
    std::cout << "Threads: " << numThreads << "\n";
    std::cout << "Execution time: " << duration.count() << " ms\n";

    std::cout << "\nFirst 10 results:\n";

    for (int i = 0; i < std::min(N, 10); ++i) {
        std::cout << "i = " << i
                  << " | A+B = " << results.add[i]
                  << " | A-B = " << results.sub[i]
                  << " | A*B = " << results.mul[i]
                  << "\n";
    }

    std::cout << "\nDot product = " << results.dotProduct << "\n";

    return 0;
}