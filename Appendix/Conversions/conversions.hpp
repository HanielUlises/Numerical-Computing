// include/appendix/conversions/conversions.hpp
#pragma once

#include <cctype>
#include <concepts>
#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace appendix::conversions {

[[nodiscard]] inline int
binary_to_decimal(std::string_view binary)
{
    int result = 0;
    for (char c : binary) {
        if (c < '0' || c > '1')
            throw std::invalid_argument("invalid binary digit: '"s + c + "'");
        result = (result << 1) | (c - '0');
    }
    return result;
}

[[nodiscard]] inline std::string
decimal_to_binary(int decimal)
{
    if (decimal == 0)
        return "0";

    std::string bin;
    bool negative = decimal < 0;
    if (negative)
        decimal = -decimal;

    while (decimal > 0) {
        bin.push_back('0' + (decimal & 1));
        decimal >>= 1;
    }
    if (negative)
        bin.push_back('-');

    std::reverse(bin.begin(), bin.end());
    return bin;
}

// Generic base conversion: from_base -> 10
template<std::integral T = int>
[[nodiscard]] T
from_base(std::string_view digits, int base)
{
    if (base < 2 || base > 36)
        throw std::invalid_argument("base must be between 2 and 36");

    T result = 0;
    for (char c : digits) {
        int value;
        if (c >= '0' && c <= '9')
            value = c - '0';
        else if (c >= 'A' && c <= 'Z')
            value = 10 + (c - 'A');
        else if (c >= 'a' && c <= 'z')
            value = 10 + (c - 'a');
        else
            throw std::invalid_argument("invalid digit for base");

        if (value >= base)
            throw std::invalid_argument("digit out of range for base");

        result = result * base + value;
    }
    return result;
}

// Generic base conversion: 10 -> to_base
template<std::integral T = int>
[[nodiscard]] std::string
to_base(T value, int base)
{
    if (base < 2 || base > 36)
        throw std::invalid_argument("base must be between 2 and 36");
    if (value == 0)
        return "0";

    std::string result;
    bool negative = value < 0;
    if (negative && std::is_signed_v<T>)
        value = -value;

    while (value > 0) {
        int digit = value % base;
        char c = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
        result.push_back(c);
        value /= base;
    }
    if (negative)
        result.push_back('-');

    std::reverse(result.begin(), result.end());
    return result;
}

// Interactive runners
inline void
run_binary_to_decimal()
{
    std::cout << "enter binary number (base 2) -> decimal:\n> ";
    std::string input;
    if (!std::getline(std::cin, input) || input.empty())
        return;
    std::cout << binary_to_decimal(input) << '\n';
}

inline void
run_decimal_to_binary()
{
    std::cout << "enter decimal number -> binary (base 2):\n> ";
    std::string input;
    if (!std::getline(std::cin, input) || input.empty())
        return;
    int value = std::stoi(input);
    std::cout << decimal_to_binary(value) << '\n';
}

inline void
run_from_base()
{
    std::cout << "enter number and base (e.g. 'FF 16') -> decimal:\n> ";
    std::string digits, base_str;
    if (!std::getline(std::cin, digits, ' ') || digits.empty())
        return;
    if (!std::getline(std::cin, base_str) || base_str.empty())
        return;

    int base = std::stoi(base_str);
    std::cout << from_base(digits, base) << '\n';
}

inline void
run_to_base()
{
    std::cout << "enter decimal and target base (e.g. '255 16') -> base-n:\n> ";
    std::string value_str, base_str;
    if (!std::getline(std::cin, value_str, ' ') || value_str.empty())
        return;
    if (!std::getline(std::cin, base_str) || base_str.empty())
        return;

    int value = std::stoi(value_str);
    int base = std::stoi(base_str);
    std::cout << to_base(value, base) << '\n';
}

} 