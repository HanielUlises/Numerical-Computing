#pragma once
#include <array>
#include <functional>
#include <iostream>
#include <cassert>
#include <cmath>

constexpr std::size_t factorial(std::size_t n) {
    return (n <= 1) ? 1 : (n * factorial(n - 1));
}

// Type-safe enum
enum class Scheme { Forward, Backward, Centered };

// Finite difference coefficients for Taylor series expansion
// For simplicity, we hardcode some common stencils
template<Scheme scheme, std::size_t DerivOrder, std::size_t Accuracy>
struct FDStencil;

template<std::size_t DerivOrder, std::size_t Accuracy>
struct FDStencil<Scheme::Forward, DerivOrder, Accuracy> {
    static constexpr std::array<double, Accuracy + 1> coefficients = [] {
        std::array<double, Accuracy + 1> coeffs{};
        // Computing finite difference coefficients using forward difference table
        // For first derivative, accuracy 1: [-1, 1]/h
        // See: Fornberg algorithm for general case
        if constexpr (DerivOrder == 1 && Accuracy == 1) {
            coeffs[0] = -1.0;
            coeffs[1] = 1.0;
        } else if constexpr (DerivOrder == 1 && Accuracy == 2) {
            coeffs[0] = -3.0 / 2;
            coeffs[1] = 2.0;
            coeffs[2] = -1.0 / 2;
        }
        return coeffs;
    }();
};

template<std::size_t DerivOrder, std::size_t Accuracy>
struct FDStencil<Scheme::Backward, DerivOrder, Accuracy> {
    static constexpr std::array<double, Accuracy + 1> coefficients = [] {
        std::array<double, Accuracy + 1> coeffs{};
        if constexpr (DerivOrder == 1 && Accuracy == 1) {
            coeffs[0] = 1.0;
            coeffs[1] = -1.0;
        } else if constexpr (DerivOrder == 1 && Accuracy == 2) {
            coeffs[0] = 3.0 / 2;
            coeffs[1] = -2.0;
            coeffs[2] = 0.5;
        }
        return coeffs;
    }();
};

template<std::size_t DerivOrder, std::size_t Accuracy>
struct FDStencil<Scheme::Centered, DerivOrder, Accuracy> {
    static constexpr std::array<double, Accuracy * 2 + 1> coefficients = [] {
        std::array<double, Accuracy * 2 + 1> coeffs{};
        if constexpr (DerivOrder == 1 && Accuracy == 1) {
            coeffs[0] = -0.5;
            coeffs[2] = 0.5;
        } else if constexpr (DerivOrder == 2 && Accuracy == 1) {
            coeffs[0] = 1.0;
            coeffs[1] = -2.0;
            coeffs[2] = 1.0;
        }
        return coeffs;
    }();
};

// Core differentiation class
template<
    Scheme scheme,
    std::size_t DerivOrder,
    std::size_t Accuracy,
    typename T = double
>
class FiniteDifference {
public:
    static constexpr std::size_t stencil_size = 
        scheme == Scheme::Centered ? (2 * Accuracy + 1) : (Accuracy + 1);

    template<typename Func>
    static T differentiate(Func f, T x, T h) {
        static_assert(std::is_invocable_r_v<T, Func, T>, "Function must be callable with T -> T");
        const auto& coeffs = FDStencil<scheme, DerivOrder, Accuracy>::coefficients;
        T result = 0;
        for (std::size_t i = 0; i < stencil_size; ++i) {
            T xi = x + offset(i, h);
            result += coeffs[i] * f(xi);
        }
        return result / std::pow(h, DerivOrder);
    }

private:
    static constexpr T offset(std::size_t i, T h) {
        if constexpr (scheme == Scheme::Forward) {
            return i * h;
        } else if constexpr (scheme == Scheme::Backward) {
            return -static_cast<T>(i) * h;
        } else if constexpr (scheme == Scheme::Centered) {
            return (static_cast<T>(i) - static_cast<T>(Accuracy)) * h;
        }
        return 0;
    }
};

