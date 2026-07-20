#include <iostream>
#include <cuda_runtime.h>

// 1. Define the Cuda Kernel
// The '__global__' specifier tells the compiller this runs on the GPU (Divice)
// but is called from the CPU (Host). It must return void.

__global__ void helloFromGPU() {
    // Thread index variables help identify which thread is running
    int tid = threadIdx.x;
    int bid = blockIdx.x;

    printf("Hello World from GPU! Thread ID: %d, Block ID: %d\n", tid, bid);
}

int main() {
    std::cout << "Hello World from CPU!" << std::endl;
    // 2. Launch the kernel on the GPU
    // Syntax: kernelName<<<NumBlocks, NumThreadsPerBlock>>>(kernelArguments);
    // Here we launch 2 blocks with 4 threads per block. The kernel will be executed by 8 threads in parallel.
    helloFromGPU<<<2, 4>>>();

    // 3. Sinchronize the device
    // Since kernel launches are asynchronous, we need to synchronize the device to ensure that the kernel has completed before we exit the program.
    cudaError_t err = cudaDeviceSynchronize();

    // 4. Check for errors
    if (err != cudaSuccess) {
        std::cerr << "Error occurred while synchronizing device." << std::endl;
        return -1;
    }

    // 5. Reset the device
    err = cudaDeviceReset();

    if (err != cudaSuccess) {
        std::cerr << "Error occurred while resetting device." << std::endl;
        return -1;
    }

    std::cout << "Back to CPU!" << std::endl;

    // 6. Return success
    return 0;

    /*7. Note: The program will print "Hello World from CPU!" from the CPU
     and "Hello World from GPU!" from the GPU. The order of the output may 
     vary due to the asynchronous nature of kernel launches.*/





}

