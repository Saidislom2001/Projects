#include "Assembler.h"
#include "TrussElement2D.h"

#include <Eigen/Sparse>
#include <Eigen/Dense>
#include <iostream>
#include <vector>

Assembler::Assembler(Mesh* mesh)
    : mesh(mesh) {}

void Assembler::assembleStiffnessMatrix() {
    int totalDofs = mesh->numberOfNodes() * 2;

    globalK.resize(totalDofs, totalDofs);

    std::vector<Eigen::Triplet<double>> triplets;

    for (int e = 0; e < mesh->numberOfElements(); e++) {
        Element* element = mesh->getElement(e);

        TrussElement2D* truss = dynamic_cast<TrussElement2D*>(element);

        if (truss == nullptr) {
            std::cout << "Error: element is not TrussElement2D" << std::endl;
            continue;
        }

        auto localK = truss->stiffnessMatrix();
        auto nodes = truss->getNodes();

        int n1 = nodes[0]->getId() - 1;
        int n2 = nodes[1]->getId() - 1;

        std::vector<int> dofs = {
            2 * n1,
            2 * n1 + 1,
            2 * n2,
            2 * n2 + 1
        };

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                triplets.push_back(Eigen::Triplet<double>(
                    dofs[i],
                    dofs[j],
                    localK[i][j]
                ));
            }
        }
    }

    globalK.setFromTriplets(triplets.begin(), triplets.end());
}

void Assembler::assembleForceVector(const std::vector<Load>& loads) {
    int totalDofs = mesh->numberOfNodes() * 2;

    globalF = Eigen::VectorXd::Zero(totalDofs);

    for (const Load& load : loads) {
        int nodeIndex = load.getNode()->getId() - 1;
        int dof = load.getDof();
        int globalDof = 2 * nodeIndex + dof;

        globalF(globalDof) += load.getValue();
    }
}

void Assembler::applyBoundaryConditions(const std::vector<BoundaryCondition>& bcs) {
    Eigen::MatrixXd denseK = Eigen::MatrixXd(globalK);

    for (const BoundaryCondition& bc : bcs) {
        int nodeIndex = bc.getNode()->getId() - 1;
        int dof = bc.getDof();
        int globalDof = 2 * nodeIndex + dof;

        denseK.row(globalDof).setZero();
        denseK.col(globalDof).setZero();

        denseK(globalDof, globalDof) = 1.0;
        globalF(globalDof) = bc.getValue();
    }

    globalK = denseK.sparseView();
}

Eigen::VectorXd Assembler::solve() {
    Eigen::SimplicialLDLT<Eigen::SparseMatrix<double>> solver;

    solver.compute(globalK);

    if (solver.info() != Eigen::Success) {
        std::cout << "Matrix decomposition failed." << std::endl;
        return Eigen::VectorXd();
    }

    Eigen::VectorXd displacement = solver.solve(globalF);

    if (solver.info() != Eigen::Success) {
        std::cout << "Solving failed." << std::endl;
        return Eigen::VectorXd();
    }

    return displacement;
}

void Assembler::printGlobalK() const {
    std::cout << "\n--- Global Stiffness Matrix K ---" << std::endl;

    Eigen::MatrixXd denseK = Eigen::MatrixXd(globalK);

    for (int i = 0; i < denseK.rows(); i++) {
        for (int j = 0; j < denseK.cols(); j++) {
            std::cout << denseK(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

void Assembler::printGlobalF() const {
    std::cout << "\n--- Global Force Vector F ---" << std::endl;

    for (int i = 0; i < globalF.size(); i++) {
        std::cout << globalF(i) << std::endl;
    }
}