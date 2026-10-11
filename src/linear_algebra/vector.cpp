#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

#include "core/types.hpp"
#include "linear_algebra/vector.hpp"
#include "linear_algebra/dense_matrix.hpp"

namespace cfd {

template <VectorOrientation Orientation>
Vector<Orientation>::Vector(usize sz, real initial_value)
    : data_(sz, initial_value) {}

template <VectorOrientation Orientation>
Vector<Orientation>::Vector(const std::vector<real> &vector_data)
    : data_(vector_data) {}

//

template <VectorOrientation Orientation>
usize Vector<Orientation>::size() const noexcept {
  return data_.size();
}

template <VectorOrientation Orientation>
bool Vector<Orientation>::empty() const noexcept {
  return data_.empty();
}


template <VectorOrientation Orientation>
real Vector<Orientation>::l1_norm() const noexcept {
  real abs_norm{};

  for (auto element : data_) {
    abs_norm += std::abs(element);
  }

  return abs_norm;
}

template <VectorOrientation Orientation>
real Vector<Orientation>::l2_norm() const noexcept {
  real norm{};

  for (auto element : data_) {
    norm += element * element;
  }

  std::cerr << std::sqrt(norm) << '\n';

  return std::sqrt(norm);
}

template <VectorOrientation Orientation>
real Vector<Orientation>::linf_norm() const noexcept {
  real max_norm{};

  for (auto element : data_) {
    max_norm = std::max(max_norm, std::abs(element));
  }

  return max_norm;
}

template <VectorOrientation Orientation>
real Vector<Orientation>::p_norm(real p) const noexcept {
  assert(p >= real{1} && std::isfinite(p) && "p must be finite and >= 1.");

  const real max{linf_norm()};

  if (max == real{}) {
    return {};
  }

  real sum{};

  for (auto element : data_) {
    const real normalized_element{element / max};
    sum += std::pow(std::abs(normalized_element), p);
  }

  return max * std::pow(sum, real{1} / p);
}

template <VectorOrientation Orientation>
typename Vector<Orientation>::TransposedVector
Vector<Orientation>::transpose() const noexcept {
  return TransposedVector{data_};
}

//

template <VectorOrientation Orientation>
real& Vector<Orientation>::operator[](usize index) {
    assert(index < data_.size());
    return data_[index];
}

template <VectorOrientation Orientation>
const real& Vector<Orientation>::operator[](usize index) const {
    assert(index < data_.size());
    return data_[index];
}

template <VectorOrientation Orientation>
Vector<Orientation>
Vector<Orientation>::operator+(const Vector &other) const noexcept {
  assert(size() == other.size() &&
         "Inconsistent vector sizes in addition operation.");

  Vector sum(*this);

  for (usize i{}; i < size(); ++i) {
    sum[i] += other[i];
  }

  return sum;
}

template <VectorOrientation Orientation>
Vector<Orientation> &
Vector<Orientation>::operator+=(const Vector &other) noexcept {
  assert(size() == other.size() &&
         "Inconsistent vector sizes in addition operation.");

  for (usize i{}; i < size(); ++i) {
    data_[i] += other[i];
  }

  return *this;
}

template <VectorOrientation Orientation>
Vector<Orientation>
Vector<Orientation>::operator-(const Vector &other) const noexcept {
  assert(size() == other.size() &&
         "Inconsistent vector sizes in subtraction operation.");

  Vector difference(*this);

  for (usize i{}; i < size(); ++i) {
    difference[i] -= other[i];
  }

  return difference;
}

template <VectorOrientation Orientation>
Vector<Orientation> &
Vector<Orientation>::operator-=(const Vector &other) noexcept {
  assert(size() == other.size() &&
         "Inconsistent vector sizes in subtraction operation.");

  for (usize i{}; i < size(); ++i) {
    data_[i] -= other[i];
  }

  return *this;
}

template <VectorOrientation Orientation>
Vector<Orientation> Vector<Orientation>::operator*(real scalar) const noexcept {
  Vector scaled(*this);

  for (auto &value : scaled.data_) {
    value *= scalar;
  }

  return scaled;
}

template <VectorOrientation Orientation>
Vector<Orientation> &Vector<Orientation>::operator*=(real scalar) noexcept {
  for (auto &value : data_) {
    value *= scalar;
  }

  return *this;
}

//

template <VectorOrientation Orientation>
Vector<Orientation> operator*(real scalar,
                              const Vector<Orientation> &vector) noexcept {
  return vector * scalar;
}

// Row vector * column vector = scalar (dot product).
real operator*(const RowVector &row_vector,
               const ColumnVector &column_vector) noexcept {
  assert(row_vector.size() == column_vector.size() &&
         "Inconsistent vector sizes in dot product.");

  real result{};

  for (usize i{}; i < row_vector.size(); ++i) {
    result += row_vector[i] * column_vector[i];
  }

  return result;
}

// Column vector * row vector = matrix (outer product).
DenseMatrix operator*(const ColumnVector &column_vector,
                      const RowVector &row_vector) noexcept {
  DenseMatrix result{column_vector.size(), row_vector.size()};

  for (usize i{}; i < column_vector.size(); ++i) {
    for (usize j{}; j < row_vector.size(); ++j) {
      result[i, j] = column_vector[i] * row_vector[j];
    }
  }

  return result;
}

template <VectorOrientation Orientation>
std::ostream &operator<<(std::ostream &out, const Vector<Orientation> &vector) {
  out << "( ";

  for (usize index{}; index < vector.size(); ++index) {
    out << vector[index] << ' ';
  }

  return out << ')';
}

//
// Explicit class instantiations.

template class Vector<VectorOrientation::Row>;
template class Vector<VectorOrientation::Column>;

//
// Explicit free-function instantiations.

template RowVector operator*
    <VectorOrientation::Row>(real, const RowVector &) noexcept;

template ColumnVector operator*
    <VectorOrientation::Column>(real, const ColumnVector &) noexcept;

template std::ostream &operator<< <VectorOrientation::Row>(std::ostream &,
                                                           const RowVector &);

template std::ostream &
operator<< <VectorOrientation::Column>(std::ostream &, const ColumnVector &);

} // namespace cfd
