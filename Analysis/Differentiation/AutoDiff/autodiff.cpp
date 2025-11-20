#include "autodiff.h"

template <typename T>
variable<T>::variable(T value) : value(value) {}

template <typename T>
value_and_partial<T> variable<T>::evaluate_and_derive(variable<T>* var) {
    T partial = (this == var) ? static_cast<T>(1) : static_cast<T>(0);
    return { value, partial };
}

//Addition

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

// Product

template <typename T, typename... Ops>
multiply<T, Ops...>::multiply(Ops... ops) : operands(ops...) {
    static_assert((std::is_same_v<Ops, expression<T>*> && ...),
                  "All operands must be expression<T>*");
}

template <typename T, typename... Ops>
value_and_partial<T> multiply<T, Ops...>::evaluate_and_derive(variable<T>* var) {
    constexpr std::size_t n = sizeof...(Ops);

    // Evaluate every operand exactly once
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

// Trigonometric operations

template<typename T>
struct sin_op : unary_op<T> {
    using unary_op<T>::operand;

    sin_op(expression<T>* op) : unary_op<T>(op) {}

    value_and_partial<T> evaluate_and_derive(variable<T>* var) override {
        auto ev = operand->evaluate_and_derive(var);
        return {
            std::sin(ev.value),
            std::cos(ev.value) * ev.partial
        };
    }
};

template<typename T>
struct asin_op : unary_op<T> {
    using unary_op<T>::operand;
    asin_op(expression<T>* op) : unary_op<T>(op) {}

    value_and_partial<T> evaluate_and_derive(variable<T>* var) override {
        auto ev = operand->evaluate_and_derive(var);
        T value = std::asin(ev.value);
        T deriv = ev.partial / std::sqrt(1 - ev.value * ev.value);
        return { value, deriv };
    }
};


template<typename T>
struct cos_op : unary_op<T> {
    using unary_op<T>::operand;

    cos_op(expression<T>* op) : unary_op<T>(op) {}

    value_and_partial<T> evaluate_and_derive(variable<T>* var) override {
        auto ev = operand->evaluate_and_derive(var);
        return {
            std::cos(ev.value),
            -std::sin(ev.value) * ev.partial
        };
    }
};

template<typename T>
struct acos_op : unary_op<T> {
    using unary_op<T>::operand;
    acos_op(expression<T>* op) : unary_op<T>(op) {}

    value_and_partial<T> evaluate_and_derive(variable<T>* var) override {
        auto ev = operand->evaluate_and_derive(var);
        T value = std::acos(ev.value);
        T deriv = -ev.partial / std::sqrt(1 - ev.value * ev.value);
        return { value, deriv };
    }
};

template<typename T>
struct tan_op : unary_op<T> {
    using unary_op<T>::operand;
    tan_op(expression<T>* op) : unary_op<T>(op) {}

    value_and_partial<T> evaluate_and_derive(variable<T>* var) override {
        auto ev = operand->evaluate_and_derive(var);
        T value = std::tan(ev.value);
        T deriv = (1 / std::cos(ev.value)) * (1 / std::cos(ev.value)) * ev.partial; // sec^2(x)
        return { value, deriv };
    }
};

template<typename T>
struct cot_op : unary_op<T> {
    using unary_op<T>::operand;
    cot_op(expression<T>* op) : unary_op<T>(op) {}

    value_and_partial<T> evaluate_and_derive(variable<T>* var) override {
        auto ev = operand->evaluate_and_derive(var);
        T value = static_cast<T>(1) / std::tan(ev.value);
        T deriv = -static_cast<T>(1) / (std::sin(ev.value) * std::sin(ev.value)) * ev.partial; // -csc^2(x)
        return { value, deriv };
    }
};

template<typename T>
struct sec_op : unary_op<T> {
    using unary_op<T>::operand;
    sec_op(expression<T>* op) : unary_op<T>(op) {}

    value_and_partial<T> evaluate_and_derive(variable<T>* var) override {
        auto ev = operand->evaluate_and_derive(var);
        T secx = static_cast<T>(1) / std::cos(ev.value);
        T deriv = secx * std::tan(ev.value) * ev.partial;
        return { secx, deriv };
    }
};


template<typename T>
struct exp_op : unary_op<T> {
    using unary_op<T>::operand;

    exp_op(expression<T>* op) : unary_op<T>(op) {}

    value_and_partial<T> evaluate_and_derive(variable<T>* var) override {
        auto ev = operand->evaluate_and_derive(var);
        T e = std::exp(ev.value);
        return { e, e * ev.partial };
    }
};

template<typename T>
struct log_op : unary_op<T> {
    using unary_op<T>::operand;

    log_op(expression<T>* op) : unary_op<T>(op) {}

    value_and_partial<T> evaluate_and_derive(variable<T>* var) override {
        auto ev = operand->evaluate_and_derive(var);
        return {
            std::log(ev.value),
            (static_cast<T>(1) / ev.value) * ev.partial
        };
    }
};


template struct variable<float>;
template struct variable<double>;

template struct plus<float, expression<float>*, expression<float>*>;
template struct plus<double, expression<double>*, expression<double>*>;

template struct multiply<float, expression<float>*, expression<float>*>;
template struct multiply<double, expression<double>*, expression<double>*>;

template struct sin_op<float>;
template struct sin_op<double>;

template struct asin_op<float>;
template struct asin_op<double>;

template struct cos_op<float>;
template struct cos_op<double>;

template struct acos_op<float>;
template struct acos_op<double>;

template struct tan_op<float>;
template struct tan_op<double>;

template struct cot_op<float>;
template struct cot_op<double>;

template struct sec_op<float>;
template struct sec_op<double>;

template struct exp_op<float>;
template struct exp_op<double>;

template struct log_op<float>;
template struct log_op<double>;
