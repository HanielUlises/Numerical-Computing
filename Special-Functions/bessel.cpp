#include "bessel.hpp"
#include <cmath>

namespace special_functions {

template <typename T>
T bessel_j0(T x)
{
    constexpr int max_iter = 50;
    T term = T(1);
    T sum  = T(1);
    T x2   = (x * x) / T(4);

    for (int k = 1; k < max_iter; ++k) {
        term *= -x2 / (T(k) * T(k));
        sum  += term;
    }

    return sum;
}

template double bessel_j0<double>(double);
template float bessel_j0<float>(float);

}
