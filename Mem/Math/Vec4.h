#pragma once

#include "Vec3.h"

template <typename T, typename = typename std::enable_if<std::is_same<T, int>::value || std::is_same<T, float>::value || std::is_same<T, double>::value>::type>
class Vec4 : public Vec3<T> {
public:
    T w;

    Vec4(T xOff = 0, T yOff = 0, T zOff = 0, T wOff = 0) : Vec3<T>(xOff, yOff, zOff), w(wOff) {};
    Vec4(const Vec4& other) : Vec3<T>(other.x, other.y, other.z), w(other.w) {};

    Vec4 operator+(T offset) const {
        return Vec4(this->x + offset, this->y + offset, this->z + offset, w + offset);
    };

    Vec4 operator+(const Vec4& other) const {
        return Vec4(this->x + other.x, this->y + other.y, this->z + other.z, w + other.w);
    };

    Vec4 operator-(T offset) const {
        return Vec4(this->x - offset, this->y - offset, this->z - offset, w - offset);
    };

    Vec4 operator-(const Vec4& other) const {
        return Vec4(this->x - other.x, this->y - other.y, this->z - other.z, w - other.w);
    };

    Vec4 operator*(T offset) const {
        return Vec4(this->x * offset, this->y * offset, this->z * offset, w * offset);
    };

    Vec4 operator*(const Vec4& other) const {
        return Vec4(this->x * other.x, this->y * other.y, this->z * other.z, w * other.w);
    };

    Vec4 operator/(T offset) const {
        return Vec4(this->x / offset, this->y / offset, this->z / offset, w / offset);
    };

    Vec4 operator/(const Vec4& other) const {
        return Vec4(this->x / other.x, this->y / other.y, this->z / other.z, w / other.w);
    };

    T* get() const {
        return &this->x;
    };
};

template <typename T>
Vec4(T, T, T, T) -> Vec4<T>;