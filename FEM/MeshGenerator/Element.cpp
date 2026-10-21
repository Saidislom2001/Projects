#include "Element.h"
#include <iostream>

Element::Element(int id, const vector<int>& nodeIDs, int materialId) : id(id), nodeIDs(nodeIDs), materialId(materialId) {}
int Element::getId() const {
    return id;
}

const vector<int>& Element::getNodeIDs() const {
    return nodeIDs;
}

void Element::print() const {
    std::cout << "Element ID: " << id << ", Node IDs: ";
    for (int nodeId : nodeIDs) {
        std::cout << nodeId << " ";
    }

    std::cout << ", Material ID: " << materialId << std::endl;
}

int Element::getMaterialId() const {
    return materialId;
}


