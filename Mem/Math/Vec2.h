#pragma once

#include <type_traits>

template <typename T, typename = typename std::enable_if<std::is_same<T, int>::value || std::is_same<T, float>::value || std::is_same<T, double>::value>::type>
class Vec2 {
public:
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

    T* get() const {
        return &this->x;
    };
};

template <typename T>
Vec2(T, T) -> Vec2<T>;