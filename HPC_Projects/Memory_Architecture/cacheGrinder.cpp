#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

const size_t N = 10'000;

// Row-major: Sequential access
long long sum_row_major(const std::vector<int>& matrix) {
    long long sum = 0;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            sum += matrix[i * N + j];
        }
    }
    return sum;
}

// Column-major: Strided access
long long sum_column_major(const std::vector<int>& matrix) {
    long long sum = 0;
    for (size_t j = 0; j < N; ++j) {
        for (size_t i = 0; i < N; ++i) {
            sum += matrix[i * N + j];
        }
    }
    return sum;
}

void run_test(const std::string& name, long long (*func)(const std::vector<int>&), const std::vector<int>& matrix) {
    auto start = std::chrono::high_resolution_clock::now();
    long long result = func(matrix);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Calculate the bandwidth 
    double bytes_accessed = static_cast<double>(N) * N * sizeof(int);
    double gigabytes = bytes_accessed / 1e9;
    double bandwidth = gigabytes / elapsed.count();

    std::cout << std::left << std::setw(15) << name
                << " | Time: " << std::fixed << std::setprecision(6) << elapsed.count() << " s"
                << " | Bandwidth: " << std::fixed << std::setprecision(2) << bandwidth << " GB/s"
                << " | Sum: " << result
                << std::endl;
}

int main() {
    std::cout << "Allocating " << N << " x " << N << " matrix (" << (N * N * sizeof(int) / (1024 * 1024)) << " MB)...\n\n";
    std::vector<int> matrix(N * N, 1); // Initialize with 1s for simplicity

    run_test("Row-major", sum_row_major, matrix);
    run_test("Column-major", sum_column_major, matrix);

    return 0;
}