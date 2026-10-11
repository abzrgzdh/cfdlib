#include "linear_algebra/linear_solver.hpp"

namespace cfd {

LinearSolver::LinearSolver(usize number_of_cells)
    : coefficient_matrix_(number_of_cells, number_of_cells),
      right_hand_side_(number_of_cells) {}

void
LinearSolver::set_coefficient_matrix(const DenseMatrix &coefficient_matrix) {
  coefficient_matrix_ = coefficient_matrix;
}

void LinearSolver::set_right_hand_side(const ColumnVector &right_hand_side) {
  right_hand_side_ = right_hand_side;
}

} // namespace cfd
