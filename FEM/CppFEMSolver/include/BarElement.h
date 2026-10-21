#ifndef BARELEMENT_H
#define BARELEMENT_H

#include "Element.h"
#include <vector>

class BarElement : public Element {
public:
    BarElement(int id, Material* material, const std::vector<Node*>& nodes);
    
    double length() const;
    std::vector<std::vector<double>> stiffnessMatrix() const;

    void print() const override;

};

#endif
