#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

// Now taking N as a parameter
long long sum_row_major(const std::vector<int>& matrix, size_t N) {
    long long sum = 0;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            sum += matrix[i * N + j];
        }
    }
    return sum;
}

long long sum_column_major(const std::vector<int>& matrix, size_t N) {
    long long sum = 0;
    for (size_t j = 0; j < N; ++j) {
        for (size_t i = 0; i < N; ++i) {
            sum += matrix[i * N + j];
        }
    }
    return sum;
}

void run_sweep() {
    std::vector<size_t> sizes = {256, 512, 1024, 2048, 4096, 8192, 10000}; // Example sizes

    std::cout << std::left << std::setw(8) << "N"
              << std::setw(12) << "Size (MB)"
              << std::setw(18) << "Row Major (ms)"
                << std::setw(18) << "Column Major (ms)" << std::endl;

    std::cout << std::string(56, '-') << std::endl;

    for (size_t N : sizes) {
        size_t total_elements = N * N;
        double size_mb = static_cast<double>(total_elements * sizeof(int)) / (1024 * 1024);

        std::vector<int> matrix(total_elements, 1);

        // Scale iterations to ensure at least ~100M operations per test
        // This prevents microsecond-level clock jitter on small N
        int iterations = (100000000 / total_elements) + 1;

        // Measure row-major access time
        auto start_row = std::chrono::high_resolution_clock::now();
        long long dummy_row = 0;
        for (int iter = 0; iter < iterations; ++iter) {
            dummy_row += sum_row_major(matrix, N);
        }
        
        auto end_row = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> diff_row = end_row - start_row;
        double ns_per_el_row = (diff_row.count() * 1e9) / (iterations * total_elements);

        // Measure column-major access time
        auto start_col = std::chrono::high_resolution_clock::now();
        long long dummy_col = 0;
        for (int i = 0; i < iterations; ++i) {
            dummy_col += sum_column_major(matrix, N);
        }

        auto end_col = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff_col = end_col - start_col;
        double ns_per_el_col = (diff_col.count() * 1e9) / (total_elements * iterations);

        std::cout << std::left << std::setw(8) << N 
                  << std::setw(12) << std::fixed << std::setprecision(2) << size_mb 
                  << std::setw(18) << std::fixed << std::setprecision(3) << ns_per_el_row 
                  << std::setw(18) << std::fixed << std::setprecision(3) << ns_per_el_col 
                  << " (Sum check: " << (dummy_row == dummy_col ? "OK" : "FAIL") << ")\n";

    }
}

int main() {
    run_sweep();
    return 0;
}