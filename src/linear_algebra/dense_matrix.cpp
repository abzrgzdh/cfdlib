#include <cassert>
#include <vector>

#include "core/types.hpp"
#include "linear_algebra/dense_matrix.hpp"
#include "linear_algebra/vector.hpp"

namespace cfd {

DenseMatrix::DenseMatrix(usize m, usize n, real initial_value)
    : rows_{m}, cols_{n}, data_(m * n, initial_value) {}

usize DenseMatrix::rows() const noexcept { return rows_; }
usize DenseMatrix::cols() const noexcept { return cols_; }
usize DenseMatrix::size() const noexcept { return data_.size(); }
bool DenseMatrix::empty() const noexcept { return data_.empty(); }

real &DenseMatrix::operator[](usize row, usize col) {
  assert(row < rows_ && col < cols_);
  return data_[row * cols_ + col];
}

real DenseMatrix::operator[](usize row, usize col) const {
  assert(row < rows_ && col < cols_);
  return data_[row * cols_ + col];
}

DenseMatrix &DenseMatrix::operator+=(const DenseMatrix &dense_matrix) {
  assert(rows_ == dense_matrix.rows_ && cols_ == dense_matrix.cols_);
  for (usize i{}; i < data_.size(); ++i) {
    data_[i] += dense_matrix.data_[i];
  }
  return *this;
}

DenseMatrix &DenseMatrix::operator-=(const DenseMatrix &dense_matrix) {
  assert(rows_ == dense_matrix.rows_ && cols_ == dense_matrix.cols_);
  for (usize i{}; i < data_.size(); ++i) {
    data_[i] -= dense_matrix.data_[i];
  }
  return *this;
}

DenseMatrix operator+(const DenseMatrix &A, const DenseMatrix &B) {
  assert(A.rows() == B.rows() && A.cols() == B.cols());

  DenseMatrix result(A.rows(), A.cols());

  for (usize i{}; i < A.rows(); ++i) {
    for (usize j{}; j < A.cols(); ++j) {
      result[i, j] = A[i, j] + B[i, j];
    }
  }

  return result;
}

DenseMatrix operator-(const DenseMatrix &A, const DenseMatrix &B) {
  assert(A.rows() == B.rows() && A.cols() == B.cols());

  DenseMatrix C(A.rows(), A.cols());

  for (usize i{}; i < A.rows(); ++i) {
    for (usize j{}; j < A.cols(); ++j) {
      C[i, j] = A[i, j] - B[i, j];
    }
  }

  return C;
}

DenseMatrix operator*(const DenseMatrix &A, const DenseMatrix &B) {
  assert(A.cols() == B.rows());

  DenseMatrix result(A.rows(), B.cols());

  for (usize i{}; i < A.rows(); ++i) {
    for (usize k{}; k < A.cols(); ++k) {
      for (usize j{}; j < B.cols(); ++j) {
        result[i, j] += A[i, k] * B[k, j];
      }
    }
  }

  return result;
}

ColumnVector operator*(const DenseMatrix &dense_matrix,
                       const ColumnVector &vector) {
  assert(dense_matrix.cols() == vector.size());

  ColumnVector result(dense_matrix.rows());

  for (usize i{}; i < dense_matrix.rows(); ++i) {
    for (usize j{}; j < dense_matrix.cols(); ++j) {
      result[i] += dense_matrix[i, j] * vector[j];
    }
  }

  return result;
}

RowVector operator*(const RowVector &vector, const DenseMatrix &dense_matrix) {
  assert(vector.size() == dense_matrix.rows());

  RowVector result(dense_matrix.cols());

  for (usize i{}; i < dense_matrix.rows(); ++i) {
    for (usize j{}; j < dense_matrix.cols(); ++j) {
      result[j] += vector[i] * dense_matrix[i, j];
    }
  }

  return result;
}

DenseMatrix operator*(real scalar, const DenseMatrix &dense_matrix) {
  DenseMatrix scaled(dense_matrix.rows(), dense_matrix.cols());

  for (usize i{}; i < dense_matrix.rows(); ++i) {
    for (usize j{}; j < dense_matrix.cols(); ++j) {
      scaled[i, j] = scalar * dense_matrix[i, j];
    }
  }

  return scaled;
}

DenseMatrix operator*(const DenseMatrix &dense_matrix, real scalar) {
  return scalar * dense_matrix;
}

} // namespace cfd
