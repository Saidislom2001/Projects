#pragma once
#include <Eigen/Dense>
#include <vector>
#include <string>

/**
 * @brief 2D Node in the finite element mesh.
 *
 * Stores spatial coordinates and boundary condition information
 * (Dirichlet flags with prescribed values, and applied nodal loads).
 */
class Node {
public:
    Node(int id, double x, double y)
        : id_(id), coords_(x, y), ndof_(2) {
        dof_indices_.resize(ndof_);
        dirichlet_flags_.setZero();
        dirichlet_values_.setZero();
        nodal_loads_.setZero();
    }

    int getId() const noexcept { return id_; }
    const Eigen::Vector2d& getCoords() const noexcept { return coords_; }
    double x() const noexcept { return coords_(0); }
    double y() const noexcept { return coords_(1); }

    int getNumDOF() const noexcept { return ndof_; }

    // --- Global DOF management -------------------------------------------------
    const std::vector<int>& getDOFIndices() const noexcept { return dof_indices_; }
    void setDOFIndices(const std::vector<int>& indices) { dof_indices_ = indices; }

    // --- Dirichlet BCs ---------------------------------------------------------
    void setDirichlet(int local_dof, double value) {
        dirichlet_flags_(local_dof)  = 1;
        dirichlet_values_(local_dof) = value;
    }
    bool hasDirichlet(int local_dof) const { return dirichlet_flags_(local_dof) != 0; }
    double getDirichletValue(int local_dof) const { return dirichlet_values_(local_dof); }

    // --- Nodal (point) loads ---------------------------------------------------
    void addLoad(int local_dof, double value) { nodal_loads_(local_dof) += value; }
    double getLoad(int local_dof) const { return nodal_loads_(local_dof); }

private:
    int id_;
    Eigen::Vector2d coords_;
    int ndof_;

    std::vector<int> dof_indices_;      ///< global DOF indices for this node
    Eigen::Vector2i  dirichlet_flags_;  ///< 0 = free, 1 = prescribed
    Eigen::Vector2d  dirichlet_values_;
    Eigen::Vector2d  nodal_loads_;
};
