#ifndef BOUNDARYCONDITION_H
#define BOUNDARYCONDITION_H

#include "Node.h"

class BoundaryCondition {
private:
    Node* node;
    int dof;
    double value;

public:
    BoundaryCondition(Node* node, int dof, double value);

    Node* getNode() const;
    int getDof() const;
    double getValue() const;

    void print() const;
};

#endif