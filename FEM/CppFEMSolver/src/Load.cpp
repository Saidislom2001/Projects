#include "Load.h"
#include <iostream>

Load::Load(Node* node, int dof, double value)
    : node(node), dof(dof), value(value) {}

Node* Load::getNode() const {
    return node;
}

int Load::getDof() const {
    return dof;
}

double Load::getValue() const {
    return value;
}

void Load::print() const {
    std::cout << "Load: Node "
              << node->getId()
              << ", DOF " << dof
              << ", Value = " << value
              << std::endl;
}