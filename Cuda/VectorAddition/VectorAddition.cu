#include <iostream>
#include <cuda_runtime.h>
using namespace std;

// 1. Define the Cuda Kernel
// The '__global__' specifier tells the compiler this runs on the GPU (Device)
// but is called from the CPU (Host). It must return void.
__global__ void vectorMultiply(const float* A, const float* B, float* C, int N){
    // Calculate the global thread index
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    // Boundary check to ensure we don't access out of bounds memory
    if (i < N) {
        C[i] = A[i] * B[i];
    }
}

int main() {
    // Array size (let's say we want to add two vectors of size 1 million)
    const int N = 1'000'000; // 1 million elements
    const size_t size = N * sizeof(float); // Size in bytes

    // --- CPU (Host) memory allocation ---
    float* h_A = new float[N]; // Host array A
    float* h_B = new float[N]; // Host array B
    float* h_C = new float[N]; // Host array C (result)

    // Initialize host arrays with some values
    for (int i = 0; i < N; ++i) {
        h_A[i] = static_cast<float>(i); // A[i] = i
        h_B[i] = static_cast<float>(2 * i); // B[i] = 2*i
    }

    // --- GPU (Device) memory allocation ---
    float *d_A, *d_B, *d_C; // Device pointers
    // cudaMalloc allocates memory on the GPU. It takes a pointer to the device pointer and the size in bytes.
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);

    // Data transfer from Host to Device
    // cudaMemcpy copies data between Host and Device. It takes the destination pointer, source pointer, size in bytes, and the direction of transfer.
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // --- Execution configuration ---
    // We want 256 threads per block (a standard block size)
    int blockSize = 256;
    int numBlocks = (N + blockSize - 1) / blockSize; // Use ceiling division

    cout << "Launching kernel with " << numBlocks << " blocks of " << blockSize << " threads each." << endl;

    // Launch the kernel
    vectorMultiply<<<numBlocks, blockSize>>>(d_A, d_B, d_C, N);

    // Data transfer from Device to Host
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    // Verify the result
    bool success = true;
    for (int i = 0; i < N; ++i) {
        if (h_C[i] != h_A[i] * h_B[i]) {
            success = false;
            cout << "Error at index " << i << ": " << h_C[i] << " != " << h_A[i] * h_B[i] << endl;
            break;
        }
    }

    if (success) {
        cout << "Vector multiplication completed successfully!" << endl;
    } else {
        cout << "Vector multiplication failed!" << endl;
    }


    // Free GPU memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    // Free CPU memory
    delete[] h_A;
    delete[] h_B;
    delete[] h_C;

    return 0;
}