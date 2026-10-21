#ifndef MESH_H
#define MESH_H

#include "Node.h"
#include "Material.h"
#include "Element.h"

#include <vector>

class Mesh {
private:
    std::vector<Node*> nodes;
    std::vector<Material*> materials;
    std::vector<Element*> elements;

public:
    ~Mesh();

    void addNode(Node* node);
    void addMaterial(Material* material);
    void addElement(Element* element);

    Node* getNode(int index) const;
    Material* getMaterial(int index) const;
    Element* getElement(int index) const;

    int numberOfNodes() const;
    int numberOfMaterials() const;
    int numberOfElements() const;

    void print() const;
};

#endif