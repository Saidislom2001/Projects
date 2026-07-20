# include <iostream>
# include <algorithm>
# include <vector>

int main() {
    std::vector<int> v = {4,2,3,7,9,4,5};

    // count number of items less than 5
    int count = std::count_if(v.begin(), v.end(), [](int x) { return x < 5; });

    std::cout << "Number of items less than 5: " << count << std::endl;

    // find the first occurance of 7
    auto it = std::find_if(v.begin(), v.end(), [](int x) { return x == 7; });

    if (it != v.end()) {
        std::cout << "Found " << *it << " in the vector." << std::endl;
    } else {
        std::cout << "7 not found in the vector." << std::endl;
    }

    // sort the vector and print the sorted values
    std::sort(v.begin(), v.end());
    for (const auto& val : v) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}