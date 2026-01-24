#include "gamma.hpp"
#include <cmath>

namespace special_functions {

template <typename T>
T gamma(T x)
{
    static constexpr T g = 7;
    static constexpr T coeffs[] = {
        T(0.99999999999980993),
        T(676.5203681218851),
        T(-1259.1392167224028),
        T(771.32342877765313),
        T(-176.61502916214059),
        T(12.507343278686905),
        T(-0.13857109526572012),
        T(9.9843695780195716e-6),
        T(1.5056327351493116e-7)
    };

    if (x < T(0.5))
        return M_PI / (std::sin(M_PI * x) * gamma(T(1) - x));

    x -= T(1);
    T a = coeffs[0];

    for (std::size_t i = 1; i < std::size(coeffs); ++i)
        a += coeffs[i] / (x + T(i));

    T t = x + g + T(0.5);
    return std::sqrt(T(2) * M_PI) * std::pow(t, x + T(0.5)) * std::exp(-t) * a;
}

template double gamma<double>(double);
template float gamma<float>(float);

}
