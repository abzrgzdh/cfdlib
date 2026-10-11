#pragma once

#include "core/types.hpp"
#include "linear_solver.hpp"

namespace cfd {

// Forward declaration

class DenseMatrix;

//

class ConjugateGradient : public LinearSolver {
public:
  ConjugateGradient() = default;
  explicit ConjugateGradient(usize number_of_cells);

  virtual ColumnVector solve(usize max_iterations,
                             real convergence_threshold) const final override;
};

} // namespace cfd
