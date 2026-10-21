#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "Mesh.h"
#include "Load.h"
#include "BoundaryCondition.h"

#include <Eigen/Sparse>
#include <Eigen/Dense>
#include <vector>

class Assembler {
private:
    Mesh* mesh;
    Eigen::SparseMatrix<double> globalK;
    Eigen::VectorXd globalF;

public:
    Assembler(Mesh* mesh);

    void assembleStiffnessMatrix();
    void assembleForceVector(const std::vector<Load>& loads);
    void applyBoundaryConditions(const std::vector<BoundaryCondition>& bcs);

    Eigen::VectorXd solve();

    void printGlobalK() const;
    void printGlobalF() const;
};

#endif
