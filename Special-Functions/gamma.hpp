#pragma once
#include <type_traits>

namespace special_functions {

template <typename T>
requires std::is_floating_point_v<T>
T gamma(T x);

}
