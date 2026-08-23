#include "elliptic.hpp"
#include <cmath>
#include <limits>

namespace special_functions {

template <typename T>
T elliptic_k(T k)
{
    if (k < T(0) || k >= T(1))
        return std::numeric_limits<T>::quiet_NaN();

    T a = T(1);
    T b = std::sqrt(T(1) - k * k);
    T c;
    T sum = T(0);
    T pow2 = T(1);

    for (int i = 0; i < 50; ++i) {
        c = (a - b) * T(0.5);
        sum += pow2 * c * c;
        T a_next = (a + b) * T(0.5);
        b = std::sqrt(a * b);
        a = a_next;
        pow2 *= T(2);

        if (c < std::numeric_limits<T>::epsilon())
            break;
    }

    return M_PI / (T(2) * a);
}

template double elliptic_k<double>(double);
template float elliptic_k<float>(float);

}
