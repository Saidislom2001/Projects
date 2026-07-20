# Parallel Vector Operations

A C++ project using POSIX threads to perform parallel vector operations.

## Operations

- Vector addition: `A + B`
- Vector subtraction: `A - B`
- Element-wise multiplication: `A * B`
- Dot product: `A · B`

## Concepts Practiced

- POSIX threads
- Work partitioning
- Shared memory
- Local reductions
- False sharing awareness

## Build

```bash
g++ main.cpp VectorOps.cpp -o vector_ops -pthread