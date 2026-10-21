#include "BoundaryCondition.h"
#include <iostream>

BoundaryCondition::BoundaryCondition(Node* node, int dof, double value)
    : node(node), dof(dof), value(value) {}

Node* BoundaryCondition::getNode() const {
    return node;
}

int BoundaryCondition::getDof() const {
    return dof;
}

double BoundaryCondition::getValue() const {
    return value;
}

void BoundaryCondition::print() const {
    std::cout << "Boundary Condition: Node "
              << node->getId()
              << ", DOF " << dof
              << ", Value = " << value
              << std::endl;
}