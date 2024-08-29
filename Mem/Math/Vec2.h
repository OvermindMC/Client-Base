#pragma once

#include <type_traits>
#include <string>

template <typename T, typename = typename std::enable_if<std::is_same<T, int>::value || std::is_same<T, float>::value || std::is_same<T, double>::value>::type>
struct Vec2 {
    T x, y;

    Vec2(T xOff = 0, T yOff = 0) : x(xOff), y(yOff) {};
    Vec2(const Vec2& other) : x(other.x), y(other.y) {};

    Vec2 operator+(T offset) const {
        return Vec2(x + offset, y + offset);
    };

    Vec2 operator+(const Vec2& other) const {
        return Vec2(x + other.x, y + other.y);
    };

    Vec2 operator-(T offset) const {
        return Vec2(x - offset, y - offset);
    };

    Vec2 operator-(const Vec2& other) const {
        return Vec2(x - other.x, y - other.y);
    };

    Vec2 operator*(T offset) const {
        return Vec2(x * offset, y * offset);
    };

    Vec2 operator*(const Vec2& other) const {
        return Vec2(x * other.x, y * other.y);
    };

    Vec2 operator/(T offset) const {
        return Vec2(x / offset, y / offset);
    };

    Vec2 operator/(const Vec2& other) const {
        return Vec2(x / other.x, y / other.y);
    };

    float magnitude() const {
        return std::sqrt(this->x * this->x + this->y * this->y);
    };

    std::string toStr() const {
        return std::to_string(this->x) + ", " + std::to_string(this->y);
    };

    operator std::string() const {
        return toStr();
    };
};

template <typename T>
Vec2(T, T) -> Vec2<T>;