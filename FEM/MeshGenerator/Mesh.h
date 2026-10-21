#ifndef MESH_H
#define MESH_H

#include "Element.h"
#include "Material.h"
#include "Load.h"
#include "Node.h"
#include <vector>
#include <string>

using namespace std;

class Mesh {
    private:
        int nx;
        int ny;
        double width;
        double height;
        vector<Load> loads;
        Material material;
        vector<Node> nodes;
        vector<Element> elements;
    
    public:
        Mesh(int nx, int ny, double width, double height, const Material& material);

        void generateNodes();
        void generateElements();

        void printNodes() const;
        void printElements() const;
        void printMesh() const;

        void addLoad(const Load& load);
        void printLoads() const;
        

        void saveToFile(const string& filename) const;
};

#endif // MESH_H