#pragma once

#include <ostream>
#include <vector>

#include "core/types.hpp"

namespace cfd {

class DenseMatrix;

//
//

enum class VectorOrientation { Row, Column };

//
//

// Explicit instantiation is used in the .cpp file.
template <VectorOrientation Orientation> class Vector {
public:
  using TransposedVector =
      Vector<(Orientation == VectorOrientation::Row) ? VectorOrientation::Column
                                                     : VectorOrientation::Row>;
  //

public:
  Vector() = default;
  explicit Vector(usize sz, real initial_value = {});
  Vector(const std::vector<real> &vector_data);

  //

  usize size() const noexcept;
  bool empty() const noexcept;

  // NOTE: In-place transpose is neither possible in this template class
  // design, nor really necessary in computations.
  TransposedVector transpose() const noexcept;

  real l1_norm() const noexcept;
  real l2_norm() const noexcept;
  real linf_norm() const noexcept;
  real p_norm(real p) const noexcept;

  //

  real &operator[](usize index);
  const real &operator[](usize index) const;

  Vector operator+(const Vector &other) const noexcept;
  Vector &operator+=(const Vector &other) noexcept;

  Vector operator-(const Vector &other) const noexcept;
  Vector &operator-=(const Vector &other) noexcept;

  Vector operator*(real scalar_factor) const noexcept;
  Vector &operator*=(real scalar) noexcept;

  //

private:
  std::vector<real> data_{};
};

//
//

using ColumnVector = Vector<VectorOrientation::Column>;
using RowVector = Vector<VectorOrientation::Row>;

//
//

template <VectorOrientation Orientation = VectorOrientation::Column>
Vector<Orientation> operator*(real scalar,
                              const Vector<Orientation> &vector) noexcept;

real operator*(const RowVector &row_vector,
               const ColumnVector &column_vector) noexcept;

DenseMatrix operator*(const ColumnVector &column_vector,
                      const RowVector &row_vector) noexcept;

template <VectorOrientation Orientation = VectorOrientation::Column>
std::ostream &operator<<(std::ostream &out, const Vector<Orientation> &vector);

//
// Explicit class instantiations (declaration)

extern template class Vector<VectorOrientation::Row>;
extern template class Vector<VectorOrientation::Column>;

//
// Explicit free-function instantiations (declaration)

extern template RowVector operator*
    <VectorOrientation::Row>(real, const RowVector &) noexcept;

extern template ColumnVector operator*
    <VectorOrientation::Column>(real, const ColumnVector &) noexcept;

extern template std::ostream &
operator<< <VectorOrientation::Row>(std::ostream &, const RowVector &);

extern template std::ostream &
operator<< <VectorOrientation::Column>(std::ostream &, const ColumnVector &);

} // namespace cfd
