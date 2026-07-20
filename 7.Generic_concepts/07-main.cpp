#include <iostream>
#include "07-vector.h"

int main(){

    // test the implementation
    Vector<int> x;
    Vector<double> y(5, 12.0);

    try{
        std::cout << "y[3]:  " << y[3] << std::endl;
        std::cout << "y[15]: " << y[15] << std::endl;
    }
    catch(std::out_of_range& err){
        std::cout << "Some bad access, aborting ..." << std::endl;
        return -1;
    }
}












