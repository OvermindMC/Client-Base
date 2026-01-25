#pragma once

#include "Vec2.h"

template<Numeric T>
struct Vec3 {
    T x{}, y{}, z{};

    constexpr explicit Vec3(T x = T(0), T y = T(0), T z = T(0)) noexcept : x(x), y(y), z(z) {};

    
    [[nodiscard]] constexpr bool operator==(const Vec3& other) const noexcept {
        return x == other.x && y == other.y && z == other.z;
    };

    [[nodiscard]] constexpr bool operator!=(const Vec3& other) const noexcept {
        return !(*this == other);
    };


    constexpr Vec3& operator+=(const Vec3& other) noexcept {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    };

    [[nodiscard]] constexpr Vec3 operator+(const Vec3& other) const noexcept {
        return Vec3(x + other.x, y + other.y, z + other.z);
    };

    constexpr Vec3& operator+=(T offset) noexcept {
        x += offset;
        y += offset;
        z += offset;
        return *this;
    };

    [[nodiscard]] constexpr Vec3 operator+(T offset) const noexcept {
        return Vec3(x + offset, y + offset, z + offset);
    };

    [[nodiscard]] friend constexpr Vec3 operator+(T lhs, const Vec3& rhs) noexcept {
        return Vec3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
    };


    constexpr Vec3& operator-=(const Vec3& other) noexcept {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    };

    [[nodiscard]] constexpr Vec3 operator-(const Vec3& other) const noexcept {
        return Vec3(x - other.x, y - other.y, z - other.z);
    };

    constexpr Vec3& operator-=(T offset) noexcept {
        x -= offset;
        y -= offset;
        z -= offset;
        return *this;
    };

    [[nodiscard]] constexpr Vec3 operator-(T offset) const noexcept {
        return Vec3(x - offset, y - offset, z - offset);
    };

    [[nodiscard]] friend constexpr Vec3 operator-(T lhs, const Vec3& rhs) noexcept {
        return Vec3(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
    };


    constexpr Vec3& operator/=(const Vec3& other) noexcept requires std::floating_point<T> {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    };

    [[nodiscard]] constexpr Vec3 operator/(const Vec3& other) const noexcept requires std::floating_point<T> {
        return Vec3(x / other.x, y / other.y, z / other.z);
    };

    constexpr Vec3& operator/=(T offset) noexcept requires std::floating_point<T> {
        x /= offset;
        y /= offset;
        z /= offset;
        return *this;
    };

    [[nodiscard]] constexpr Vec3 operator/(T offset) const noexcept requires std::floating_point<T> {
        return Vec3(x / offset, y / offset, z / offset);
    };

    [[nodiscard]] friend constexpr Vec3 operator/(T lhs, const Vec3& rhs) noexcept requires std::floating_point<T> {
        return Vec3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
    };


    constexpr Vec3& operator*=(const Vec3& other) noexcept {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    };

    [[nodiscard]] constexpr Vec3 operator*(const Vec3& other) const noexcept {
        return Vec3(x * other.x, y * other.y, z * other.z);
    };

    constexpr Vec3& operator*=(T offset) noexcept {
        x *= offset;
        y *= offset;
        z *= offset;
        return *this;
    };

    [[nodiscard]] constexpr Vec3 operator*(T offset) const noexcept {
        return Vec3(x * offset, y * offset, z * offset);
    };

    [[nodiscard]] friend constexpr Vec3 operator*(T lhs, const Vec3& rhs) noexcept {
        return Vec3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
    };
};