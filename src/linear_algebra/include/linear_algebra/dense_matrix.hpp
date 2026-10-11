#pragma once

#include <vector>

#include "core/types.hpp"
#include "linear_algebra/vector.hpp"

namespace cfd {

class DenseMatrix {
public:
  DenseMatrix() = default;
  DenseMatrix(usize m, usize n, real initial_value = {});

  usize rows() const noexcept;
  usize cols() const noexcept;
  usize size() const noexcept;
  bool empty() const noexcept;

  real &operator[](usize row, usize col);
  real operator[](usize row, usize col) const;

  DenseMatrix &operator+=(const DenseMatrix &dense_matrix);
  DenseMatrix &operator-=(const DenseMatrix &dense_matrix);

private:
  usize rows_{};
  usize cols_{};
  std::vector<real> data_{};
};

DenseMatrix operator+(const DenseMatrix &A, const DenseMatrix &B);
DenseMatrix operator-(const DenseMatrix &A, const DenseMatrix &B);

// Matrix-Matrix multiply
DenseMatrix operator*(const DenseMatrix &A, const DenseMatrix &B);

// Matrix-Vector left-multiply
ColumnVector operator*(const DenseMatrix &dense_matrix,
                       const ColumnVector &vector);

// RowVector-Matrix right-multiply
RowVector operator*(const RowVector &vector, const DenseMatrix &dense_matrix);

// Multiplication by scalar from left and right
DenseMatrix operator*(real scalar, const DenseMatrix &dense_matrix);
DenseMatrix operator*(const DenseMatrix &dense_matrix, real scalar);

} // namespace cfd
