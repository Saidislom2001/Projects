#include "TrussElement2D.h"
#include <iostream>
#include <cmath>

TrussElement2D::TrussElement2D(int id, Material* material, const std::vector<Node*>& nodes)
    : Element(id, material, nodes) {}

double TrussElement2D::length() const {
    double dx = nodes[1]->getX() - nodes[0]->getX();
    double dy = nodes[1]->getY() - nodes[0]->getY();

    return std::sqrt(dx * dx + dy * dy);
}

double TrussElement2D::cosTheta() const {
    return (nodes[1]->getX() - nodes[0]->getX()) / length();
}

double TrussElement2D::sinTheta() const {
    return (nodes[1]->getY() - nodes[0]->getY()) / length();
}

std::vector<std::vector<double>> TrussElement2D::stiffnessMatrix() const {
    double E = material->getYoungModulus();
    double A = material->getArea();
    double L = length();

    double c = cosTheta();
    double s = sinTheta();

    double k = E * A / L;

    return {
        { k*c*c,  k*c*s, -k*c*c, -k*c*s },
        { k*c*s,  k*s*s, -k*c*s, -k*s*s },
        {-k*c*c, -k*c*s,  k*c*c,  k*c*s },
        {-k*c*s, -k*s*s,  k*c*s,  k*s*s }
    };
}

void TrussElement2D::print() const {
    std::cout << "2D Truss Element " << id << std::endl;
    std::cout << "Length = " << length() << std::endl;
    std::cout << "cos(theta) = " << cosTheta() << std::endl;
    std::cout << "sin(theta) = " << sinTheta() << std::endl;

    auto K = stiffnessMatrix();

    std::cout << "Element stiffness matrix:" << std::endl;
    for (const auto& row : K) {
        for (double value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}