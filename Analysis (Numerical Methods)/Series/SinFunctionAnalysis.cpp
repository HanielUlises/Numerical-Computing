#include <iostream>
#include <cmath>

// Compile-time factorial
template<int N>
struct Factorial {
    static constexpr unsigned long long value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0> {
    static constexpr unsigned long long value = 1;
};

// Compile-time Taylor Series term for sine: (-1)^k * x^(2k+1) / (2k+1)!
template<int K, typename T>
struct SineTerm {
    static constexpr T value(T x) {
        T term = (K % 2 == 0 ? 1 : -1) * std::pow(x, 2 * K + 1) / Factorial<2 * K + 1>::value;
        return term + SineTerm<K - 1, T>::value(x);
    }
};

// Base case: stop at K = 0 (first term: x)
template<typename T>
struct SineTerm<0, T> {
    static constexpr T value(T x) { return x; }
};

// Wrapper to compute sine with N terms (0-based index, so N=4 means 5 terms)
template<int N, typename T>
struct TaylorSine {
    static constexpr T compute(T x) {
        return SineTerm<N, T>::value(x);
    }
};

template<int N, typename T>
void test_sine(T x) {
    T taylorSine = TaylorSine<N, T>::compute(x);
    T librarySine = std::sin(x);
    T error = std::fabs(taylorSine - librarySine);
    std::cout << "\nAt x = " << x << ":\tTaylor Series Sine = " << taylorSine
              << ",\tLibrary Sine = " << librarySine 
              << ",\tError = " << error;
}

int main() {
    // 4 terms (x - x³/3! + x⁵/5! - x⁷/7!)
    for (float x = 0; x <= 6.5; x += 0.25) {
        test_sine<3, float>(x);
    }
    return 0;
}