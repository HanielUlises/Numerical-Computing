#include "autodiff.h"

// ---------- variable implementation ----------

template <typename T>
variable<T>::variable(T value) : value(value) {}

template <typename T>
value_and_partial<T> variable<T>::evaluate_and_derive(variable<T>* var) {
    T partial = (this == var) ? static_cast<T>(1) : static_cast<T>(0);
    return { value, partial };
}

// ---------- plus implementation ----------

template <typename T, typename... Ops>
plus<T, Ops...>::plus(Ops... ops) : operands(ops...) {
    static_assert((std::is_same_v<Ops, expression<T>*> && ...),
                  "All operands must be expression<T>*");
}

template <typename T, typename... Ops>
value_and_partial<T> plus<T, Ops...>::evaluate_and_derive(variable<T>* var) {
    value_and_partial<T> result{ static_cast<T>(0), static_cast<T>(0) };
    std::apply([&](auto... ops) {
        (([&] {
            auto temp = ops->evaluate_and_derive(var);
            result.value += temp.value;
            result.partial += temp.partial;
        }()), ...);
    }, operands);
    return result;
}

// ---------- multiply implementation ----------

template <typename T, typename... Ops>
multiply<T, Ops...>::multiply(Ops... ops) : operands(ops...) {
    static_assert((std::is_same_v<Ops, expression<T>*> && ...),
                  "All operands must be expression<T>*");
}

template <typename T, typename... Ops>
value_and_partial<T> multiply<T, Ops...>::evaluate_and_derive(variable<T>* var) {
    constexpr std::size_t n = sizeof...(Ops);

    // Evaluate every operand exactly once; store in an array.
    auto evals = std::apply([&](auto*... ops) -> std::array<value_and_partial<T>, n> {
        return { ops->evaluate_and_derive(var)... };
    }, operands);

    // Product of all operand values.
    T prod = static_cast<T>(1);
    for (const auto& ev : evals)
        prod *= ev.value;

    // Derivative using the product rule:
    // ∂(f₁f₂...fₙ)/∂x = Σ[i=1..n] ( (∏[j≠i] fⱼ) * (∂fᵢ/∂x) )
    T deriv = static_cast<T>(0);
    for (std::size_t i = 0; i < evals.size(); ++i) {
        T term = evals[i].partial;
        for (std::size_t j = 0; j < evals.size(); ++j) {
            if (i != j)
                term *= evals[j].value;
        }
        deriv += term;
    }
    return { prod, deriv };
}

// ---------- Explicit Template Instantiations ----------

template struct variable<float>;
template struct variable<double>;

template struct plus<float, expression<float>*, expression<float>*>;
template struct plus<double, expression<double>*, expression<double>*>;

template struct multiply<float, expression<float>*, expression<float>*>;
template struct multiply<double, expression<double>*, expression<double>*>;