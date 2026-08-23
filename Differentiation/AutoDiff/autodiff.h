#pragma once

#include <tuple>
#include <array>
#include <cstddef>
#include <type_traits>
#include <utility>

// Holds the numerical value of an expression and its partial
// derivative with respect to a single variable.  This type is
// returned by every expression node during automatic
// differentiation so that value and derivative information
// propagate together through the expression graph.
template <typename T>
struct value_and_partial {
    static_assert(std::is_same_v<T, float> || std::is_same_v<T, double>,
                  "Only float and double are supported.");
    T value, partial;
};

template <typename T>
struct variable;

template <typename T>
struct expression {
    virtual ~expression() = default;
    virtual value_and_partial<T> evaluate_and_derive(variable<T>* var) = 0;
};

template <typename T>
struct variable : public expression<T> {
    T value;
    explicit variable(T value);
    value_and_partial<T> evaluate_and_derive(variable<T>* var) override;
};

template <typename T, typename... Ops>
struct plus : public expression<T> {
    std::tuple<Ops...> operands;
    explicit plus(Ops... ops);
    value_and_partial<T> evaluate_and_derive(variable<T>* var) override;
};

template <typename T, typename... Ops>
struct multiply : public expression<T> {
    std::tuple<Ops...> operands;
    explicit multiply(Ops... ops);
    value_and_partial<T> evaluate_and_derive(variable<T>* var) override;
};

template <typename T>
struct unary_op : expression<T> {
    expression<T>* operand;

    unary_op(expression<T>* op) : operand(op) {}
};