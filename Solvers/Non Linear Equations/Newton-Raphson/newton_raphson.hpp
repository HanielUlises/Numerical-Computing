#pragma once

#include <vector>
#include <functional>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <concepts>

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<typename Mat>
concept MatrixLike = requires(Mat m, int i, int j, typename Mat::value_type val)
{
    { m.rows() } -> std::convertible_to<int>;
    { m.cols() } -> std::convertible_to<int>;
    { m(i,j) } -> std::convertible_to<typename Mat::value_type&>;
    { m(i,j) = val };
};

template<typename Vec, MatrixLike Mat>
struct NewtonResult
{
    Vec solution;
    int iterations;
    bool converged;
    double residual;
};

template<typename Vec, typename Func, typename JacFunc, typename Mat>
requires MatrixLike<Mat>
NewtonResult<Vec, Mat> newton_raphson(
    Func&& system,                                     // (x) → F(x), returns vector or Matrix column
    const Vec& x0,
    double tol = 1e-12,
    int max_iter = 50,
    bool verbose = true)
{
    using Scalar = typename Vec::value_type;
    Vec x = x0;
    int n = x.size();
    int iter = 0;

    if (verbose) {
        std::cout << std::fixed << std::setprecision(12);
        std::cout << "Iter |                 x                 ||F||           ||dx||\n";
        std::cout << "---------------------------------------------------------------\n";
    }

    for (iter = 1; iter <= max_iter; ++iter)
    {
        // Residual F(x) 
        auto Fx = system(x);                           // Could be std::vector or Matrix column
        Vec F(n);
        for (int i = 0; i < n; ++i)
            F[i] = (Fx.size() ? Fx[i] : Fx(i,0));      // unified access

        double residual = 0.0;
        for (auto v : F) residual += v*v;
        residual = std::sqrt(residual);

        if (verbose) {
            std::cout << std::setw(4) << iter << " | ";
            for (int i = 0; i < std::min(n,4); ++i) std::cout << std::setw(14) << x[i] << " ";
            if (n > 4) std::cout << "...";
            std::cout << "  " << std::scientific << residual;
        }

        if (residual < tol) {
            if (verbose) std::cout << "  ← CONVERGED\n";
            return {x, iter, true, residual};
        }

        // Compute Jacobian (finite differences if not provided)
        Mat J(n, n);
        Scalar h = 1e-8;
        for (int j = 0; j < n; ++j) {
            Vec xph = x, xmh = x;
            xph[j] += h; xmh[j] -= h;

            auto Fph = system(xph);
            auto Fmh = system(xmh);

            for (int i = 0; i < n; ++i) {
                Scalar fph = (Fph.size() ? Fph[i] : Fph(i,0));
                Scalar fmh = (Fmh.size() ? Fmh[i] : Fmh(i,0));
                J(i,j) = (fph - fmh) / (2*h);
            }
        }

        // Solve J Δx = -F 
        Vec delta(n);
        try {
            auto delta_mat = J.inverse() * (-Mat(F));  
            for (int i = 0; i < n; ++i)
                delta[i] = delta_mat(i,0);
        } catch (...) {
            if (verbose) std::cout << "  ← SINGULAR JACOBIAN\n";
            return {x, iter, false, residual};
        }

        double dx_norm = 0.0;
        for (auto d : delta) dx_norm += d*d;
        dx_norm = std::sqrt(dx_norm);

        if (verbose) std::cout << "  " << dx_norm << "\n";

        // Update
        for (int i = 0; i < n; ++i) x[i] += delta[i];
    }

    if (verbose) std::cout << "  ← MAX ITERATIONS\n";
    return {x, iter-1, false, 0.0};
}

// Method with analytic Jacobian
template<typename Vec, typename Func, typename JacFunc>
auto newton_raphson(
    Func&& F,
    JacFunc&& J,
    const Vec& x0,
    double tol = 1e-12,
    int max_iter = 50,
    bool verbose = true)
{
    using Scalar = typename Vec::value_type;
    using Mat = decltype(J(x0));

    Vec x = x0;
    int n = x.size();

    if (verbose) {
        std::cout << std::fixed << std::setprecision(12);
        std::cout << "Iter |                 x                 ||F||           ||dx||\n";
        std::cout << "---------------------------------------------------------------\n";
    }

    for (int iter = 1; iter <= max_iter; ++iter)
    {
        auto Fx = F(x);
        Vec Fvec(n);
        for (int i = 0; i < n; ++i)
            Fvec[i] = Fx(i,0);

        double residual = 0.0;
        for (auto v : Fvec) residual += v*v;
        residual = std::sqrt(residual);

        if (verbose) {
            std::cout << std::setw(4) << iter << " | ";
            for (int i = 0; i < std::min(n,4); ++i)
                std::cout << std::setw(14) << x[i] << " ";
            std::cout << "  " << std::scientific << residual;
        }

        if (residual < tol) {
            if (verbose) std::cout << "  ← CONVERGED\n";
            return NewtonResult<Vec, Mat>{x, iter, true, residual};
        }

        Mat JF = J(x);
        Mat delta_mat = JF.inverse() * (-Mat(Fvec));

        Vec delta(n);
        for (int i = 0; i < n; ++i) delta[i] = delta_mat(i,0);

        double dx_norm = 0.0;
        for (auto d : delta) dx_norm += d*d;
        dx_norm = std::sqrt(dx_norm);

        if (verbose) std::cout << "  " << dx_norm << "\n";

        for (int i = 0; i < n; ++i) x[i] += delta[i];
    }

    return NewtonResult<Vec, Mat>{x, max_iter, false, 0.0};
}