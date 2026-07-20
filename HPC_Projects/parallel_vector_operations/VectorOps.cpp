#include "VectorOps.h"
#include <iostream>
#include <pthread.h>

struct ThreadData {
    int tid;
    int start;
    int end;
    const std::vector<double>* A;
    const std::vector<double>* B;
    std::vector<double>* add;
    std::vector<double>* sub;
    std::vector<double>* mul;
    double partialDot;
};

void* VectorOpsThread(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int start = data->start;
    int end = data->end;

    const std::vector<double>* A = data->A;
    const std::vector<double>* B = data->B;

    std::vector<double>* add = data->add;
    std::vector<double>* sub = data->sub;
    std::vector<double>* mul = data->mul;

    double localDot = 0.0;

    for (int i = start; i < end; ++i) {
        (*add)[i] = (*A)[i] + (*B)[i];
        (*sub)[i] = (*A)[i] - (*B)[i];
        (*mul)[i] = (*A)[i] * (*B)[i];
        localDot += (*A)[i] * (*B)[i];
    }

    data->partialDot = localDot;

    pthread_exit(NULL);
}

VectorResults parallelVectorOps(
    const std::vector<double>& A,
    const std::vector<double>& B,
    int numThreads
) {
    int N = A.size();
    VectorResults results;
    results.add.resize(N);
    results.sub.resize(N);
    results.mul.resize(N);
    results.dotProduct = 0.0;

    std::vector<pthread_t> threads(numThreads);
    std::vector<ThreadData> threadData(numThreads);

    int chunkSize = (N + numThreads - 1) / numThreads; // Ceiling division

    for (int t = 0; t < numThreads; ++t) {
        threadData[t].tid = t;
        threadData[t].start = t * chunkSize;
        threadData[t].end = std::min((t + 1) * chunkSize, N);
        threadData[t].A = &A;
        threadData[t].B = &B;
        threadData[t].add = &results.add;
        threadData[t].sub = &results.sub;
        threadData[t].mul = &results.mul;

        pthread_create(&threads[t], NULL, VectorOpsThread, (void*)&threadData[t]);
    }

    for (int t = 0; t < numThreads; ++t) {
        pthread_join(threads[t], NULL);
        results.dotProduct += threadData[t].partialDot;
    }

    return results;
}
