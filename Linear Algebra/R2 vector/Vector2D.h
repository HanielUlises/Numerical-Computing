#pragma once

#include <iostream>
#include <concepts>
#include <cassert>

template<typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template<arithmetic T>
class Vector2D {
public:
    T x{};
    T y{};

    static constexpr Vector2D zero{ T(0), T(0) };

    // Constructors
    constexpr Vector2D() = default;
    constexpr Vector2D(T x, T y);

    // Mutators
    constexpr void set_x(T val) noexcept;
    constexpr void set_y(T val) noexcept;

    // Accessors
    [[nodiscard]] constexpr T get_x() const noexcept;
    [[nodiscard]] constexpr T get_y() const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);

    // Comparison
    [[nodiscard]] constexpr bool operator==(const Vector2D& other) const noexcept = default;
    [[nodiscard]] constexpr bool operator!=(const Vector2D& other) const noexcept = default;

    // Unary
    [[nodiscard]] constexpr Vector2D operator-() const noexcept;

    // Scalar arithmetic
    [[nodiscard]] constexpr Vector2D operator*(T scalar) const noexcept;
    [[nodiscard]] Vector2D operator/(T scalar) const;

    constexpr Vector2D& operator*=(T scalar) noexcept;
    Vector2D& operator/=(T scalar);

    friend constexpr Vector2D operator*(T scalar, const Vector2D& v) noexcept {
        return v * scalar;
    }

    // Vector arithmetic
    [[nodiscard]] constexpr Vector2D operator+(const Vector2D& other) const noexcept;
    [[nodiscard]] constexpr Vector2D operator-(const Vector2D& other) const noexcept;

    constexpr Vector2D& operator+=(const Vector2D& other) noexcept;
    constexpr Vector2D& operator-=(const Vector2D& other) noexcept;

    // Geometry & utilities
    [[nodiscard]] constexpr T magnitude_squared() const noexcept;
    [[nodiscard]] T magnitude() const noexcept;

    [[nodiscard]] Vector2D unit() const;
    Vector2D& normalize();

    [[nodiscard]] T distance_to(const Vector2D& other) const noexcept;
    [[nodiscard]] constexpr T dot(const Vector2D& other) const noexcept;
    [[nodiscard]] constexpr T cross(const Vector2D& other) const noexcept;

    [[nodiscard]] T angle_between(const Vector2D& other) const;
    [[nodiscard]] Vector2D project_onto(const Vector2D& onto) const;
    [[nodiscard]] Vector2D reflect_over(const Vector2D& normal) const;

    void rotate(T angle_radians, const Vector2D& around_point = zero);
    [[nodiscard]] Vector2D rotated(T angle_radians, const Vector2D& around_point = zero) const;

    void clamp_magnitude(T max_magnitude);

    static constexpr Vector2D lerp(const Vector2D& a, const Vector2D& b, T t) noexcept;
    static T angle_from_to(const Vector2D& from, const Vector2D& to);
};