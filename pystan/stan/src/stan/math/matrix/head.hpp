#ifndef __STAN__MATH__MATRIX__HEAD_HPP__
#define __STAN__MATH__MATRIX__HEAD_HPP__

#include <stan/math/matrix/Eigen.hpp>
#include <vector>
#include <stan/math/error_handling/matrix/check_column_index.hpp>
#include <stan/math/error_handling/matrix/check_row_index.hpp>
#include <stan/math/error_handling/matrix/check_std_vector_index.hpp>

namespace stan {
  namespace math {

    /**
     * Return the specified number of elements as a vector
     * from the front of the specified vector.
     * @tparam T Type of value in vector
     * @param v Vector input
     * @param n Size of return 
     * @return The first n elements of v
     */
    template <typename T>
    inline
    Eigen::Matrix<T,Eigen::Dynamic,1>
    head(const Eigen::Matrix<T,Eigen::Dynamic,1>& v,
         size_t n) {
      if (n != 0)
        stan::math::check_row_index("head(%1%)",n,v,"n",(double*)0);
      return v.head(n);
    }

    /**
     * Return the specified number of elements as a row vector
     * from the front of the specified row vector.
     * @tparam T Type of value in vector
     * @param rv Row vector
     * @param n Size of return row vector
     * @return The first n elements of rv
     */
    template <typename T>
    inline
    Eigen::Matrix<T,1,Eigen::Dynamic>
    head(const Eigen::Matrix<T,1,Eigen::Dynamic>& rv,
         size_t n) {
      if (n != 0)
        stan::math::check_column_index("head(%1%)",n,rv,"n",(double*)0);
      return rv.head(n);
    }

    /**
     * Return the specified number of elements as a standard vector
     * from the front of the specified standard vector.
     * @tparam T Type of value in vector
     * @param sv Standard vector
     * @param n Size of return 
     * @return The first n elements of sv
     */
    template <typename T>
    std::vector<T> head(const std::vector<T>& sv,
                        size_t n) {
      if (n != 0)
        stan::math::check_std_vector_index("head(%1%)",n,sv,"n",(double*)0);

      std::vector<T> s;
      for (size_t i = 0; i < n; ++i)
        s.push_back(sv[i]);
      return s;
    }


  }
}

#endif
