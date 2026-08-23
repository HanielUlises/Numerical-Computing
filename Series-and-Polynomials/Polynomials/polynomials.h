#include <vector>
#include <ranges>
#include <cassert>
#include <concepts>
#include <iostream>
#include <cmath>

// Horner's Method
template <std::floating_point T, std::ranges::range Range>
T horner(const Range& coefficients, T x) {
    assert(!std::ranges::empty(coefficients));
    T result = *std::ranges::begin(coefficients);
    for (const auto& coeff : coefficients | std::views::drop(1)) {
        result = result * x + coeff;
    }
    return result;
}

// Naive Polynomial Evaluation
template <std::floating_point T, std::ranges::range Range>
T naive(const Range& coefficients, T x) {
    assert(!std::ranges::empty(coefficients));
    T result = 0.0;
    size_t degree = std::ranges::size(coefficients) - 1;
    for (size_t i = 0; i < coefficients.size(); ++i) {
        result += coefficients[i] * std::pow(x, static_cast<T>(degree - i));
    }
    return result;
}

// Estrin's Scheme 
template <std::floating_point T, std::ranges::range Range>
T estrin(const Range& coefficients, T x) {
    assert(!std::ranges::empty(coefficients));
    std::vector<T> temp(coefficients.begin(), coefficients.end());
    T x2 = x * x; 
    
    for (size_t step = 1; step < temp.size(); step *= 2) {
        for (size_t i = 0; i + step < temp.size(); i += 2 * step) {
            temp[i] = temp[i] * x2 + temp[i + step];
        }
    }
    
    T result = temp[0];
    for (size_t i = 2; i < temp.size(); i += 2) {
        result = result * x2 + (i < temp.size() ? temp[i] : 0);
    }
    
    return result;
}