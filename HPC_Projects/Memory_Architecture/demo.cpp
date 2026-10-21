#include <iostream>

int main() {
    std::cout << "Give an integer: ";
    int a;
    std::cin >> a;

    if (a>0 && a%2 == 0) {
        std::cout << "An integer is positive and even\n";
    }
    else if (a<0 && a%2 == 0)
    {
        std::cout << "An integer is negative and even\n";
    }
    else if (a>0 && a%2 != 0)
    {
        std::cout << "An integer is positive and odd\n";
    }
    else if (a<0 && a%2 != 0)
    {
        std::cout << "An integer is negative and odd\n";
    }
    else {
        std::cout << "An integer is zero\n";
    }
    
    return 0;
    
}
