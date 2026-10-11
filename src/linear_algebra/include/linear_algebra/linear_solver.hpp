#pragma once

#include "core/types.hpp"

#include "linear_algebra/vector.hpp"
#include "linear_algebra/dense_matrix.hpp"

namespace cfd {

class LinearSolver {
public:
  LinearSolver() = default;
  explicit LinearSolver(usize number_of_cells);
  virtual ~LinearSolver() = default;

  void set_coefficient_matrix(const DenseMatrix &coefficient_matrix);
  void set_right_hand_side(const ColumnVector &right_hand_side);
  virtual ColumnVector solve(usize max_iterations,
                             real convergence_threshold) const = 0;

protected:
  DenseMatrix coefficient_matrix_{};
  ColumnVector right_hand_side_{};
};

} // namespace cfd
