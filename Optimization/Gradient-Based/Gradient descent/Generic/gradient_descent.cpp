#include "gradient_descent.h"
#include <cmath>

template<typename T>
variable<T>::variable(T value) : value(value) {}

template<typename T>
value_and_partial<T> variable<T>::evaluate_and_derive(variable<T>* var) {
    return {value, (this == var) ? T(1) : T(0)};
}

template<typename T, typename... Ops>
plus<T, Ops...>::plus(Ops... ops) : operands(ops...) {}

template<typename T, typename... Ops>
value_and_partial<T> plus<T, Ops...>::evaluate_and_derive(variable<T>* var) {
    value_and_partial<T> result{T(0), T(0)};
    std::apply([&](auto... ops) {
        ((result.value += ops.evaluate_and_derive(var).value,
        result.partial += ops.evaluate_and_derive(var).partial), ...);
    }, operands);
    return result;
}

template<typename T, typename... Ops>
multiply<T, Ops...>::multiply(Ops... ops) : operands(ops...) {}

template<typename T, typename... Ops>
value_and_partial<T> multiply<T, Ops...>::evaluate_and_derive(variable<T>* var) {
    value_and_partial<T> result{T(1), T(0)};
    std::apply([&](auto... ops) {
        auto eval = [&](auto op) { return op.evaluate_and_derive(var); };
        value_and_partial<T> prod{T(1), T(0)};
        ((prod.value *= eval(ops).value), ...);
        std::apply([&](auto... ops_2) {
            value_and_partial<T> term = eval(ops_2);
            T other_prod = T(1);
            std::apply([&](auto... ops_3) {
                ((ops_3 != ops_2 ? other_prod *= eval(ops_3).value : T(1))), ...);
            }, operands);
            result.partial += term.partial * other_prod;
        }, operands);
        result.value = prod.value;
    }, operands);
    return result;
}

template<typename T, typename F>
void gradient_descent(F objective, std::vector<variable<T>*>& variables, 
                    T learning_rate, int max_iterations, T tolerance) {
    int iteration = 0;
    T prev_value = T(0);
    
    while (iteration < max_iterations) {
        value_and_partial<T> result = objective->evaluate_and_derive(nullptr);
        std::vector<T> gradients;
        for (auto* var : variables) {
            gradients.push_back(objective->evaluate_and_derive(var).partial);
        }

        for (size_t i = 0; i < variables.size(); ++i) {
            variables[i]->value -= learning_rate * gradients[i];
        }

        T current_value = result.value;
        std::cout << "iteration " << iteration + 1 << ":\tvalue = " << current_value;
        for (size_t i = 0; i < variables.size(); ++i) {
            std::cout << ", x_" << i << " = " << variables[i]->value;
        }
        std::cout << "\n";

        if (std::fabs(current_value - prev_value) < tolerance) {
            std::cout << "converged within tolerance.\n";
            break;
        }
        prev_value = current_value;
        iteration++;
    }
    if (iteration >= max_iterations) {
        std::cout << "maximum iterations reached.\n";
    }
}

template<int max_iterations, typename T, typename F>
void gradient_descent_static<max_iterations, T, F>::apply(F objective, 
    std::vector<variable<T>*>& variables, T learning_rate, T tolerance) {
    gradient_descent(objective, variables, learning_rate, max_iterations, tolerance);
}

int main() {
    variable<float> x(2.0f);
    variable<float> y(3.0f);
    std::vector<variable<float>*> vars = {&x, &y};
    
    auto x_squared = multiply<float, variable<float>&, variable<float>&>(x, x);
    auto y_squared = multiply<float, variable<float>&, variable<float>&>(y, y);
    auto objective = plus<float, 
                        multiply<float, variable<float>&, variable<float>&>, 
                        multiply<float, variable<float>&, variable<float>&>>
                        (x_squared, y_squared);

    std::cout << "minimizing f(x, y) = x^2 + y^2:\n";
    gradient_descent(&objective, vars, 0.1f, 50, 0.0001f);

    std::cout << "\nstatic version (10 iterations):\n";
    variable<float> x_2(2.0f), y_2(3.0f);
    std::vector<variable<float>*> vars_2 = {&x_2, &y_2};
    auto x_2_squared = multiply<float, variable<float>&, variable<float>&>(x_2, x_2);
    auto y_2_squared = multiply<float, variable<float>&, variable<float>&>(y_2, y_2);
    auto objective_2 = plus<float, 
                            multiply<float, variable<float>&, variable<float>&>, 
                            multiply<float, variable<float>&, variable<float>&>>
                            (x_2_squared, y_2_squared);
    gradient_descent_static<10, float, decltype(&objective_2)>::apply(
        &objective_2, vars_2, 0.1f, 0.0001f);

    return 0;
}