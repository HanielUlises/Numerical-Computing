#include <concepts>
#include <type_traits>

template <typename T>
struct Domain;

template <typename R, typename A, typename B>
struct Domain<R(*)(A, B)> {
    using type = std::common_type_t<A, B>;
};

template <typename T>
using Domain_t = typename Domain<T>::type;

template <typename Op>
concept BinaryOperation = requires(Op op, Domain<Op> a, Domain<Op> b) {
    { op(a, b) } -> std::convertible_to<Domain<Op>>;
};

template <typename Op>
    requires BinaryOperation<Op>
Domain<Op> square(const Domain<Op>& x, Op op) {
    return op(x, x);
}