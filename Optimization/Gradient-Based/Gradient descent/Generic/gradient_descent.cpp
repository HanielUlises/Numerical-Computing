#pragma once

#include "gradient_descent.h"

#include <cmath>
#include <limits>
#include <iostream>

template<typename T, typename F>
void gradient_descent(F objective,
                      std::vector<variable<T>*>& variables,
                      T learning_rate,
                      int max_iterations,
                      T tolerance)
{
    // Basic sanity checks (fail fast)
    if (!objective) {
        std::cerr << "gradient_descent: null objective pointer\n";
        return;
    }
    if (variables.empty()) {
        std::cerr << "gradient_descent: no variables to optimize\n";
        return;
    }
    if (max_iterations <= 0) {
        std::cerr << "gradient_descent: max_iterations must be positive\n";
        return;
    }

    // previous value used for convergence test; initialize with +inf so
    // the first iteration doesn't trigger early exit when current value is finite.
    T prev_value = std::numeric_limits<T>::infinity();

    for (int iter = 0; iter < max_iterations; ++iter)
    {
        // Evaluate objective value (no derivative requested)
        value_and_partial<T> obj_v = objective->evaluate_and_derive(nullptr);
        T current_value = obj_v.value;

        // Compute gradient: evaluate derivative w.r.t. each variable once
        std::vector<T> gradients;
        gradients.reserve(variables.size());
        for (auto* v : variables) {
            auto vp = objective->evaluate_and_derive(v); // evaluate value+partial w.r.t v
            gradients.push_back(vp.partial);
        }

        // Update variables: x <- x - lr * grad
        for (std::size_t i = 0; i < variables.size(); ++i) {
            variables[i]->value -= learning_rate * gradients[i];
        }

        // Logging (keeps same format as the rest of the project)
        std::cout << "iteration " << (iter + 1) << ":\tvalue = " << current_value;
        for (std::size_t i = 0; i < variables.size(); ++i)
            std::cout << ", x_" << i << " = " << variables[i]->value;
        std::cout << '\n';

        // Convergence check: absolute change in objective value
        if (std::fabs(current_value - prev_value) < tolerance) {
            std::cout << "converged within tolerance.\n";
            return;
        }

        prev_value = current_value;
    }

    std::cout << "maximum iterations reached.\n";
}
