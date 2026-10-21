#include "Mesh.h"
#include <iostream>

Mesh::~Mesh() {
    for (Node* node : nodes) {
        delete node;
    }

    for (Material* material : materials) {
        delete material;
    }

    for (Element* element : elements) {
        delete element;
    }
}

void Mesh::addNode(Node* node) {
    nodes.push_back(node);
}

void Mesh::addMaterial(Material* material) {
    materials.push_back(material);
}

void Mesh::addElement(Element* element) {
    elements.push_back(element);
}

Node* Mesh::getNode(int index) const {
    return nodes[index];
}

Material* Mesh::getMaterial(int index) const {
    return materials[index];
}

Element* Mesh::getElement(int index) const {
    return elements[index];
}

int Mesh::numberOfNodes() const {
    return nodes.size();
}

int Mesh::numberOfMaterials() const {
    return materials.size();
}

int Mesh::numberOfElements() const {
    return elements.size();
}

void Mesh::print() const {
    std::cout << "\n--- Mesh Info ---" << std::endl;

    std::cout << "Nodes:" << std::endl;
    for (Node* node : nodes) {
        node->print();
    }

    std::cout << "\nMaterials:" << std::endl;
    for (Material* material : materials) {
        material->print();
    }

    std::cout << "\nElements:" << std::endl;
    for (Element* element : elements) {
        element->print();
    }
}