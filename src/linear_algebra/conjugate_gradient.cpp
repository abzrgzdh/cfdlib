#include "core/types.hpp"
#include "linear_algebra/conjugate_gradient.hpp"
#include "linear_algebra/dense_matrix.hpp"
#include "linear_algebra/linear_solver.hpp"
#include "linear_algebra/vector.hpp"

namespace cfd {

ConjugateGradient::ConjugateGradient(usize number_of_cells)
    : LinearSolver(number_of_cells) {}

ColumnVector ConjugateGradient::solve(usize max_iterations,
                                      real convergence_threshold) const {
  auto &A = coefficient_matrix_;
  auto &b = right_hand_side_;

  usize sz = b.size();
  ColumnVector r0(sz);
  ColumnVector r1(sz);
  ColumnVector p0(sz);
  ColumnVector p1(sz);
  ColumnVector x(sz);

  real alpha{};
  real beta{};

  usize iteration{};

  p1 = b - A * x;
  r1 = p0 - A * x;

  do {
    r0 = r1;
    p0 = p1;

    alpha = (r0.transpose() * r0) / (p0.transpose() * (A * p0));
    x = x + alpha * p0;
    r1 = r0 - alpha * A * p0;
    beta = (r1.transpose() * r1) / (r0.transpose() * r0);
    p1 = r1 + beta * p0;

    ++iteration;
  } while (iteration < max_iterations && r1.l2_norm() > convergence_threshold);

  return x;
}

} // namespace cfd
