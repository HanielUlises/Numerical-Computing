#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

template <typename T>
concept EqualityComparable = std::equality_comparable<T>;

template <typename F>
concept DistanceTransformation =
    Transformation<F> &&
    EqualityComparable<Domain_t<F>>;

/**
 * @brief Provides the domain type associated with an operation.
 *
 * @tparam T Operation type.
 */
template <typename T>
struct Domain;

/**
 * @brief Defines the domain of a binary operation as the common type
 *        of its two argument types.
 *
 * @tparam R Return type.
 * @tparam A First argument type.
 * @tparam B Second argument type.
 */
template <typename R, typename A, typename B>
struct Domain<R (*)(A, B)> {
    using type = std::common_type_t<A, B>;
};

/**
 * @brief Defines the domain of a unary transformation as its argument type.
 *
 * @tparam R Return type.
 * @tparam A Argument type.
 */
template <typename R, typename A>
struct Domain<R (*)(A)> {
    using type = A;
};

/**
 * @brief Convenience alias for the domain type of an operation.
 *
 * @tparam T Operation type.
 */
template <typename T>
using Domain_t = typename Domain<T>::type;

/**
 * @brief Concept defining a binary operation whose result is convertible
 *        to its domain type.
 *
 * @tparam Op Binary operation type.
 */
template <typename Op>
concept BinaryOperation = requires(Op op, Domain_t<Op> a, Domain_t<Op> b) {
    { op(a, b) } -> std::convertible_to<Domain_t<Op>>;
};

/**
 * @brief Concept defining a unary transformation whose result is convertible
 *        to its domain type.
 *
 * @tparam F Transformation type.
 */
template <typename F>
concept Transformation = requires(F f, Domain_t<F> x) {
    { f(x) } -> std::convertible_to<Domain_t<F>>;
};

/**
 * @brief Concept defining an integral type.
 *
 * @tparam N Type to be constrained.
 */
template <typename N>
concept Integer = std::integral<N>;

/**
 * @brief Provides the distance type associated with a transformation.
 *
 * @tparam T Transformation type.
 */
template <typename T>
struct DistanceType;

/**
 * @brief Defines the distance type of a unary transformation as the
 *        unsigned version of its domain type.
 *
 * @tparam R Return type.
 * @tparam A Argument type.
 */
template <typename R, typename A>
struct DistanceType<R (*)(A)> {
    using type = std::make_unsigned_t<A>;
};

/**
 * @brief Convenience alias for the distance type of a transformation.
 *
 * @tparam T Transformation type.
 */
template <typename T>
using DistanceType_t = typename DistanceType<T>::type;

/**
 * @brief Computes the result of applying a unary transformation a specified
 *        number of times.
 *
 * @tparam F Transformation type.
 * @tparam N Integral iteration count type.
 *
 * @param x Initial value.
 * @param n Number of applications of the transformation.
 * @param f Unary transformation.
 *
 * @return The value obtained after applying @p f exactly @p n times.
 *
 * @pre n >= 0.
 */
template <typename F, typename N>
requires Transformation<F> && Integer<N>
Domain_t<F> power_unary(Domain_t<F> x, N n, F f)
{
    while (n != N(0)) {
        n = n - N(1);
        x = f(x);
    }

    return x;
}

/**
 * @brief Computes the number of applications of a unary transformation
 *        required to transform one value into another.
 *
 * @tparam F Transformation type.
 *
 * @param x Initial value.
 * @param y Target value.
 * @param f Unary transformation.
 *
 * @return The number of applications of @p f required to transform @p x
 *         into @p y.
 *
 * @pre y is reachable from x under repeated application of f.
 */
template <typename F>
requires Transformation<F>
DistanceType_t<F> distance(Domain_t<F> x, Domain_t<F> y, F f)
{
    using N = DistanceType_t<F>;

    N n(0);

    while (x != y) {
        x = f(x);
        n = n + N(1);
    }

    return n;
}
