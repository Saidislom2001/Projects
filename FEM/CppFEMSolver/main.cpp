#include "Mesh.h"
#include "TrussElement2D.h"
#include "BoundaryCondition.h"
#include "Load.h"
#include "Assembler.h"

#include <vector>
#include <iostream>

int main() {
    Mesh mesh;

    mesh.addNode(new Node(1, 0.0, 0.0));
    mesh.addNode(new Node(2, 3.0, 4.0));

    mesh.addMaterial(new Material(1, "Steel", 210e9, 0.01));

    std::vector<Node*> elementNodes = {
        mesh.getNode(0),
        mesh.getNode(1)
    };

    mesh.addElement(new TrussElement2D(1, mesh.getMaterial(0), elementNodes));

    std::vector<BoundaryCondition> bcs;
    bcs.push_back(BoundaryCondition(mesh.getNode(0), 0, 0.0));
    bcs.push_back(BoundaryCondition(mesh.getNode(0), 1, 0.0));
    bcs.push_back(BoundaryCondition(mesh.getNode(1), 0, 0.0));

    std::vector<Load> loads;
    loads.push_back(Load(mesh.getNode(1), 1, -1000.0));

    mesh.print();

    std::cout << "\n--- Boundary Conditions ---" << std::endl;
    for (const BoundaryCondition& bc : bcs) {
        bc.print();
    }

    std::cout << "\n--- Loads ---" << std::endl;
    for (const Load& load : loads) {
        load.print();
    }

    Assembler assembler(&mesh);
    assembler.assembleStiffnessMatrix();
    assembler.assembleForceVector(loads);

    std::cout << "\nBefore boundary conditions:";
    assembler.printGlobalK();
    assembler.printGlobalF();

    assembler.applyBoundaryConditions(bcs);

    std::cout << "\nAfter boundary conditions:";
    assembler.printGlobalK();
    assembler.printGlobalF();

    Eigen::VectorXd displacements = assembler.solve();

    std::cout << "\n--- Displacements ---" << std::endl;
    for (int i = 0; i < displacements.size(); i++) {
        std::cout << "u[" << i << "] = " << displacements[i] << std::endl;
    }
    return 0;
}