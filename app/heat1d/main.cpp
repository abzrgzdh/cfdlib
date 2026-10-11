#include <cassert>
#include <print>

#include "cfd.hpp"

using namespace cfd;

// solve the heat equation implicitly of the form dT/dt = gamma * d^2 T/ dx^2
// over a domain L using the conjugate gradient methdod
// initial condition: 0 everywhere
// boundary condition: T(0) = 0, T(L) = 1
int main() {
  // input variables
  constexpr real gamma{1.0};
  constexpr usize number_of_cells{100};
  constexpr real domain_length{1.0};
  constexpr real boundary_value_left{0.0};
  constexpr real boundary_value_right{1.0};
  constexpr real dx{domain_length / number_of_cells};

  // vectors and matrices
  ColumnVector coordinate_x(number_of_cells);
  ColumnVector temperature(number_of_cells);
  ColumnVector boundary_conditions(number_of_cells);

  DenseMatrix coefficient_matrix(number_of_cells, number_of_cells);

  // Initialize arrays and set-up 1-D mesh
  for (usize i{0}; i < number_of_cells; ++i) {
    coordinate_x[i] = static_cast<real>(i) * dx + dx / 2.0;
    temperature[i] = real{};
    boundary_conditions[i] = real{};
  }

  // Calculate individual matrix coefficients
  constexpr real a_E{gamma / dx};
  constexpr real a_W{gamma / dx};
  constexpr real a_P{-1.0 * (a_E + a_W)};

  // Set individual matrix coefficients
  for (usize i{1}; i < number_of_cells - 1; ++i) {
    coefficient_matrix[i, i] = a_P;
    coefficient_matrix[i, i + 1] = a_E;
    coefficient_matrix[i, i - 1] = a_W;
  }

  coefficient_matrix[0, 0] = -1.0 * (a_E + 2 * a_W);
  coefficient_matrix[0, 1] = a_E;
  coefficient_matrix[number_of_cells - 1, number_of_cells - 2] = a_W;
  coefficient_matrix[number_of_cells - 1, number_of_cells - 1] =
      -1.0 * (a_E + 2 * a_W);

  // Set boundary conditions
  boundary_conditions[0] = -2.0 * a_W * boundary_value_left;
  boundary_conditions[number_of_cells - 1] = -2.0 * a_E * boundary_value_right;

  // Solve the linear system using the conjugate gradient method
  ConjugateGradient cg_solver{number_of_cells};
  cg_solver.set_coefficient_matrix(coefficient_matrix);
  cg_solver.set_right_hand_side(boundary_conditions);
  temperature = cg_solver.solve(100, 1e-10);

  // The obtained temperature profile a linear one of the form T(x) = x. Thus,
  // we can compare it directly against the coordinate vector (which in this
  // case acts as an analytic solution)
  ColumnVector difference(number_of_cells);
  for (usize i{0}; i < number_of_cells; ++i) {
    difference[i] += std::fabs(temperature[i] - coordinate_x[i]);
  }

  // Ensure that temperature has converged to at least single precision
  assert(difference.l2_norm() < 1e-8);

  std::print("Simulation successful, final residual: {}", difference.l2_norm());

  return 0;
}
