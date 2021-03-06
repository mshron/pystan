#ifndef __STAN__AGRAD__REV__MATRIX__DOT_SELF_HPP__
#define __STAN__AGRAD__REV__MATRIX__DOT_SELF_HPP__

#include <vector>
#include <stan/math/matrix/Eigen.hpp>
#include <stan/math/matrix/typedefs.hpp>
#include <stan/math/error_handling/matrix/check_vector.hpp>
#include <stan/agrad/fwd/fvar.hpp>
#include <stan/agrad/fwd/matrix/dot_product.hpp>

namespace stan {
  namespace agrad {

    template<typename T, int R, int C>
    inline fvar<T>
    dot_self(const Eigen::Matrix<fvar<T>, R, C>& v) {
      stan::math::check_vector("dot_self(%1%)",v,"v",(double*)0);
      return dot_product(v, v);
    }
  }
}
#endif
