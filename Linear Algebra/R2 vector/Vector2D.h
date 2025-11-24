#pragma once

#include <iostream>
#include <concepts>

template<typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template<arithmetic T>
class Vector2D {
public:
    T x{};
    T y{};

    static const Vector2D zero;

    // ctors
    constexpr Vector2D();
    constexpr Vector2D(T x, T y);

    // mutators
    constexpr void set_x(T val) noexcept;
    constexpr void set_y(T val) noexcept;

    // accessors
    [[nodiscard]] constexpr T get_x() const noexcept;
    [[nodiscard]] constexpr T get_y() const noexcept;

    // stream
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        return os << '(' << v.x << ", " << v.y << ')';
    }

    // comparison
    [[nodiscard]] constexpr bool operator==(const Vector2D& other) const noexcept = default;
    [[nodiscard]] constexpr bool operator!=(const Vector2D& other) const noexcept = default;

    // unary
    [[nodiscard]] constexpr Vector2D operator-() const noexcept;

    // scalar ops
    [[nodiscard]] constexpr Vector2D operator*(T scalar) const noexcept;
    [[nodiscard]] Vector2D operator/(T scalar) const;

    constexpr Vector2D& operator*=(T scalar) noexcept;
    Vector2D& operator/=(T scalar);

    friend constexpr Vector2D operator*(T scalar, const Vector2D& v) noexcept {
        return v * scalar;
    }

    // vector ops
    [[nodiscard]] constexpr Vector2D operator+(const Vector2D& other) const noexcept;
    [[nodiscard]] constexpr Vector2D operator-(const Vector2D& other) const noexcept;

    constexpr Vector2D& operator+=(const Vector2D& other) noexcept;
    constexpr Vector2D& operator-=(const Vector2D& other) noexcept;

    // geometry
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

    constexpr T& operator[](std::size_t i);
    constexpr const T& operator[](std::size_t i) const;

    constexpr Vector2D operator*(const Vector2D& other) const noexcept;
    constexpr Vector2D operator/(const Vector2D& other) const;
    constexpr Vector2D& operator*=(const Vector2D& other) noexcept;
    Vector2D& operator/=(const Vector2D& other);

    // perpendiculars
    [[nodiscard]] constexpr Vector2D perpendicular_left() const noexcept;
    [[nodiscard]] constexpr Vector2D perpendicular_right() const noexcept;

    // zero checks
    [[nodiscard]] constexpr bool is_zero() const noexcept;
    [[nodiscard]] constexpr bool nearly_zero(T eps = T(1e-6)) const noexcept;

    // component clamping
    constexpr void clamp(T min_value, T max_value) noexcept;

    // component-wise min/max
    static constexpr Vector2D min(const Vector2D& a, const Vector2D& b) noexcept;
    static constexpr Vector2D max(const Vector2D& a, const Vector2D& b) noexcept;

    // determinant alias
    constexpr T determinant(const Vector2D& other) const noexcept;

    // polar angle
    [[nodiscard]] T angle() const noexcept;

    // conversion
    static constexpr T deg2rad(T deg) noexcept;
    static constexpr T rad2deg(T rad) noexcept;

    [[nodiscard]] Vector2D normalized_or_zero() const noexcept;

    // floor/ceil/round
    [[nodiscard]] Vector2D floor() const noexcept;
    [[nodiscard]] Vector2D ceil() const noexcept;
    [[nodiscard]] Vector2D round() const noexcept;
};

template<arithmetic T>
inline const Vector2D<T> Vector2D<T>::zero{ T(0), T(0) };

