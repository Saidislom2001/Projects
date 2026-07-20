#include <iostream>

class Counter {
public:
    static int next() {
        return cnt++;
    }
private:
    inline static int cnt = 0; // Static member variable to keep track of the count
};


int main() {
    
    Counter c1, c2, c3;
    std::cout << "Counter 1: " << c1.next() << std::endl;
    std::cout << "Counter 2: " << c2.next() << std::endl;
    std::cout << "Counter 3: " << c3.next() << std::endl;
    return 0;
}