#ifndef LOAD_H
#define LOAD_H

#include "Node.h"

class Load {
private:
    Node* node;
    int dof;        // 0 = Fx, 1 = Fy
    double value;   // Force magnitude

public:
    Load(Node* node, int dof, double value);

    Node* getNode() const;
    int getDof() const;
    double getValue() const;

    void print() const;
};

#endif