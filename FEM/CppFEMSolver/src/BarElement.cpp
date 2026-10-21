#include "BarElement.h"
#include <iostream>
#include <cmath>

BarElement::BarElement(int id, Material* material, const std::vector<Node*>& nodes)
    :Element(id, material, nodes){}

double BarElement::length() const {
    double x1 = nodes[0]->getX();
    double x2 = nodes[1]->getX();

    return std::abs(x2-x1);
}

std::vector<std::vector<double>> BarElement::stiffnessMatrix() const {
    double E = material->getYoungModulus();
    double A = material->getArea();
    double L = length();

    double k = E * A / L;

    return {
        {k, -k},
        {-k, k}
        };
}

void BarElement::print() const {
    std::cout << "1D Bar Element " << id << std::endl;
    std::cout << "Length = " << length() << std::endl;

    auto K = stiffnessMatrix();

    std::cout << "Local stiffness matrix: " << std::endl;
    for (const auto& row : K){
        for (double value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}