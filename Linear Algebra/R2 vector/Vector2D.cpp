#include "Vector2D.h"
#include "Utils.h"
#include <cmath>
#include <cassert>
#include <numbers>

template<arithmetic T>
constexpr Vector2D<T>::Vector2D(T x_val, T y_val)
    : x(x_val), y(y_val)
{
}

template<arithmetic T>
constexpr void Vector2D<T>::set_x(T val) noexcept { x = val; }

template<arithmetic T>
constexpr void Vector2D<T>::set_y(T val) noexcept { y = val; }

template<arithmetic T>
constexpr T Vector2D<T>::get_x() const noexcept { return x; }

template<arithmetic T>
constexpr T Vector2D<T>::get_y() const noexcept { return y; }

template<arithmetic T>
std::ostream& operator<<(std::ostream& os, const Vector2D<T>& v)
{
    return os << '(' << v.x << ", " << v.y << ')';
}

template<arithmetic T>
constexpr Vector2D<T> Vector2D<T>::operator-() const noexcept
{
    return {-x, -y};
}

template<arithmetic T>
constexpr Vector2D<T> Vector2D<T>::operator*(T scalar) const noexcept
{
    return {x * scalar, y * scalar};
}

template<arithmetic T>
Vector2D<T> Vector2D<T>::operator/(T scalar) const
{
    assert(!nearly_zero(scalar));
    return {x / scalar, y / scalar};
}

template<arithmetic T>
constexpr Vector2D<T>& Vector2D<T>::operator*=(T scalar) noexcept
{
    x *= scalar;
    y *= scalar;
    return *this;
}

template<arithmetic T>
Vector2D<T>& Vector2D<T>::operator/=(T scalar)
{
    assert(!nearly_zero(scalar));
    x /= scalar;
    y /= scalar;
    return *this;
}

template<arithmetic T>
constexpr Vector2D<T> Vector2D<T>::operator+(const Vector2D<T>& other) const noexcept
{
    return {x + other.x, y + other.y};
}

template<arithmetic T>
constexpr Vector2D<T> Vector2D<T>::operator-(const Vector2D<T>& other) const noexcept
{
    return {x - other.x, y - other.y};
}

template<arithmetic T>
constexpr Vector2D<T>& Vector2D<T>::operator+=(const Vector2D<T>& other) noexcept
{
    x += other.x;
    y += other.y;
    return *this;
}

template<arithmetic T>
constexpr Vector2D<T>& Vector2D<T>::operator-=(const Vector2D<T>& other) noexcept
{
    x -= other.x;
    y -= other.y;
    return *this;
}

template<arithmetic T>
constexpr T Vector2D<T>::magnitude_squared() const noexcept
{
    return x * x + y * y;
}

template<arithmetic T>
T Vector2D<T>::magnitude() const noexcept
{
    return std::sqrt(magnitude_squared());
}

template<arithmetic T>
Vector2D<T> Vector2D<T>::unit() const
{
    const T mag = magnitude();
    assert(!nearly_zero(mag));
    return *this / mag;
}

template<arithmetic T>
Vector2D<T>& Vector2D<T>::normalize()
{
    const T mag = magnitude();
    assert(!nearly_zero(mag));
    return *this /= mag;
}

template<arithmetic T>
T Vector2D<T>::distance_to(const Vector2D<T>& other) const noexcept
{
    return (*this - other).magnitude();
}

template<arithmetic T>
constexpr T Vector2D<T>::dot(const Vector2D<T>& other) const noexcept
{
    return x * other.x + y * other.y;
}

template<arithmetic T>
constexpr T Vector2D<T>::cross(const Vector2D<T>& other) const noexcept
{
    return x * other.y - y * other.x;
}

template<arithmetic T>
T Vector2D<T>::angle_between(const Vector2D<T>& other) const
{
    const T cos_theta = dot(other) / (magnitude() * other.magnitude());
    return std::acos(std::clamp(cos_theta, T(-1), T(1)));
}

template<arithmetic T>
Vector2D<T> Vector2D<T>::project_onto(const Vector2D<T>& onto) const
{
    const T denom = onto.magnitude_squared();
    assert(!nearly_zero(denom));
    return onto * (dot(onto) / denom);
}

template<arithmetic T>
Vector2D<T> Vector2D<T>::reflect_over(const Vector2D<T>& normal) const
{
    return *this - normal.unit() * (dot(normal) * T(2));
}

template<arithmetic T>
void Vector2D<T>::rotate(T angle_radians, const Vector2D<T>& around_point)
{
    const T c = std::cos(angle_radians);
    const T s = std::sin(angle_radians);
    const T tx = x - around_point.x;
    const T ty = y - around_point.y;

    x = tx * c - ty * s + around_point.x;
    y = tx * s + ty * c + around_point.y;
}

template<arithmetic T>
Vector2D<T> Vector2D<T>::rotated(T angle_radians, const Vector2D<T>& around_point) const
{
    Vector2D<T> copy = *this;
    copy.rotate(angle_radians, around_point);
    return copy;
}

template<arithmetic T>
void Vector2D<T>::clamp_magnitude(T max_magnitude)
{
    const T mag_sq = magnitude_squared();
    if (mag_sq > max_magnitude * max_magnitude) {
        *this *= max_magnitude / std::sqrt(mag_sq);
    }
}

template<arithmetic T>
constexpr Vector2D<T> Vector2D<T>::lerp(const Vector2D<T>& a, const Vector2D<T>& b, T t) noexcept
{
    return a + (b - a) * t;
}

template<arithmetic T>
T Vector2D<T>::angle_from_to(const Vector2D<T>& from, const Vector2D<T>& to)
{
    return std::atan2(to.y - from.y, to.x - from.x);
}

template class Vector2D<float>;
template class Vector2D<double>;
template class Vector2D<int>;
template class Vector2D<long long>;