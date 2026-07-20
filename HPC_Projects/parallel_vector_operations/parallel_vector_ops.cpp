#include <iostream>
#include <vector>
#include <stdlib.h>    // atoi
#include <pthread.h>
#include <stdio.h>     // printf

using namespace std;

struct Bounds{
    int tid;
    int start;
    int end;

    const vector<double>* A;
    const vector<double>* B;

    vector<double>* add;
    vector<double>* sub;
    vector<double>* mul;

    double partialDot;
};

void* VectorOps(void* arg)
{
    Bounds* data = (Bounds*)(arg);		// unpack arguments
    int tid  = data->tid;
    int start = data->start;
    int end   = data->end;

    const vector<double>* A = data->A;
    const vector<double>* B = data->B;

    vector<double>* add = data->add;
    vector<double>* sub = data->sub;
    vector<double>* mul = data->mul;

    double localDot = 0.0;

    for(int i = start; i < end; ++i) {
        (*add)[i] = (*A)[i] + (*B)[i];
        (*sub)[i] = (*A)[i] - (*B)[i];
        (*mul)[i] = (*A)[i] * (*B)[i];
        localDot += (*A)[i] * (*B)[i];
    }

    data->partialDot = localDot;

    pthread_exit(NULL);
}

int main(int argc, char **argv){

    if(argc != 3) {
        cout << "Usage: ./vector_ops <vector_size> <num_threads>" << endl;
        return 1;
    }

    int N = atoi(argv[1]); // Vector size
    int T = atoi(argv[2]); // Number of threads

    if(T <= 0 || N <= 0) {
        cout << "Vector size and number of threads must be positive integers." << endl;
        return 1;
    }

    vector<double> A(N), B(N), add(N), sub(N), mul(N);

    // Initialize vectors A and B
    for(int i = 0; i < N; ++i) {
        A[i] = i + 1;
        B[i] = (i + 1) * 2;
    }

    vector<pthread_t> threadID(T);           // thread IDs
    vector<Bounds> args(T);                  // thread arguments

    for(int t = 0; t < T; ++t) {
        int start = (N / T) * t;
        int end = (t == T - 1) ? N : (N / T) * (t + 1); // Last thread may take the remainder

        args[t] = {t, start, end, &A, &B, &add, &sub, &mul, 0.0};
        pthread_create(&threadID[t], nullptr, VectorOps, &args[t]);
    }

    double dotProduct = 0.0;

    // Wait for all threads to complete
    for(int t = 0; t < T; ++t) {
        pthread_join(threadID[t], nullptr);
        dotProduct += args[t].partialDot;
    }

    cout << "\nFirst 10 results:\n";
    for (int i = 0; i < min(N, 10); ++i) {
        cout << "i=" << i
                  << " A+B=" << add[i]
                  << " A-B=" << sub[i]
                  << " A*B=" << mul[i]
                  << "\n";
    }

    cout << "Dot product: " << dotProduct << endl;

    return 0;
}