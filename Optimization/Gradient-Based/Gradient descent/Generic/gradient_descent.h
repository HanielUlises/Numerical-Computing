#pragma once

#include "../Analysis/Differentiation/AutoDiff/autodiff.h"
#include <vector>
#include <iostream>


template<typename T, typename F>
void gradient_descent(F objective,
                      std::vector<variable<T>*>& variables,
                      T learning_rate,
                      int max_iterations,
                      T tolerance);

template<int MaxIterations, typename T, typename F>
inline void gradient_descent(F objective,
                             std::vector<variable<T>*>& variables,
                             T learning_rate,
                             T tolerance){
    gradient_descent<T, F>(objective,
                           variables,
                           learning_rate,
                           MaxIterations,
                           tolerance);
}