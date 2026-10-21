#include <stdio.h>
#include <cuda_runtime.h>

// Device kernel running on the GPU
__global__ void helloFromGPU() {
    // Obtain unique thread and block indices
    printf("Hello World from GPU thread %d in block %d!\n", threadIdx.x, blockIdx.x);
}

int main() {
    printf("Hello World from CPU host!\n");

    // Launch kernel with 2 blocks, each containing 4 threads (8 total threads)
    helloFromGPU<<<2, 4>>>();

    // Synchronize host CPU with device GPU to flush printf output before exit
    cudaDeviceSynchronize();

    return 0;
}
