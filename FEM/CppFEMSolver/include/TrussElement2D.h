#ifndef TRUSSELEMENT2D_H
#define TRUSSELEMENT2D_H

#include "Element.h"
#include <vector>

class TrussElement2D : public Element {
public:
    TrussElement2D(int id, Material* material, const std::vector<Node*>& nodes);

    double length() const;
    double cosTheta() const;
    double sinTheta() const;

    std::vector<std::vector<double>> stiffnessMatrix() const;

    void print() const override;
};

#endif