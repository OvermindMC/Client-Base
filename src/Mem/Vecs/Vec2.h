#pragma once

#include <concepts>
#include <type_traits>

template<typename T>
concept Numeric = std::is_same_v<T, int> || std::is_same_v<T, float> || std::is_same_v<T, double>;

template<Numeric T>
struct Vec2 {
    T x{}, y{};

    constexpr explicit Vec2(T x = T(0), T y = T(0)) noexcept : x(x), y(y) {};

    
    [[nodiscard]] constexpr bool operator==(const Vec2& other) const noexcept {
        return x == other.x && y == other.y;
    };

    [[nodiscard]] constexpr bool operator!=(const Vec2& other) const noexcept {
        return !(*this == other);
    };


    constexpr Vec2& operator+=(const Vec2& other) noexcept {
        x += other.x;
        y += other.y;
        return *this;
    };

    [[nodiscard]] constexpr Vec2 operator+(const Vec2& other) const noexcept {
        return Vec2(x + other.x, y + other.y);
    };

    constexpr Vec2& operator+=(T offset) noexcept {
        x += offset;
        y += offset;
        return *this;
    };

    [[nodiscard]] constexpr Vec2 operator+(T offset) const noexcept {
        return Vec2(x + offset, y + offset);
    };

    [[nodiscard]] friend constexpr Vec2 operator+(T lhs, const Vec2& rhs) noexcept {
        return Vec2(lhs + rhs.x, lhs + rhs.y);
    };


    constexpr Vec2& operator-=(const Vec2& other) noexcept {
        x -= other.x;
        y -= other.y;
        return *this;
    };

    [[nodiscard]] constexpr Vec2 operator-(const Vec2& other) const noexcept {
        return Vec2(x - other.x, y - other.y);
    };

    constexpr Vec2& operator-=(T offset) noexcept {
        x -= offset;
        y -= offset;
        return *this;
    };

    [[nodiscard]] constexpr Vec2 operator-(T offset) const noexcept {
        return Vec2(x - offset, y - offset);
    };

    [[nodiscard]] friend constexpr Vec2 operator-(T lhs, const Vec2& rhs) noexcept {
        return Vec2(lhs - rhs.x, lhs - rhs.y);
    };


    constexpr Vec2& operator/=(const Vec2& other) noexcept requires std::floating_point<T> {
        x /= other.x;
        y /= other.y;
        return *this;
    };

    [[nodiscard]] constexpr Vec2 operator/(const Vec2& other) const noexcept requires std::floating_point<T> {
        return Vec2(x / other.x, y / other.y);
    };

    constexpr Vec2& operator/=(T offset) noexcept requires std::floating_point<T> {
        x /= offset;
        y /= offset;
        return *this;
    };

    [[nodiscard]] constexpr Vec2 operator/(T offset) const noexcept requires std::floating_point<T> {
        return Vec2(x / offset, y / offset);
    };

    [[nodiscard]] friend constexpr Vec2 operator/(T lhs, const Vec2& rhs) noexcept requires std::floating_point<T> {
        return Vec2(lhs / rhs.x, lhs / rhs.y);
    };


    constexpr Vec2& operator*=(const Vec2& other) noexcept {
        x *= other.x;
        y *= other.y;
        return *this;
    };

    [[nodiscard]] constexpr Vec2 operator*(const Vec2& other) const noexcept {
        return Vec2(x * other.x, y * other.y);
    };

    constexpr Vec2& operator*=(T offset) noexcept {
        x *= offset;
        y *= offset;
        return *this;
    };

    [[nodiscard]] constexpr Vec2 operator*(T offset) const noexcept {
        return Vec2(x * offset, y * offset);
    };

    [[nodiscard]] friend constexpr Vec2 operator*(T lhs, const Vec2& rhs) noexcept {
        return Vec2(lhs * rhs.x, lhs * rhs.y);
    };
};