#include "zeta.hpp"
#include <cmath>
#include <limits>
#include <array>

namespace special_functions {

namespace {

template <typename T>
constexpr std::array<T, 8> bernoulli_numbers()
{
    return {
        T( 1.0 / 6.0),
        T(-1.0 / 30.0),
        T( 1.0 / 42.0),
        T(-1.0 / 30.0),
        T( 5.0 / 66.0),
        T(-691.0 / 2730.0),
        T( 7.0 / 6.0),
        T(-3617.0 / 510.0)
    };
}

template <typename T>
T pochhammer(T x, int n)
{
    T result = T(1);
    for (int i = 0; i < n; ++i)
        result *= (x + T(i));
    return result;
}

}

template <typename T>
T riemann_zeta(T s)
{
    if (s <= T(1))
        return std::numeric_limits<T>::quiet_NaN();

    constexpr int n_terms = 20;
    constexpr int m_corr  = 8;

    T sum = T(0);
    for (int n = 1; n <= n_terms; ++n)
        sum += std::pow(T(n), -s);

    T n = T(n_terms);
    T tail = std::pow(n, T(1) - s) / (s - T(1)) + T(0.5) * std::pow(n, -s);

    T corr = T(0);
    auto B = bernoulli_numbers<T>();

    for (int k = 1; k <= m_corr; ++k) {
        T coef = B[k - 1] / std::tgamma(T(2 * k + 1));
        T term = coef * pochhammer(s, 2 * k - 1) * std::pow(n, -s - T(2 * k - 1));
        corr += term;
    }

    return sum + tail + corr;
}

template double riemann_zeta<double>(double);
template float riemann_zeta<float>(float);

}
