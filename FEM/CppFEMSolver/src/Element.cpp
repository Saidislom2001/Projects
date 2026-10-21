#include "Element.h"
#include <iostream>

Element::Element(int id, Material* material, const std::vector<Node*>& nodes)
    : id(id), material(material), nodes(nodes) {}


Element::~Element(){}

int Element::getId() const{
    return id;
}

Material* Element::getMaterial() const{
    return material;
}

std::vector<Node*> Element::getNodes() const{
    return nodes;
}

void Element::print()  const{
    std::cout << "Element " << id << std::endl;
    std::cout << "Nodes ";

    for (Node* node : nodes) {
        std::cout << node->getId() << " ";
    }
    std::cout << std::endl;
}
