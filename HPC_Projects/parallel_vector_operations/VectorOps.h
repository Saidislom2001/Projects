#ifndef VECTOROPS_H
#define VECTOROPS_H

#include <vector>

struct VectorResults {
    std::vector<double> add;
    std::vector<double> sub;
    std::vector<double> mul;
    double dotProduct;

};

VectorResults parallelVectorOps(
    const std::vector<double>& A,
    const std::vector<double>& B,
    int numThreads
);

#endif // VECTOROPS_H