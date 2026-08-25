#include <concepts>
#include <type_traits>

// Domain of an operation
template <typename T>
struct Domain;

// Binary operation: Domain is the common type of its arguments
template <typename R, typename A, typename B>
struct Domain<R(*)(A, B)> {
    using type = std::common_type_t<A, B>;
};

// Unary transformation: Domain is its argument type
template <typename R, typename A>
struct Domain<R(*)(A)> {
    using type = A;
};

template <typename T>
using Domain_t = typename Domain<T>::type;


// Binary operation concept
template <typename Op>
concept BinaryOperation = requires(Op op, Domain_t<Op> a, Domain_t<Op> b) {
    { op(a, b) } -> std::convertible_to<Domain_t<Op>>;
};


// Unary transformation concept
template <typename F>
concept Transformation = requires(F f, Domain_t<F> x) {
    { f(x) } -> std::convertible_to<Domain_t<F>>;
};


// Integer concept
template <typename N>
concept Integer = std::integral<N>;


// Unary power
template <typename F, typename N>
    requires (Transformation<F> && Integer<N>)
Domain_t<F> power_unary(Domain_t<F> x, N n, F f)
{
    // Precondition: n > 0
    while (n != N(0)) {
        n = n - N(1);
        x = f(x);
    }

    return x;
}
