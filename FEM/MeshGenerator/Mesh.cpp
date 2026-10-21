#include "Mesh.h"
#include <iostream>
#include <fstream>

using namespace std;

Mesh::Mesh(int nx, int ny, double width, double height, const Material& material) : nx(nx), ny(ny), width(width), height(height), material(material) {}

void Mesh::generateNodes() {
    nodes.clear();
    double dx = width / nx;
    double dy = height / ny;

    int id = 1;

    for (int j = 0; j <= ny; j++) {
        for (int i = 0; i <= nx; i++) {
            double x = i * dx;
            double y = j * dy;
            nodes.push_back(Node(id, x, y));
            id++;
        }
    }
}

void Mesh::generateElements() {
    elements.clear();
    int id = 1;

    for (int j = 0; j < ny; j++) {
        for (int i = 0; i < nx; i++) {
            int n1 = j * (nx + 1) + i + 1;
            int n2 = n1 + 1;
            int n3 = n2 + (nx + 1);
            int n4 = n3 - 1;

            vector<int> nodeIDs = {n1, n2, n3, n4};
            elements.push_back(Element(id, nodeIDs, material.getId()));
            id++;
            
        }
    }
}

void Mesh::printNodes() const {
    cout << "Nodes:" << endl;
    for (const auto& node : nodes) {
        node.print();
    }
}

void Mesh::printElements() const {
    cout << "Elements:" << endl;
    for (const Element& element : elements) {
        element.print();
    }
}

void Mesh::printMesh() const {
    printNodes();
    cout << endl;
    printElements();
    cout << endl;
    material.print();
}



void Mesh::addLoad(const Load& load) {
    if (!isValidNodeId(load.getNodeId())) {
        cout << "Error: Node ID " << load.getNodeId()
             << " does not exist. Load not added." << endl;
        return;
    }

    loads.push_back(load);
}

void Mesh::printLoads() const {
    cout << "Loads:" << endl;

    if (loads.empty()) {
        cout << "No loads applied." << endl;
        return;
    }

    for (const Load& load : loads) {
        load.print();
    }
}


void Mesh::saveToFile(const string& filename) const {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    outFile << "Nodes:" << endl;
    for (const auto& node : nodes) {
        outFile << node.getId() << " " << node.getX() << " " << node.getY() << endl;
    }

    outFile << endl << "Elements:" << endl;
    for (const Element& element : elements) {
        outFile << element.getId();
        for (int nodeId : element.getNodeIDs()) {
            outFile << " " << nodeId;
        }
        outFile << endl;
    }

    outFile.close();
    cout << "Mesh saved to file: " << filename << endl;
}