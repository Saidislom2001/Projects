#ifndef ELEMENT_H
#define ELEMENT_H
#include "Node.h"
#include "Material.h"
#include <vector>

class Element
{
protected:
    /* data */
    int id;
    Material* material;
    std::vector<Node*> nodes;
public:
    Element(int id, Material* material, const std::vector<Node*>& nodes);
    virtual ~Element();

    int getId() const;
    Material* getMaterial() const;
    std::vector<Node*> getNodes() const;

    virtual void print() const;
};

#endif